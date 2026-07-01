// FUNC_NAME: Player::updateGameplayState
void __fastcall Player::updateGameplayState(int this)
{
  char cVar1;
  
  FUN_0087a9b0(); // likely Player::updateBaseState or similar
  if ((((*(uint *)(this + 0xc88) >> 2 & 1) == 0) && (**(int **)(DAT_012233a0 + 4) != 0)) &&
     (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
    cVar1 = FUN_007f47a0(); // likely some condition check
    if (cVar1 == '\0') {
      FUN_004088c0(this + 0x3c); // likely Player::updateMovement or similar
    }
  }
  return;
}