// FUNC_NAME: PlayerF2FSM::updateFinishingMoveSelection
void __thiscall FUN_0080bc40(int thisPtr, undefined4 targetingData)
{
  char isActive;
  int result;
  undefined4 finishingMoveID;
  
  FUN_0046c710(targetingData);
  FUN_0043aff0(targetingData, 0xe40c68d4);
  isActive = FUN_0043b120();
  while (isActive == '\0') {
    FUN_0043b210();
    result = FUN_0043ab70();
    if (result == 0) {
      FUN_0043b210();
      finishingMoveID = FUN_0043ab90();
      FUN_004089b0(thisPtr + 0x50, finishingMoveID); // +0x50 = currentFinishingMove
    }
    else if (result == 1) {
      // +0x58 = some timer/state related to finishing move
      int timerState = thisPtr + 0x58;
      FUN_0043b210(timerState);
      FUN_0043ad10(timerState);
    }
    else if (result == 2) {
      // +0x68 = bool flag for direction (?)
      int iVar2 = FUN_0043b210();
      *(bool *)(thisPtr + 0x68) = *(int *)(iVar2 + 8) != 0;
    }
    FUN_0043b1a0();
    isActive = FUN_0043b120();
  }
  return;
}