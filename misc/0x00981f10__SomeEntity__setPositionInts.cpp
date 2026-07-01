// FUNC_NAME: SomeEntity::setPositionInts
void __thiscall SomeEntity::setPositionInts(uint *this, int x, int y)
{
  float fVar1;
  
  fVar1 = (float)x;
  *this = *this | 8; // Set some flag (e.g., position dirty flag)
  if (x < 0) {
    fVar1 = fVar1 + DAT_00e44578; // Handle negative values (likely 2^32 as float)
  }
  this[9] = (uint)fVar1; // +0x24: x position stored as uint (converted from float)
  fVar1 = (float)y;
  if (y < 0) {
    fVar1 = fVar1 + DAT_00e44578;
  }
  this[10] = (uint)fVar1; // +0x28: y position stored as uint
  return;
}