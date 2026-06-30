// FUNC_NAME: Animation::updateBoneTransforms
uint Animation::updateBoneTransforms(int param_1, int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint in_EAX;
  uint uVar4;
  undefined4 uVar5;
  int *piVar6;
  
  uVar4 = in_EAX & 0xffffff00;
  if ((param_2 != 0) && (param_1 != 0)) {
    bVar1 = *(byte *)(param_2 + 0x6f); // +0x6f: bone count
    for (piVar6 = (int *)(param_2 + 0xc); piVar6 < (int *)(param_2 + 0xc + (uint)bVar1 * 4);
        piVar6 = piVar6 + 1) {
      if ((piVar6 != (int *)0x0) && (iVar3 = *piVar6, iVar3 != 0)) {
        uVar2 = *(undefined1 *)(iVar3 + 0x1c); // +0x1c: bone type/flags
        FUN_005f2680(); // getAnimationData?
        FUN_005dbc10(*(undefined4 *)(param_2 + 0x5c), // +0x5c: animation time
                     (double)*(float *)(param_1 + 0x3c), // +0x3c: blend weight
                     (double)*(float *)(param_2 + 0x50), // +0x50: playback speed
                     (double)*(float *)(param_1 + 0x4c), // +0x4c: blend factor
                     uVar2);
        *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(param_1 + 4); // +0x04: bone transform
        uVar5 = FUN_005f37b0(); // getNextBone?
        FUN_005f1400(uVar5); // applyTransform?
      }
    }
    uVar4 = CONCAT31((int3)((uint)piVar6 >> 8),1);
  }
  return uVar4;
}