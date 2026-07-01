// FUNC_NAME: SomeClass::setNibbleValue
void __thiscall setNibbleValue(int this, float param_2, char param_3)
{
  uint uVar1;
  byte bVar2;
  undefined4 local_8;
  
  bVar2 = param_3 * 4;  // Nibble shift amount (0, 4, 8, 12, etc.)
  local_8 = (int)(longlong)ROUND(param_2 / *(float *)(this + 0xe4)); // Scale factor at +0xE4
  uVar1 = local_8 + (*(uint *)(this + 0xcc) >> (bVar2 & 0x1f) & 0xf); // Add to existing nibble value at +0xCC
  if (uVar1 < 0x10) {
    if ((uVar1 == 0) && (DAT_00e44598 < param_2)) {
      uVar1 = 1; // Clamp to minimum 1 if param_2 exceeds threshold
    }
  }
  else {
    uVar1 = 0xf; // Clamp to maximum 15
  }
  *(uint *)(this + 0xcc) =
       ~(0xf << (bVar2 & 0x1f)) & *(uint *)(this + 0xcc) | uVar1 << (bVar2 & 0x1f); // Update nibble at +0xCC
  return;
}