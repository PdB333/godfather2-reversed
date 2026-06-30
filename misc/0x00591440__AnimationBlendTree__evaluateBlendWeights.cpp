// FUNC_NAME: AnimationBlendTree::evaluateBlendWeights
void AnimationBlendTree::evaluateBlendWeights(float param_1, int param_2, int *param_3)
{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  float fStack_10;
  float local_c;
  float local_8 [2];
  
  // Check if animation state is not in a special mode (e.g., not in transition)
  if (*(int *)(*(int *)((int)param_1 + 0x7c) + 0x2c) != 2) {
    piVar1 = *(int **)(param_2 + 4);
    iVar2 = *piVar1;
    // Validate index and get blend weight function pointer from global table
    if (((-1 < iVar2) && (iVar2 < DAT_01205574)) &&
       (pcVar3 = *(code **)(DAT_01205570 + 4 + iVar2 * 0xc), pcVar3 != (code *)0x0)) {
      (*pcVar3)(param_1,iVar2,local_8);
    }
    iVar2 = piVar1[1];
    if (((-1 < iVar2) && (iVar2 < DAT_01205574)) &&
       (pcVar3 = *(code **)(DAT_01205570 + 4 + iVar2 * 0xc), pcVar3 != (code *)0x0)) {
      (*pcVar3)(param_1,iVar2,&local_c);
    }
    iVar2 = piVar1[2];
    if (((-1 < iVar2) && (iVar2 < DAT_01205574)) &&
       (pcVar3 = *(code **)(DAT_01205570 + 4 + iVar2 * 0xc), pcVar3 != (code *)0x0)) {
      (*pcVar3)(param_1,iVar2,&fStack_10);
    }
    param_1 = 0.0;
    // Compute blend factor: (middle - low) / (high - low)
    if (0.0 < fStack_10 - local_c) {
      param_1 = (local_8[0] - local_c) / (fStack_10 - local_c);
    }
    uVar4 = piVar1[3];
    // Check if we need to reset the blend buffer
    if ((uint)param_3[1] <= uVar4) {
      local_8[1] = 0.0;
      FUN_00591c00(local_8 + 1);
    }
    // Store computed blend weight into output array
    *(float *)(*param_3 + uVar4 * 4) = param_1;
  }
  return;
}