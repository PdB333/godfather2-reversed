// FUNC_NAME: Transform::copyFrom
undefined4 * __thiscall Transform::copyFrom(undefined4 *this, const Transform &other)
{
  // Clone the other's transformation data into this object.
  // Calls base initializer (likely a memset or default constructor).
  FUN_0081f9f0(&other);
  
  // Set vtable pointer for this instance.
  *this = &PTR_LAB_00d7333c; // vtable pointer
  
  // Copy transformation matrix or transform block (88 bytes from offset 0x50 to 0xA4).
  // Offsets relative to structure base:
  // +0x50: translation (3 floats)
  // +0x60: rotation (4 floats, quaternion)
  // +0x70: scale (3 floats)
  // +0x80: extra (4 floats, e.g., shear or second vector)
  // +0x90: extra (6 floats, e.g., third column or extended data)
  // Note: This structure likely represents a 4x3 matrix with additional fields.
  
  // Copy block at +0x50 to +0x5C (translation)
  this[0x14] = *(undefined4 *)(&other + 0x50 / 4);   // +0x50
  this[0x15] = *(undefined4 *)(&other + 0x54 / 4);   // +0x54
  this[0x16] = *(undefined4 *)(&other + 0x58 / 4);   // +0x58
  this[0x17] = *(undefined4 *)(&other + 0x5C / 4);   // +0x5C
  
  // Copy block at +0x60 to +0x6C (rotation quaternion)
  this[0x18] = *(undefined4 *)(&other + 0x60 / 4);   // +0x60
  this[0x19] = *(undefined4 *)(&other + 0x64 / 4);   // +0x64
  this[0x1A] = *(undefined4 *)(&other + 0x68 / 4);   // +0x68
  this[0x1B] = *(undefined4 *)(&other + 0x6C / 4);   // +0x6C
  
  // Copy block at +0x70 to +0x7C (scale)
  this[0x1C] = *(undefined4 *)(&other + 0x70 / 4);   // +0x70
  this[0x1D] = *(undefined4 *)(&other + 0x74 / 4);   // +0x74
  this[0x1E] = *(undefined4 *)(&other + 0x78 / 4);   // +0x78
  this[0x1F] = *(undefined4 *)(&other + 0x7C / 4);   // +0x7C
  
  // Copy block at +0x80 to +0x8C (extra matrix row or shears)
  this[0x20] = *(undefined4 *)(&other + 0x80 / 4);   // +0x80
  this[0x21] = *(undefined4 *)(&other + 0x84 / 4);   // +0x84
  this[0x22] = *(undefined4 *)(&other + 0x88 / 4);   // +0x88
  this[0x23] = *(undefined4 *)(&other + 0x8C / 4);   // +0x8C
  
  // Copy block at +0x90 to +0xA4 (extended data)
  this[0x24] = *(undefined4 *)(&other + 0x90 / 4);   // +0x90
  this[0x25] = *(undefined4 *)(&other + 0x94 / 4);   // +0x94
  this[0x26] = *(undefined4 *)(&other + 0x98 / 4);   // +0x98
  this[0x27] = *(undefined4 *)(&other + 0x9C / 4);   // +0x9C
  this[0x28] = *(undefined4 *)(&other + 0xA0 / 4);   // +0xA0
  this[0x29] = *(undefined4 *)(&other + 0xA4 / 4);   // +0xA4
  
  return this;
}