// FUNC_NAME: PlayerHealthComponent::applyDamage
void __thiscall PlayerHealthComponent::applyDamage(int this, uint damageAmount)
{
  float fVar1;
  float fVar2;
  
  if (damageAmount <= *(uint *)(this + 0x13c)) {
    // Subtract damage from current health
    *(uint *)(this + 0x13c) = *(uint *)(this + 0x13c) - damageAmount;
    
    // Get damage multiplier from weapon data if available
    if (*(int *)(this + 0x1d0) == 0) {
      fVar1 = 0.0;
    }
    else {
      // +0x58 is weapon damage multiplier, +0x188 is player damage resistance
      fVar1 = *(float *)(*(int *)(this + 0x1d0) + 0x58) * *(float *)(this + 0x188);
    }
    
    fVar2 = (float)(int)damageAmount;
    if ((int)damageAmount < 0) {
      fVar2 = fVar2 + DAT_00e44578; // Handle negative damage (healing)
    }
    
    // Apply damage to health bar UI if present
    if (*(int *)(this + 0x230) != 0) {
      FUN_00892490(fVar2 * fVar1, 6); // Update health bar with damage value
    }
    
    // Clamp health value between min and max
    fVar2 = *(float *)(this + 0x104) + fVar2 * fVar1;
    fVar1 = DAT_00d7bcac; // Minimum health
    if ((fVar2 <= DAT_00d7bcac) || (fVar1 = DAT_00d7bca8, DAT_00d7bca8 <= fVar2)) {
      fVar2 = fVar1;
    }
    *(float *)(this + 0x104) = fVar2; // Update current health value
  }
  return;
}