// FUNC_NAME: Player::getNumActiveWeapons
char __fastcall Player::getNumActiveWeapons(int thisPtr)
{
  char count;

  count = *(int *)(thisPtr + 0xa4c) != 0;
  if (*(int *)(thisPtr + 0xa50) != 0) {
    count = count + 1;
  }
  if (*(int *)(thisPtr + 0xa54) != 0) {
    count = count + 1;
  }
  if (*(int *)(thisPtr + 0xa58) != 0) {
    count = count + 1;
  }
  return count;
}