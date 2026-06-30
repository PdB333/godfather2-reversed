// FUNC_NAME: VFX::DrawWorldSpaceEffect
void __fastcall VFX::DrawWorldSpaceEffect(void* unusedThis, void* entity, undefined4 param3, undefined4 param4)
{
  // entity points to an object with sub-pointers at +0x14 and +0x18
  // +0x14: pointer to transform chain: +0x30 -> pointer to matrix? -> +0x18 -> final transform
  int transform = *(int*)(*(int*)(*(int*)((int)entity + 0x14) + 0x30) + 0x18);
  
  // Read world position (vec3) from transform at offsets 0x30, 0x34, 0x38
  undefined4 localPosX = *(undefined4*)(transform + 0x30);
  undefined4 localPosY = *(undefined4*)(transform + 0x34);
  undefined4 localPosZ = *(undefined4*)(transform + 0x38);
  
  // +0x18: pointer to effect descriptor, +0x2c: bitfield encoding transformation ID
  uint bitfield = *(uint*)(*(int*)((int)entity + 0x18) + 0x2c);
  
  // Decode the bitfield top two bits to get the actual transformation ID
  uint topBits = bitfield & 0xC0000000;
  int transformId;
  if (topBits == 0) {
    // 00: bit index (shift right 5, mask 5 bits)
    transformId = 1 << ((byte)(bitfield >> 5) & 0x1f);
  }
  else if (topBits == 0x40000000) {
    // 01: table lookup at base 8
    transformId = *(int*)(bitfield * 4 + 8);
  }
  else if (topBits == 0xC0000000) {
    // 11: table lookup at base 0x54
    transformId = *(int*)(bitfield * 4 + 0x54);
  }
  else {
    // 10: error sentinel
    transformId = -0x80000000;
  }
  
  // Call the actual rendering function with the position, parameters, and transform ID
  FUN_0054ebf0(&localPosX, param3, param4, transformId, 0, 0, 0, 0, 0);
  return;
}