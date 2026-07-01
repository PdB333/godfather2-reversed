// FUNC_NAME: RewardManager::GetRewardAmount
// Address: 0x0095ca80
// Role: Looks up reward money based on an entity's crime/quest ID hash from a global lookup table.
// Uses two globals: g_rewardTable (array of 8-byte entries, first 4 bytes = hash) and g_rewardTableCount.
// Defaults to 100, returns 3, 5000, or 10000 for specific known hashes.

extern uint* g_rewardTable;       // DAT_011307f8
extern uint  g_rewardTableCount;  // DAT_011307fc

__fastcall uint RewardManager::GetRewardAmount(int thisPtr)
{
  uint result;
  uint index;
  int  hash;

  result = 100;   // default reward

  index = *(uint*)(thisPtr + 0x8);  // entity's lookup index field
  if (index < g_rewardTableCount)
  {
    hash = *(int*)(g_rewardTable + index * 2);  // each entry is 8 bytes: hash then ??? (not used)

    if (hash == 0x3d26cff9)      // "crime_bank_heist" or similar
    {
      result = 10000;
    }
    else if (hash == 0x45c2f636) // "crime_favor" or similar
    {
      result = 3;
    }
    else if (hash == 0x7116917a) // "crime_extortion" or similar
    {
      result = 5000;
    }
  }
  return result;
}