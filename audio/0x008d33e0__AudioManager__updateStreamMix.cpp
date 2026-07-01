// FUNC_NAME: AudioManager::updateStreamMix
void __fastcall AudioManager::updateStreamMix(int this)
{
  int iVar1;
  uint uVar2;
  float fVar3;
  
  if (DAT_00e44598 < *(float *)(this + 0x10)) {
    uVar2 = 0;
    fVar3 = _DAT_00d5780c / *(float *)(this + 0x10);
    if (*(int *)(this + 0x1c) != 0) {
      do {
        FUN_008d5e20(fVar3);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(this + 0x1c));
    }
    iVar1 = 4;
    do {
      FUN_008d5eb0(fVar3);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    FUN_008d5eb0(fVar3);
  }
  return;
}