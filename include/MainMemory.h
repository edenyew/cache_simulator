#pragma once

#include <memory>
#include "types.h"


const u32 MAIN_MEMORY_SIZE = 4 * 1024 * 1024; // 4MB MAIN MEMORY (8 bits = 1 byte, 32 bits = 4 bytes)

class MainMemory
{
private:
  std::unique_ptr<std::array<u8, MAIN_MEMORY_SIZE>> memory;

public:
  MainMemory();
  ~MainMemory();

  void Read(u32 startAddress, u8 size, u8* destination);
  void Write(u32 startAddress, u8 size, u8* source);
  void Print();
  
};
