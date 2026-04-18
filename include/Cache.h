#pragma once

#include "MainMemory.h"
#include "RandomReplacement.h"
#include "types.h"

#include <array>


// general idea for data size:
// addresses = u32
// actual byte data = u8

// total lines = 64 sets * 4 ways = 256 cache lines
// each cache line of size = 64 bytes
// memory address = 32-bit

const u8 MEMORY_ADDRESS_SIZE = 32;    // 32-bit memory addresses
const u8 CACHE_LINE_SIZE = 64;        // 64-byte cache lines
const u32 CACHE_SETS = 64;            // Cache with 64 sets
const u8 CACHE_WAYS = 4;              // 4-way set associative cache 



// MEMORY ADDRESS = [TAG | SET INDEX | BYTE OFFSET]
// BYTE OFFSET = which byte inside a 64 byte cache line
// SET INDEX = which set to check among all 64 sets of Cache
// TAG SIZE = for that specific set, which memory block is it

const u8 CACHE_LINE_BYTE_OFFSET_SIZE = 6;
const u8 CACHE_LINE_SET_INDEX_SIZE = 6;
const u8 CACHE_LINE_TAG_SIZE = 20;


struct CacheLine
{
  u32 tag = 0;
  std::array<u8, CACHE_LINE_SIZE> data;
  bool valid = false;
};

struct AddressParts
{
  u32 tag;
  u8 setIndex;
  u8 byteOffset;

  AddressParts(u32 address)
  {
    byteOffset = address & (CACHE_LINE_SIZE - 1);
    setIndex = (address >> CACHE_LINE_BYTE_OFFSET_SIZE) & ((1 << CACHE_LINE_SET_INDEX_SIZE) - 1);
    tag = address >> (CACHE_LINE_BYTE_OFFSET_SIZE + CACHE_LINE_SET_INDEX_SIZE);
  }
};

class CacheSet
{
public:
  CacheSet();
  ~CacheSet();

  CacheLine* Find(u32 tag);
  CacheLine* Replace(u32 tag, u8* sourceData);

private:
  std::array<CacheLine, CACHE_WAYS> lines;   // Array of caches lines 
  RandomReplacement replacement;             // Random replacement algorithm
};

class Cache
{

};