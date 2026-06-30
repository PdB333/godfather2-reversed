// FUNC_NAME: AnimationController::updateBlendWeights
undefined4 __fastcall AnimationController::updateBlendWeights(int this)
{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = DAT_01205214;
  if (*(char *)(this + 0xe8) != '\0') {
    *(float *)(this + 0xd0) = DAT_01205214;
    if (*(float *)(this + 0xdc) < fVar3) {
      if (*(char *)(this + 0xe9) != '\0') {
        FUN_006a96e0();
        return 1;
      }
      FUN_006a9510();
      return 1;
    }
    fVar2 = *(float *)(this + 0xdc) - *(float *)(this + 0xc4);
    if (fVar2 <= DAT_00e44598) {
      fVar2 = 0.0;
    }
    else {
      fVar2 = (fVar3 - *(float *)(this + 0xc4)) / fVar2;
    }
    fVar1 = (*(float *)(this + 0xe0) - *(float *)(this + 200)) * fVar2 +
            *(float *)(this + 200);
    fVar3 = DAT_00e44598;
    if (DAT_00e44598 < (float)((uint)(fVar1 - *(float *)(this + 0xd4)) & DAT_00e44680)) {
      FUN_005e6750(*(undefined4 *)(this + 0x88),fVar1);
      FUN_005e6750(*(undefined4 *)(this + 0xa0),fVar1);
      fVar3 = DAT_00e44598;
      *(float *)(this + 0xd4) = fVar1;
    }
    fVar2 = (*(float *)(this + 0xe4) - *(float *)(this + 0xcc)) * fVar2 +
            *(float *)(this + 0xcc);
    if (fVar3 < (float)((uint)(fVar2 - *(float *)(this + 0xd8)) & DAT_00e44680)) {
      FUN_005e6700(*(undefined4 *)(this + 0x88),fVar2);
      FUN_005e6700(*(undefined4 *)(this + 0xa0),fVar2);
      *(float *)(this + 0xd8) = fVar2;
    }
  }
  return 1;
}