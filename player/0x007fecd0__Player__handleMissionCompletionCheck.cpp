// FUNC_NAME: Player::handleMissionCompletionCheck
void __fastcall Player::handleMissionCompletionCheck(int thisPtr)
{
  char cVar1;
  undefined4 uVar2;
  int local_4;
  
  if ((*(uint *)(thisPtr + 0x894) >> 2 & 1) != 0) {
    // Clear bit 2 (0x4) of the flags at +0x894
    *(uint *)(thisPtr + 0x894) = *(uint *)(thisPtr + 0x894) & 0xfffffffb;
    local_4 = thisPtr;
    uVar2 = FUN_00445ff0(thisPtr + 0x1b98, 0); // Get some object from offset +0x1b98
    local_4 = 0;
    cVar1 = FUN_004480d0(uVar2, 0x8bd0e0eb, &local_4); // Check mission completion condition
    if ((cVar1 != '\0') && (cVar1 = FUN_00725c30(), cVar1 != '\0')) {
      FUN_00725150(thisPtr + 0x390, thisPtr); // Handle mission completion (offset +0x390 likely a component)
      FUN_00724cb0(0); // Clear some state
    }
  }
  return;
}