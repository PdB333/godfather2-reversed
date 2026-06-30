// FUNC_NAME: Vector4::scaleXYZ
void __fastcall Vector4::scaleXYZ(float *thisVec, float *sourceVec, float scale)
{
  // Scales the X, Y, Z components of a 4-component vector, preserving W
  // +0x00: x, +0x04: y, +0x08: z, +0x0C: w
  
  float srcY = sourceVec[1]; // +0x04
  float srcZ = sourceVec[2]; // +0x08
  float srcW = sourceVec[3]; // +0x0C
  float origW = thisVec[3];  // Preserve original W component

  thisVec[0] = scale * sourceVec[0]; // Scale X
  thisVec[1] = scale * srcY;         // Scale Y
  thisVec[2] = scale * srcZ;         // Scale Z
  thisVec[3] = scale * srcW;         // Temporarily scaled
  thisVec[3] = origW;                // Restore original W (overwrite)
}