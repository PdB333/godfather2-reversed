// FUNC_NAME: CoverState::canTransitionToCoverOrOpenState
undefined1 __fastcall CoverState::canTransitionToCoverOrOpenState(int this)
{
  float *pfVar1;
  int iVar2;
  undefined1 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  uVar3 = 0;
  if ((*(byte *)(this + 0x128) & 1) != 0) { // Check if cover state is active
    if (((*(uint *)(this + 0x128) >> 3 & 1) != 0) && // Check some cover flag (maybe inCover?)
       ((*(uint *)(this + 0x128) >> 10 & 1) == 0)) { // Check another flag (maybe obstacle blocking?)
      pfVar1 = (float *)FUN_00471610(); // Get player transform
      iVar2 = FUN_00471610(); // Get cover target transform
      fVar5 = *(float *)(this + 0xac) - *(float *)(iVar2 + 0x30); // Delta X
      fVar6 = *(float *)(this + 0xb0) - *(float *)(iVar2 + 0x34); // Delta Y
      fVar7 = *(float *)(this + 0xb4) - *(float *)(iVar2 + 0x38); // Delta Z
      if (*(int *)(this + 0x118) == 1) { // Check some mode (maybe peek mode?)
        fVar4 = (DAT_00e44564 - pfVar1[1]) * fVar6 + (DAT_00e44564 - pfVar1[0]) * fVar5 +
                (DAT_00e44564 - pfVar1[2]) * fVar7; // Dot product with negated player forward
      }
      else {
        fVar4 = pfVar1[1] * fVar6 + pfVar1[0] * fVar5 + pfVar1[2] * fVar7; // Dot product with player forward
      }
      if ((0.0 <= fVar4) && // Player is facing the cover
          (DAT_00d6e928 <= fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5)) { // Within some distance threshold
        return 0; // Cannot transition (blocked)
      }
    }
    uVar3 = 1; // Can transition
  }
  return uVar3;
}