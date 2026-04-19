#pragma once

#include "MainMemory.h"
#include "Cache.h"
#include "types.h"

class MemorySystem
{
public:
  MemorySystem();
  ~MemorySystem();

  u32 Read(u32 address);
  void Write(u32 address, u32 data);
  void PrintMainMemory();

private:
  MainMemory mainMemory;
  Cache cache;
};