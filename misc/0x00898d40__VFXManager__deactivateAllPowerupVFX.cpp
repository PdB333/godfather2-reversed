// FUNC_NAME: VFXManager::deactivateAllPowerupVFX
void VFXManager::deactivateAllPowerupVFX(void)
{
  // Deactivate all powerup visual effects (exploder, healer, vest variants)
  FUN_00408240(&DAT_0112eb5c,"deactivate_exploder_vfx");   // +0x0: exploder VFX
  FUN_00408240(&DAT_0112eb64,"deactivate_exploder1_vfx");  // +0x8: exploder variant 1 VFX
  FUN_00408240(&DAT_0112eb84,"deactivate_healer_vfx");     // +0x28: healer VFX
  FUN_00408240(&DAT_0112eb7c,"deactivate_healer1_vfx");    // +0x20: healer variant 1 VFX
  FUN_00408240(&DAT_0112eb74,"deactivate_vest_vfx");       // +0x18: vest VFX
  FUN_00408240(&DAT_0112eb6c,"deactivate_vest1_vfx");      // +0x10: vest variant 1 VFX
  return;
}