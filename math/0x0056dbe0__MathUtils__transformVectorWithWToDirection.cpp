// FUNC_NAME: MathUtils::transformVectorWithWToDirection
void MathUtils::transformVectorWithWToDirection(int source, int dest)
{
  // Call base transformation function (likely applies a matrix multiply or similar)
  FUN_0056d530(source, dest);

  // Copy 4-component vector from source at +0x30 to dest at +0x10
  // Source vector layout: +0x30 = x, +0x34 = y, +0x38 = z, +0x3c = w
  // Dest vector layout:   +0x10 = x, +0x14 = y, +0x18 = z, +0x1c = w
  *(float *)(dest + 0x10) = *(float *)(source + 0x30);  // x
  *(float *)(dest + 0x14) = *(float *)(source + 0x34);  // y
  *(float *)(dest + 0x18) = *(float *)(source + 0x38);  // z
  *(float *)(dest + 0x1c) = *(float *)(source + 0x3c);  // w

  // Force w component to 0 (convert to direction vector – discard translation)
  *(float *)(dest + 0x1c) = 0.0f;
}