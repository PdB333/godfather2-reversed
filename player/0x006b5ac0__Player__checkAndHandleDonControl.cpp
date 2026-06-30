// FUNC_NAME: Player::checkAndHandleDonControl
void __fastcall Player::checkAndHandleDonControl(int thisPtr)
{
  int iVar1;
  
  if ((((*(byte *)(thisPtr + 0x34) & 1) != 0) &&
      (*(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) & 0xfffffffe,
      (*(byte *)(thisPtr + 0x34) & 1) == 0) && (*(int *)(thisPtr + 0x40) != 0)) {
    // +0x34: flags (bit 0 = don control active)
    // +0x40: pointer to don control manager or related entity
    iVar1 = FUN_008c74d0(*(int *)(thisPtr + 0x40));
    if ((iVar1 != 0) && ((~(byte)(*(uint *)(iVar1 + 0x84) >> 5) & 1) != 0)) {
      // +0x84: some state flags (bit 5 = something preventing don control)
      FUN_006b5170(); // likely Player::handleDonControlInput or similar
      return;
    }
  }
  return;
}