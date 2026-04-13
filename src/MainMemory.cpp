#include "MainMemory.h"
#include "types.h"
#include <array>

MainMemory::MainMemory()
{
  memory = std::make_unique<std::array<u8, MAIN_MEMORY_SIZE>>();
  memory.get()->fill(0x00);
}

MainMemory::~MainMemory()
{

}

void MainMemory::Read(u32 startAddress, u8 size, u8* destination)
{
  // Read the request amount of memory and copy to destination
  std::memcpy(destination, &memory.get()->at(startAddress), size);
}


void MainMemory::Write(u32 startAddress, u8 size, u8* source)
{
  // Copy requested amount of memory from source to main memory
  std::memcpy(&memory.get()->at(startAddress), source, size);
}


void MainMemory::Print()
{
  
}


// NOTES:
// memcpy(dest, source, size) copies size bytes from source into memory starting at startAddress
// source & dest = both are expected to be addresses (pointers)

