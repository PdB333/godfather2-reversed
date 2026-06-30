// FUNC_NAME: EARSObject::setWorldTransform
void __thiscall EARSObject::setWorldTransform(float *param_2)
{
  // Check if transform data is provided
  if (param_2 != (float *)0x0) {
    // Mark that we have a valid world transform (bit 0x10 = 4th bit)
    *(uint *)(this + 8) = *(uint *)(this + 8) | 0x10;
    // Copy 16 floats (4x4 matrix) from param_2 to this+0x60
    *(float *)(this + 0x60) = param_2[0];
    *(float *)(this + 0x64) = param_2[1];
    *(float *)(this + 0x68) = param_2[2];
    *(float *)(this + 0x6c) = param_2[3];
    *(float *)(this + 0x70) = param_2[4];
    *(float *)(this + 0x74) = param_2[5];
    *(float *)(this + 0x78) = param_2[6];
    *(float *)(this + 0x7c) = param_2[7];
    *(float *)(this + 0x80) = param_2[8];
    *(float *)(this + 0x84) = param_2[9];
    *(float *)(this + 0x88) = param_2[10];
    *(float *)(this + 0x8c) = param_2[11];
    *(float *)(this + 0x90) = param_2[12];
    *(float *)(this + 0x94) = param_2[13];
    *(float *)(this + 0x98) = param_2[14];
    *(float *)(this + 0x9c) = param_2[15];
    return;
  }
  // If null, clear the valid flag
  *(uint *)(this + 8) = *(uint *)(this + 8) & 0xffffffef;
  return;
}