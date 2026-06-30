// FUNC_NAME: DataBlock::setFromSourceAndExtras
void __thiscall DataBlock::setFromSourceAndExtras(int* this, int* src, int extraA, int extraB)
{
  // Copy first 4 32-bit values from source structure
  this[0] = src[0];
  this[1] = src[1];
  this[2] = src[2];
  this[3] = src[3];
  // Set additional fields (note: swapped parameter order)
  this[4] = extraB;  // +0x10 originally param_3
  this[5] = extraA;  // +0x14 originally param_2
}