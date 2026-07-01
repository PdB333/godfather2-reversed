// FUNC_NAME: Sentient::updateDamageState
int __thiscall Sentient::updateDamageState(int this, int sentientObj)
{
  int damageState;
  
  damageState = FUN_009afa10(sentientObj);
  if ((*(uint *)(sentientObj + 0x44) >> 4 & 1) == 0) {
    if ((damageState == 0) && ((*(int *)(sentientObj + 0x30) == 2 || (*(int *)(sentientObj + 0x30) == 1)))) {
      damageState = 3;
    }
  }
  else {
    damageState = 1;
  }
  if (((*(int *)(sentientObj + 0x30) == 0xb) || ((*(uint *)(sentientObj + 0x44) >> 6 & 1) != 0)) &&
     ((*(uint *)(this + 0x18) >> 7 & 1) == 0)) {
    *(uint *)(sentientObj + 0x44) = *(uint *)(sentientObj + 0x44) | 4;
  }
  return damageState;
}