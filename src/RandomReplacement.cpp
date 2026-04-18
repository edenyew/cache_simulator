#include "RandomReplacement.h"
#include "types.h"

#include <cstdlib>

void RandomReplacement::SetWays(u8 numOfWays)
{
  // Set the number of cache ways
  ways = numOfWays;
}

u8 RandomReplacement::GetToReplace() const
{
  // Choose a random one to replace
  return rand() % ways;
}