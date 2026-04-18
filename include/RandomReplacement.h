#pragma once

#include "types.h"
#include <cstdint>


class RandomReplacement
{
public:
  void SetWays(u8 numOfWays);
  u8 GetToReplace() const;

private:
  u8 ways = 0; // Number of ways in the cache

};