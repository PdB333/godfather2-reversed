// FUNC_NAME: Player::handleCameraShake
void __thiscall Player::handleCameraShake(int this, undefined4 *param_2)
{
  float fVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined8 uStack_18;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar3 = (**(code **)*param_2)();
  if (iVar3 == 0x27a0f69c) {
    iVar3 = FUN_00471610(); // Get player's camera manager
    bVar2 = false;
    if ((*(int *)(this + 0x5c) == 0) || (*(int *)(this + 0x5c) == 0x48)) {
      iVar4 = FUN_00471610(); // Get camera manager
      uStack_18 = *(undefined8 *)(iVar4 + 0x20); // Camera offset XZ
      fStack_10 = *(float *)(iVar4 + 0x28); // Camera offset Y
    }
    else {
      iVar4 = FUN_00471610(); // Get camera manager
      uStack_18 = *(undefined8 *)(iVar4 + 0x20); // Camera offset XZ
      fStack_10 = *(float *)(iVar4 + 0x28); // Camera offset Y
      bVar2 = true; // Flip flag for certain states
    }
    fVar1 = *(float *)(*(int *)(this + 0x50) + 0x1ec0); // Shake intensity from player data
    fStack_c = (float)uStack_18 * fVar1 + *(float *)(iVar3 + 0x30); // Apply shake to X
    fStack_8 = uStack_18._4_4_ * fVar1 + *(float *)(iVar3 + 0x34); // Apply shake to Z
    fStack_4 = fStack_10 * fVar1 + *(float *)(iVar3 + 0x38); // Apply shake to Y
    if (bVar2) {
      fStack_10 = DAT_00e44564 - fStack_10; // Invert Y for certain states
      uStack_18 = CONCAT44(DAT_00e44564 - uStack_18._4_4_,DAT_00e44564 - (float)uStack_18); // Invert XZ
    }
    FUN_00754d30(&fStack_c, &uStack_18, 1, _DAT_00d64c8c, 0, 1); // Apply camera shake offset
    *(undefined4 *)(*(int *)(this + 0x50) + 0x1ec0) = 0; // Reset shake intensity
  }
  return;
}