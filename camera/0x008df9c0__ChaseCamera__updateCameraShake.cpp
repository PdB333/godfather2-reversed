// FUNC_NAME: ChaseCamera::updateCameraShake
void __thiscall ChaseCamera::updateCameraShake(int this, int param_2)
{
  undefined4 uVar1;
  float10 fVar2;
  
  if (param_2 == 0) {
    if (*(int *)(this + 0x22c) != 2) goto LAB_008df9d5;
LAB_008dfa04:
    fVar2 = (float10)FUN_008dab60(); // getRandomFloat or similar
    FUN_008de620(DAT_00e44564 - *(float *)(this + 0x234),(float)-fVar2); // applyShakeOffset
    if (*(int *)(this + 0x230) != -1) goto LAB_008df9e8;
    uVar1 = *(undefined4 *)(this + 0x238); // shakeIntensity or duration
  }
  else {
    if ((param_2 == 1) && (*(int *)(this + 0x22c) == 0)) goto LAB_008dfa04;
LAB_008df9d5:
    uVar1 = 0x3f800000; // 1.0f
  }
  FUN_008de6b0(uVar1); // setShakeIntensity
LAB_008df9e8:
  FUN_008de5a0(1); // updateShakeTimer or similar
  return;
}