// FUNC_NAME: Player::updateMovementSpeedMultiplier
void __thiscall Player::updateMovementSpeedMultiplier(int this, float deltaTime)
{
  // Check if player is in a vehicle (bit 0xB at offset 0xC88) or in a special state (bit 0xE at offset 0xF28)
  if (((*(uint *)(this + 0xc88) >> 0xb & 1) == 0) &&
     ((*(uint *)(this + 0xf28) >> 0xe & 1) == 0)) {
    // Normal movement: apply acceleration factor (0xF58) over time
    *(float *)(this + 0xf54) = *(float *)(this + 0xf58) * deltaTime;
    return;
  }
  // In vehicle or special state: set speed multiplier directly to deltaTime (no acceleration)
  *(float *)(this + 0xf54) = deltaTime;
  return;
}