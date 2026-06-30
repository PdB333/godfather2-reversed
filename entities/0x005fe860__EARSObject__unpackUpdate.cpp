// FUNC_NAME: EARSObject::unpackUpdate
void __thiscall EARSObject::unpackUpdate(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  uVar1 = 0;
  // Copy position/rotation data (3 floats) from source to destination
  *(undefined4 *)(param_2 + 0x30) = *this;
  *(undefined4 *)(param_2 + 0x34) = this[1];
  *(undefined4 *)(param_2 + 0x38) = this[2];
  
  // Check bit 6 of flags field (offset 0xB4 = 0x2D * 4)
  if (((uint)this[0x2d] >> 6 & 1) == 0) {
    // If bit not set, read velocity from offset 0xF8 (0x3E * 4)
    local_8 = this[0x3e];
  }
  else {
    // If bit set, velocity is zero
    local_8 = 0;
  }
  
  // Check bit 5 of flags field
  if (((uint)this[0x2d] >> 5 & 1) == 0) {
    // If bit not set, read additional data from offsets 0x104 and 0x110 (0x41*4, 0x44*4)
    local_c = this[0x41];
    uVar1 = this[0x44];
  }
  else {
    // If bit set, additional data is zero
    local_c = 0;
  }
  
  // Call unpack helper with velocity and additional data
  FUN_0056b8a0(local_8, local_c, uVar1, param_2);
  return;
}