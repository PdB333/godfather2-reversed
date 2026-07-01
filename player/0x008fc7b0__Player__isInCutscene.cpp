// FUNC_NAME: Player::isInCutscene
bool __fastcall Player::isInCutscene(int thisPtr)
{
  bool result = false;
  int playerData = *(int *)(thisPtr + 0x1c); // +0x1c: mPlayerData pointer
  if (playerData != 0 && *(char *)(playerData + 200) != '\0') { // +0xC8: mIsInCutscene flag
    result = true;
  }
  return result;
}