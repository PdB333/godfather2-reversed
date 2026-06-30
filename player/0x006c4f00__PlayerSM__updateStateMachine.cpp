// FUNC_NAME: PlayerSM::updateStateMachine
void __fastcall PlayerSM::updateStateMachine(int thisPtr)
{
  int stateId;
  
  stateId = thisPtr;
  FUN_006c0c30(&stateId);
  FUN_006c45a0(thisPtr + 0x24c, thisPtr + 0x214, thisPtr + 0x208, *(undefined4 *)(thisPtr + 0x298),
               stateId, thisPtr + 0x238, thisPtr + 0x22c, thisPtr + 0x244);
  return;
}