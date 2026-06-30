// FUNC_NAME: GameStateManager::updateGameState
void GameStateManager::updateGameState(int param_1)
{
  int desiredState;
  int unaff_ESI; // likely derived from this pointer or register, but undefined in decompiled code

  if ((gGameState != 3) && (gGameState != 4))
  {
    if (unaff_ESI == 0)
    {
      desiredState = 0;
    }
    else if (param_1 == 0)
    {
      desiredState = 1;
    }
    else
    {
      if ((gGameState == 2) || (gGameState == 5) || (gGameState == 6))
        goto LAB_0053b472;
      desiredState = 2;
    }

    if (gGameState != desiredState)
    {
      transitionGameState(gGameManager); // FUN_0053b1e0
    }
  }

LAB_0053b472:
  if (*(int *)(&gSomeArray1 + (uint)gActivePlayerIndex * 0x3c) != 0)
  {
    safeDeletePointer(); // FUN_006063b0
  }
  if (*(int *)(&gSomeArray2 + (uint)gActivePlayerIndex * 0x3c) != 0)
  {
    safeDeletePointer(); // FUN_006063b0
  }
  return;
}