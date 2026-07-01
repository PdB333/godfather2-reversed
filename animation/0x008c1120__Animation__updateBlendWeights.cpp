// FUNC_NAME: Animation::updateBlendWeights
void __thiscall Animation::updateBlendWeights(int this, int blendData)
{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = *(undefined4 *)(*(int *)(blendData + 8) + 0x38);
  uVar2 = 0;
  if (*(int *)(blendData + 0x14) != 0) {
    do {
      FUN_008bf280(*(undefined4 *)(*(int *)(blendData + 0x10) + uVar2 * 4), 4, uVar1,
                   *(float *)(this + 0x1e8) + _DAT_00d5780c);
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(blendData + 0x14));
  }
  FUN_006b2ff0(*(undefined4 *)(this + 0x54), *(undefined4 *)(this + 0x1e8));
  return;
}