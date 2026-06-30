// FUNC_NAME: Matrix4x4::setFromFloatArray
void __thiscall Matrix4x4::setFromFloatArray(float *this, float *src)
{
  // Copy 4x4 matrix from src to this (16 floats)
  // Offsets: +0x40 to +0x7C store the 4x4 matrix as 16 floats
  this[0x10] = src[0];   // +0x40
  this[0x11] = src[1];   // +0x44
  this[0x12] = src[2];   // +0x48
  this[0x13] = src[3];   // +0x4C
  this[0x14] = src[4];   // +0x50
  this[0x15] = src[5];   // +0x54
  this[0x16] = src[6];   // +0x58
  this[0x17] = src[7];   // +0x5C
  this[0x18] = src[8];   // +0x60
  this[0x19] = src[9];   // +0x64
  this[0x1A] = src[10];  // +0x68
  this[0x1B] = src[11];  // +0x6C
  this[0x1C] = src[12];  // +0x70
  this[0x1D] = src[13];  // +0x74
  this[0x1E] = src[14];  // +0x78
  this[0x1F] = src[15];  // +0x7C

  // Zero out the translation column (column 3, rows 0-2)
  this[0x13] = 0.0f;     // +0x4C
  this[0x17] = 0.0f;     // +0x5C
  this[0x1B] = 0.0f;     // +0x6C

  // Set the last element (homogeneous coordinate) from global constant
  this[0x1F] = DAT_00e2b1a4; // +0x7C

  FUN_006101b0(); // Likely matrix normalization or identity check
}