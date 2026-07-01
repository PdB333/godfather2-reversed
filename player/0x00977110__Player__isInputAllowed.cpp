// FUNC_NAME: Player::isInputAllowed
undefined4 __fastcall Player::isInputAllowed(int this)
{
  char cVar1;
  
  cVar1 = FUN_00956e00(); // likely Player::isAlive or similar
  if ((cVar1 != '\0') && ((*(uint *)(this + 0x60) >> 3 & 1) == 0)) {
    return 0;
  }
  return 1;
}