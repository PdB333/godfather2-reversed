// FUNC_NAME: Monopoly::findPlayerBySlot
int * __thiscall Monopoly::findPlayerBySlot(int *thisPtr, int playerSlot)
{
  uint numPlayers;
  int *playerDataPtr;
  uint i;
  
  playerDataPtr = *(int **)(*thisPtr + 0x20); // +0x20: pointer to player data array
  numPlayers = *(uint *)(*thisPtr + 0x10);     // +0x10: count of players
  i = 0;
  
  if (numPlayers != 0) {
    do {
      if (*playerDataPtr == playerSlot) {
        return playerDataPtr;
      }
      i = i + 1;
      playerDataPtr = playerDataPtr + 0x17; // Each player record is 0x17 * 4 = 92 bytes
    } while (i < numPlayers);
  }
  return (int *)0x0;
}