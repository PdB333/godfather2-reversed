// FUNC_NAME: Animated::initBoneRotations
void Animated::initBoneRotations(void)
{
  // Called with global bone data dictionary and this+0x3c as a hash key
  float localQuats[6]; // local_30, local_2c, local_28, local_20, local_1c, local_18
  FUN_00c0b080(&DAT_011397d0, *(int *)(this + 0x3c), &localQuats);

  // Store 8 bone local quaternions (x,y,z,w) from combinations of the 6 extracted floats
  // Bone 0: (localQuats[0], localQuats[1], localQuats[2], 0)
  *(float *)(this + 0x50) = localQuats[0];  // x
  *(float *)(this + 0x54) = localQuats[1];  // y
  *(float *)(this + 0x58) = localQuats[2];  // z
  *(float *)(this + 0x5c) = 0.0f;           // w

  // Bone 1: (localQuats[0], localQuats[1], localQuats[5], 0)
  *(float *)(this + 0x60) = localQuats[0];
  *(float *)(this + 0x64) = localQuats[1];
  *(float *)(this + 0x68) = localQuats[5];
  *(float *)(this + 0x6c) = 0.0f;

  // Bone 2: (localQuats[3], localQuats[1], localQuats[5], 0)
  *(float *)(this + 0x70) = localQuats[3];
  *(float *)(this + 0x74) = localQuats[1];
  *(float *)(this + 0x78) = localQuats[5];
  *(float *)(this + 0x7c) = 0.0f;

  // Bone 3: (localQuats[3], localQuats[1], localQuats[2], 0)
  *(float *)(this + 0x80) = localQuats[3];
  *(float *)(this + 0x84) = localQuats[1];
  *(float *)(this + 0x88) = localQuats[2];
  *(float *)(this + 0x8c) = 0.0f;

  // Bone 4: (localQuats[0], localQuats[4], localQuats[2], 0)
  *(float *)(this + 0x90) = localQuats[0];
  *(float *)(this + 0x94) = localQuats[4];
  *(float *)(this + 0x98) = localQuats[2];
  *(float *)(this + 0x9c) = 0.0f;

  // Bone 5: (localQuats[0], localQuats[4], localQuats[5], 0)
  *(float *)(this + 0xa0) = localQuats[0];
  *(float *)(this + 0xa4) = localQuats[4];
  *(float *)(this + 0xa8) = localQuats[5];
  *(float *)(this + 0xac) = 0.0f;

  // Bone 6: (localQuats[3], localQuats[4], localQuats[5], 0)
  *(float *)(this + 0xb0) = localQuats[3];
  *(float *)(this + 0xb4) = localQuats[4];
  *(float *)(this + 0xb8) = localQuats[5];
  *(float *)(this + 0xbc) = 0.0f;

  // Bone 7: (localQuats[3], localQuats[4], localQuats[2], 0)
  *(float *)(this + 0xc0) = localQuats[3];
  *(float *)(this + 0xc4) = localQuats[4];
  *(float *)(this + 0xc8) = localQuats[2];
  *(float *)(this + 0xcc) = 0.0f;
}