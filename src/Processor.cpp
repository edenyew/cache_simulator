#include "Processor.h"
#include "types.h"
#include <iostream>
#include <format>
#include <string>

MemorySystem::MemorySystem()
{
  cache.Initialise(&mainMemory);
}

MemorySystem::~MemorySystem()
{

}

u32 MemorySystem::Read(u32 address)
{
  return cache.Read(address);
}

void MemorySystem::Write(u32 address, u32 data)
{
  cache.Write(address, data);
}


void MemorySystem::PrintMainMemory()
{
  mainMemory.Print();
}

int main()
{
  MemorySystem memory;

  // Print a slice of the main memory
  memory.PrintMainMemory();

  // Expected: first read should come from main memory (cache miss path)
  u32 data1 = memory.Read(0x20);
  std::cout << std::format("Value: 0x{:x}", data1) << std::endl;

  // Expected: second read should come from cache (cache hit path)
  data1 = memory.Read(0x20);
  std::cout << std::format("Value: 0x{:x}", data1) << std::endl;

  // Expected: write-through to both cache and main memory
  memory.Write(0x20, 0x6139);

  u32 data2 = memory.Read(0x20);

  // Print memory after write to verify updated bytes
  memory.PrintMainMemory();
  
  return 0;
}
