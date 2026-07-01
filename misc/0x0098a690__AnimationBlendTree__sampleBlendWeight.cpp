// FUNC_NAME: AnimationBlendTree::sampleBlendWeight
undefined4 __thiscall AnimationBlendTree::sampleBlendWeight(int this, float blendParam, undefined4 param_3, int *outIndex)
{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  float local_14;
  uint local_10;
  int local_c;
  undefined4 local_8;
  code *local_4;
  
  // +0x4c: maxBlendValue, +0x44: minBlendValue
  blendParam = (*(float *)(this + 0x4c) - *(float *)(this + 0x44)) * blendParam;
  local_10 = 0;
  local_8 = 0;
  local_c = 0;
  FUN_0098a350(&local_10,1);
  iVar1 = local_c;
  fVar4 = 0.0;
  iVar2 = 1;
  local_14 = 0.0;
  if (1 < local_c) {
    do {
      // +0x90: pointer to blend weight array
      fVar3 = (float10)FUN_0098a2a0(*(undefined4 *)(this + 0x90),&local_10,0,iVar2);
      fVar4 = (float)fVar3;
      if ((float10)blendParam < fVar3) {
        if ((fVar4 - local_14) * _DAT_00d5c458 + local_14 <= blendParam) {
          // +0x30: base animation index
          *outIndex = *(int *)(this + 0x30) + iVar2;
        }
        else {
          *outIndex = *(int *)(this + 0x30) + -1 + iVar2;
        }
        goto LAB_0098a786;
      }
      iVar2 = iVar2 + 1;
      local_14 = fVar4;
    } while (iVar2 < iVar1);
  }
  if (blendParam <= fVar4) {
    if (local_10 != 0) {
      (*local_4)(local_10);
    }
    return 0;
  }
  *outIndex = *(int *)(this + 0x30) + iVar1;
LAB_0098a786:
  if (local_10 != 0) {
    (*local_4)(local_10);
  }
  return 1;
}