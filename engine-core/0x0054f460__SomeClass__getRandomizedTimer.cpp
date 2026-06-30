// FUNC_NAME: SomeClass::getRandomizedTimer
uint __thiscall SomeClass::getRandomizedTimer(int this, float param_2)
{
  float fVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(this + 0xb0); // +0xB0: some timer value
  if (uVar2 != 0) {
    fVar1 = (float)(int)(DAT_01205224 - uVar2); // DAT_01205224: current time
    if ((int)(DAT_01205224 - uVar2) < 0) {
      fVar1 = fVar1 + DAT_00e44578; // DAT_00e44578: time wrap constant (likely 0xFFFFFFFF as float)
    }
    uVar2 = CONCAT31((int3)(uVar2 >> 8),1); // Preserve upper 24 bits, set low byte to 1
    if (param_2 <= fVar1 * DAT_00e2e210) { // DAT_00e2e210: some multiplier
      return uVar2;
    }
  }
  return uVar2 & 0xffffff00; // Clear low byte if condition fails
}