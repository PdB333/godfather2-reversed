// FUNC_NAME: EARSObject::applyParentTransform
void __thiscall EARSObject::applyParentTransform(EARSObject *this)
{
  // +0x4: pointer to parent transform source
  // +0x50: 4x4 transform matrix (16 floats)
  float localMatrix[16];

  if (*(int*)((char*)this + 4) != 0) {
    // Copy matrix from source at this+4 into local buffer
    FUN_0044b4e0(localMatrix, *(int*)((char*)this + 4));
    
    // Copy matrix to this's transform (offset 0x50)
    *(float*)((char*)this + 0x50) = localMatrix[0]; // row 0 col 0
    *(float*)((char*)this + 0x54) = localMatrix[1]; // row 0 col 1
    *(float*)((char*)this + 0x58) = localMatrix[2]; // row 0 col 2
    *(float*)((char*)this + 0x5C) = localMatrix[3]; // row 0 col 3 (overwritten to zero)
    *(float*)((char*)this + 0x60) = localMatrix[4]; // row 1 col 0
    *(float*)((char*)this + 0x64) = localMatrix[5]; // row 1 col 1
    *(float*)((char*)this + 0x68) = localMatrix[6]; // row 1 col 2
    *(float*)((char*)this + 0x6C) = localMatrix[7]; // row 1 col 3 (overwritten to zero)
    *(float*)((char*)this + 0x70) = localMatrix[8]; // row 2 col 0
    *(float*)((char*)this + 0x74) = localMatrix[9]; // row 2 col 1
    *(float*)((char*)this + 0x78) = localMatrix[10]; // row 2 col 2
    *(float*)((char*)this + 0x7C) = localMatrix[11]; // row 2 col 3 (overwritten to zero)
    *(float*)((char*)this + 0x80) = localMatrix[12]; // row 3 col 0
    *(float*)((char*)this + 0x84) = localMatrix[13]; // row 3 col 1
    *(float*)((char*)this + 0x88) = localMatrix[14]; // row 3 col 2
    *(float*)((char*)this + 0x8C) = localMatrix[15]; // row 3 col 3 (overwritten by global)

    // Force translation w components to zero and last w to global constant
    // (likely sets affine transform properties)
    *(float*)((char*)this + 0x5C) = 0.0f;   // row 0 translation w
    *(float*)((char*)this + 0x6C) = 0.0f;   // row 1 translation w
    *(float*)((char*)this + 0x7C) = 0.0f;   // row 2 translation w
    *(float*)((char*)this + 0x8C) = DAT_00e2b1a4; // global scale/flag value

    FUN_006101b0(); // Notify transform change
  }
}