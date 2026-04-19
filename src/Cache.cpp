#include "Cache.h"
#include <string>
#include <format>
#include <iostream>

CacheSet::CacheSet()
{
  // Set the number of cache ways in the replacement algorithm
  replacement.SetWays(CACHE_WAYS);
}

CacheSet::~CacheSet()
{

}

CacheLine* CacheSet::Find(u32 tag)
{
  // Find cache line based on the given tag
  for (u8 way = 0; way < CACHE_WAYS; way++)
  {
    if (lines[way].valid && lines[way].tag == tag)
    {
      return &lines[way];
    }
  }
  // Cache line was not found, return nullptr
  return nullptr;
}

CacheLine* CacheSet::Replace(u32 tag, u8* sourceData)
{
  // Get a line to replace
  u8 to_replace = replacement.GetToReplace();

  // Set new cache line attributes
  lines[to_replace].valid = true;
  lines[to_replace].tag = tag;

  // Copy 64 byte data from main memory to cache
  std::memcpy(lines[to_replace].data.data(), sourceData, CACHE_LINE_SIZE);

  return &lines[to_replace];
}

void Cache::Initialise(MainMemory* memory)
{
  mainMemory = memory;
}

u32 Cache::Read(u32 address)
{
  AddressParts addressParts(address); // split them using Struct AddressParts

  // Find requested cache line
  CacheLine* line = sets[addressParts.setIndex].Find(addressParts.tag);

  if (line) // cache hit
  {
    std::string message = std::format(
      "Reading from cache (address: 0x{:x}, set: {}, tag: {})",
      address, static_cast<u32>(addressParts.setIndex), addressParts.tag
    );

    std::cout << message << std::endl;

    // Reinterpret the memory as a 32-bit integer
    return *reinterpret_cast<u32*>(&line->data[addressParts.byteOffset]);
  }
  else // Cache miss
  {
    // Find the beginning of the cache line
    u32 lineStart = address & ~(CACHE_LINE_SIZE - 1);

    // Allocate data buffer
    std::array<u8, CACHE_LINE_SIZE> buffer;

    // Read the requested data from main memory
    mainMemory->Read(lineStart, CACHE_LINE_SIZE, buffer.data());

    // Replace the cache line in the set
    CacheLine* newLine = sets[addressParts.setIndex].Replace(addressParts.tag, buffer.data());

    // Reintepret the memory as a 32-bit integer and return it
    return *reinterpret_cast<u32*>(&newLine->data[addressParts.byteOffset]);
  }

  return 0;
}

void Cache::Write(u32 address, u32 data)
{
  AddressParts addressParts(address);

  CacheLine* line = sets[addressParts.setIndex].Find(addressParts.tag);

  std::cout << std::format(
    "Writing to cache (address: 0x{:x}, set: {}, tag: {})",
    address, static_cast<u32>(addressParts.setIndex), addressParts.tag
  ) << std::endl;

  if (line) // Cache hit
  {
    // Cache hit:
    // write the 32-bit data directly into the cache line at the byte offset.
    *reinterpret_cast<u32*>(&line->data[addressParts.byteOffset]) = data;
  }
  else // Cache miss
  {
    // Find the beginning of the cache line that this address belongs to.
    u32 lineStart = address & ~(CACHE_LINE_SIZE - 1);

    // Allocate a temporary 64-byte buffer for the full cache line.
    std::array<u8, CACHE_LINE_SIZE> buffer;

    // Read the full cache line from main memory into the buffer.
    mainMemory->Read(lineStart, CACHE_LINE_SIZE, buffer.data());

    // Replace one line in the target set with this fetched data (write-allocate).
    line = sets[addressParts.setIndex].Replace(addressParts.tag, buffer.data());

    // Now write the 32-bit value into the new cache line at the byte offset.
    *reinterpret_cast<u32*>(&line->data[addressParts.byteOffset]) = data;
  }

  // Write - through cache (immediately write modified data to main memory)
  std::cout << std::format("Writing to main memory (address: 0x{:x})", address) << std::endl;
  mainMemory->Write(address, sizeof(u32), reinterpret_cast<const u8*>(&data));
}
