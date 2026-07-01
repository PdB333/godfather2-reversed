// FUNC_NAME: Player::getHealth
float __fastcall Player::getHealth(int this)
{
  int iVar1;
  
  if (this != 0) {
    iVar1 = FUN_0043b870(DAT_0112af98); // likely getPlayerDataManager or similar
    return *(float *)(iVar1 + 0x38); // +0x38: health value
  }
  return 0.0f;
}