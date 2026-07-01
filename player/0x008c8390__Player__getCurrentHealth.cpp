// FUNC_NAME: Player::getCurrentHealth
undefined4 __fastcall Player::getCurrentHealth(int this)
{
  int iVar1;
  
  if (*(int *)(this + 8) != 0) {
    iVar1 = FUN_0043b870(DAT_01131010);
    return *(undefined4 *)(iVar1 + 0x1c);
  }
  return uRam0000001c;
}