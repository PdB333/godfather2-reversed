// FUNC_NAME: Matrix4x4::lerp
void __thiscall Matrix4x4::lerp(float *thisResult, float *otherMatrix, float t)
{
  float v0, v1, v2, v3;

  // Interpolate first row (columns 0-3, offsets 0x50-0x5C)
  v0 = otherMatrix[0x15]; // +0x54
  v1 = otherMatrix[0x16]; // +0x58
  v2 = otherMatrix[0x17]; // +0x5C
  thisResult[0x14] = otherMatrix[0x14] * t + thisResult[0x14]; // +0x50
  thisResult[0x15] = v0 * t + thisResult[0x15];
  thisResult[0x16] = v1 * t + thisResult[0x16];
  thisResult[0x17] = v2 * t + thisResult[0x17];

  // Interpolate second row (columns 0-3, offsets 0x60-0x6C)
  v0 = otherMatrix[0x19]; // +0x64
  v1 = otherMatrix[0x1A]; // +0x68
  v2 = otherMatrix[0x1B]; // +0x6C
  thisResult[0x18] = otherMatrix[0x18] * t + thisResult[0x18]; // +0x60
  thisResult[0x19] = v0 * t + thisResult[0x19];
  thisResult[0x1A] = v1 * t + thisResult[0x1A];
  thisResult[0x1B] = v2 * t + thisResult[0x1B];

  // Interpolate third row (columns 0-3, offsets 0x70-0x7C)
  v0 = otherMatrix[0x1D]; // +0x74
  v1 = otherMatrix[0x1E]; // +0x78
  v2 = otherMatrix[0x1F]; // +0x7C
  thisResult[0x1C] = otherMatrix[0x1C] * t + thisResult[0x1C]; // +0x70
  thisResult[0x1D] = v0 * t + thisResult[0x1D];
  thisResult[0x1E] = v1 * t + thisResult[0x1E];
  thisResult[0x1F] = v2 * t + thisResult[0x1F];

  // Interpolate fourth row (columns 0-3, offsets 0x80-0x8C)
  v0 = otherMatrix[0x21]; // +0x84
  v1 = otherMatrix[0x22]; // +0x88
  v2 = otherMatrix[0x23]; // +0x8C
  thisResult[0x20] = otherMatrix[0x20] * t + thisResult[0x20]; // +0x80
  thisResult[0x21] = v0 * t + thisResult[0x21];
  thisResult[0x22] = v1 * t + thisResult[0x22];
  thisResult[0x23] = v2 * t + thisResult[0x23];

  // Interpolate translation components (offsets 0x90-0x98)
  thisResult[0x24] = otherMatrix[0x24] * t + thisResult[0x24]; // +0x90
  thisResult[0x25] = otherMatrix[0x25] * t + thisResult[0x25]; // +0x94
  thisResult[0x26] = otherMatrix[0x26] * t + thisResult[0x26]; // +0x98

  // Interpolate scale components (offsets 0xA0-0xA4)
  thisResult[0x28] = otherMatrix[0x28] * t + thisResult[0x28]; // +0xA0
  thisResult[0x29] = otherMatrix[0x29] * t + thisResult[0x29]; // +0xA4
}