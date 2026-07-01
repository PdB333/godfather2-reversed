// FUNC_NAME: ChaseCamera::updateDesiredOffset
undefined4 * ChaseCamera::updateDesiredOffset(undefined4 *this, int param_2, int param_3)

{
  FUN_008334a0(); // likely ChaseCamera::constructor or base class init
  this[0x13] = 0; // +0x4C: desiredOffset (float)
  *this = &PTR_LAB_00d73448; // vtable pointer
  this[0x13] = *(float *)(param_2 + 0x4c) - *(float *)(param_3 + 0x4c); // +0x4C: target position Z difference
  return this;
}