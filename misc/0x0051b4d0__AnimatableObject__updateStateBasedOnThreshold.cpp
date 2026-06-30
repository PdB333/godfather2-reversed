// FUNC_NAME: AnimatableObject::updateStateBasedOnThreshold
void AnimatableObject::updateStateBasedOnThreshold(int this, float param_2)
{
  short *psVar1;
  float *pfVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  
  iVar6 = this;
  if ((*(uint *)(this + 0xc) & 0x10000) == 0) {
    fVar3 = *(float *)(this + 0x90);
    if ((fVar3 * DAT_00e4483c < param_2) || (param_2 < fVar3 - fVar3 * DAT_00e2b334)) {
      iVar7 = 0;
      psVar1 = (short *)(this + 0x80);
      this = 0;
      if (0 < *psVar1) {
        puVar8 = (uint *)(iVar6 + 0xf0);
        do {
          iVar4 = *(int *)(iVar6 + 0x10);
          if (puVar8[1] != 0) {
            if ((param_2 < *(float *)(iVar4 + 0x48 + iVar7)) ||
               (pfVar2 = (float *)(iVar4 + 0x50 + iVar7), *pfVar2 <= param_2 && param_2 != *pfVar2))
            {
              uVar5 = *puVar8;
              if (((uVar5 & 4) == 0) && ((*(uint *)(iVar4 + 0x14) & 0x1000000) == 0)) {
                *puVar8 = uVar5 | 0x74000000;
                FUN_005343f0();
                puVar8[1] = 0;
              }
              else {
                *puVar8 = uVar5 | 0x200000;
              }
            }
            else {
              *puVar8 = *puVar8 & 0xffdfffff;
            }
          }
          this = this + 1;
          puVar8 = puVar8 + 5;
          iVar7 = iVar7 + 0x24;
        } while (this < *(short *)(iVar6 + 0x80));
      }
      *(float *)(iVar6 + 0x90) = param_2;
    }
    *(float *)(iVar6 + 0x8c) = param_2;
  }
  return;
}