#include "MainMemory.h"
#include "types.h"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <format>
#include <stdexcept>

MainMemory::MainMemory() : memory(std::make_unique<std::array<u8, MAIN_MEMORY_SIZE>>())
{
  memory->fill(0x00);
}

MainMemory::~MainMemory()
{

}

void MainMemory::Read(u32 startAddress, u32 size, u8* destination)
{
  if (startAddress > MAIN_MEMORY_SIZE || size > (MAIN_MEMORY_SIZE - startAddress))
  {
    throw std::out_of_range("MainMemory::Read out of bounds");
  }
  std::memcpy(destination, memory->data() + startAddress, size);
}


void MainMemory::Write(u32 startAddress, u32 size, const u8* source)
{
  if (startAddress > MAIN_MEMORY_SIZE || size > (MAIN_MEMORY_SIZE - startAddress))
  {
    throw std::out_of_range("MainMemory::Write out of bounds");
  }
  std::memcpy(memory->data() + startAddress, source, size);
}


void MainMemory::Print(u32 startAddress, u32 bytesToPrint)
{
  if (startAddress >= MAIN_MEMORY_SIZE)
  {
    throw std::out_of_range("MainMemory::Print start address out of bounds");
  }

  const u32 columns = 12;
  const u32 maxBytes = MAIN_MEMORY_SIZE - startAddress;
  const u32 count = std::min(bytesToPrint, maxBytes);

  for (u32 i = 0; i < count; ++i)
  {
    std::cout << std::format("0x{:x}\t", (*memory)[startAddress + i]);
    if ((i + 1) % columns == 0)
    {
      std::cout << '\n';
    }
  }
  if (count % columns != 0)
  {
    std::cout << '\n';
  }
  std::cout << std::dec;
}


// NOTES:
// memcpy(dest, source, size) copies size bytes from source into memory starting at startAddress
// source & dest = both are expected to be addresses (pointers)
