// FUNC_NAME: AudioDataManager::findInsertionIndex
uint __fastcall AudioDataManager::findInsertionIndex(int param_1)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(int *)(param_1 + 4) + 2; // +0x04: count of sorted entries
  uVar1 = 0;
  if (*(uint *)(param_1 + 8) < uVar3) { // +0x08: capacity
    uVar3 = *(uint *)(param_1 + 8);
  }
  uVar2 = DAT_012054b4; // global iteration counter
  if (3 < (int)uVar3) {
    do {
      // Compare against sorted array at DAT_010c2680, indexed by DAT_010c2678 mask
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar2) * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar2) * 4)) {
        DAT_012054b4 = uVar2 + 1;
        return uVar1;
      }
      DAT_012054b4 = uVar2 + 2;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar2 + 1) * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar2 + 1) * 4)) {
        return uVar1 + 1;
      }
      DAT_012054b4 = uVar2 + 3;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar2 + 2) * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + (DAT_010c2678 & uVar2 + 2) * 4)) {
        return uVar1 + 2;
      }
      uVar2 = uVar2 + 4;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4)
          || *(float *)(param_1 + 0xc) ==
             *(float *)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4)) {
        DAT_012054b4 = uVar2;
        return uVar1 + 3;
      }
      uVar1 = uVar1 + 4;
      DAT_012054b4 = uVar2;
    } while (uVar1 < uVar3 - 3);
  }
  if (uVar1 < uVar3) {
    while( true ) {
      uVar2 = DAT_010c2678 & DAT_012054b4;
      DAT_012054b4 = DAT_012054b4 + 1;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + uVar2 * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + uVar2 * 4)) break;
      uVar1 = uVar1 + 1;
      if (uVar3 <= uVar1) {
        return uVar1;
      }
    }
  }
  return uVar1;
}