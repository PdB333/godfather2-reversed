// FUNC_NAME: Player::updateSomething
void __fastcall Player::updateSomething(int thisPtr)
{
  int iVar1;
  
  if ((*(int *)(thisPtr + 0x234) != 0) && ((*(uint *)(thisPtr + 0x25c) >> 4 & 1) != 0)) {
    iVar1 = FUN_006b0ee0(*(int *)(thisPtr + 0x234));
    if ((iVar1 != 0) && ((~(byte)(*(uint *)(iVar1 + 0x34) >> 0x16) & 1) == 0)) {
      *(uint *)(thisPtr + 0x25c) = *(uint *)(thisPtr + 0x25c) & 0xffffffdf;
      goto LAB_008d9cc8;
    }
  }
  *(uint *)(thisPtr + 0x25c) = *(uint *)(thisPtr + 0x25c) | 0x20;
LAB_008d9cc8:
  if (((*(uint *)(thisPtr + 0x25c) >> 5 & 1) != 0) && (*(char *)(thisPtr + 0x180) != '\0')) {
    FUN_008d9ba0();
    return;
  }
  if (*(int *)(thisPtr + 0x200) != 0) {
    FUN_004df600();
    return;
  }
  return;
}