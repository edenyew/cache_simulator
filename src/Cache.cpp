# include "Cache.h"

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
