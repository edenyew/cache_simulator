#pragma once

#include "MainMemory.h"
#include "RandomReplacement.h"
#include "types.h"

#include <array>

// total lines = 64 sets * 4 ways = 256 cache lines
// each cache line of size = 64
// memory address = 32

const u8 MEMORY_ADDRESS_SIZE = 32;    // 32-bit memory addresses
const u8 CACHE_LINE_SIZE = 64;        // 64-byte cache lines
const u32 CACHE_SETS = 64;            // Cache with 64 sets
const u8 CACHE_WAYS = 4;              // 4-way set associative cache 

const u8 CACHE_LINE_BYTE_OFFSET_SIZE = 6;
const u8 CACHE_LINE_SET_INDEX_SIZE = 6;
const u8 CACHE_LINE_TAG_SIZE = 20;


struct CacheLine
{
  u32 tag = 0;
  std::array<u8, CACHE_LINE_SIZE> data;
  bool valid = false;
};

class Cache
{

};