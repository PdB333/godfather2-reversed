// FUNC_NAME: BoneNode::getTransform
void __thiscall BoneNode::getTransform(float *outMatrix)
{
    // This function extracts a 4x4 transformation matrix from a bone node.
    // The bone node structure (param_1) has:
    // +0x00: int flags (e.g., valid/animation state)
    // +0x06: short typeID (0x25e3 = 9699, possibly a specific bone type like "skin" or "mesh")
    // +0x08: void* data pointer (array of 16 floats, offset for bone data)
    // The output matrix is row-major 4x4 (16 floats).
    
    // Constant for default diagonal value (likely 1.0f)
    float defaultDiagonal = *(float*)0x00e2b1a4;
    
    short nodeType = *(short*)((char*)this + 6);
    if (nodeType != 0x25e3)
    {
        // Not a special bone: copy the inline 16-float block starting at offset 0x08
        // (this->data[0..15] stored directly in the structure)
        float localMatrix[16];
        for (int i = 0; i < 16; i++)
            localMatrix[i] = ((float*)this)[2 + i]; // offset 8 bytes = 2 floats
        FUN_0043a2a0(outMatrix, localMatrix);
        return;
    }
    
    int boneIndex = *(int*)this; // offset 0x00
    if (boneIndex != 0)
    {
        // Bone index is valid: read matrix from an external array
        // this->data[2] is a base pointer, boneIndex is an index into that array
        float *boneArray = (float*)this->data; // offset 0x08
        float *boneMatrix = &boneArray[boneIndex * 16]; // each bone has 16 floats
        FUN_0043a2a0(outMatrix, boneMatrix);
        return;
    }
    
    // No bone data: return identity matrix (with default diagonal)
    // Set all to zero, then place defaultDiagonal at diagonal positions
    for (int i = 0; i < 16; i++)
        outMatrix[i] = 0.0f;
    outMatrix[0] = defaultDiagonal;
    outMatrix[5] = defaultDiagonal;
    outMatrix[10] = defaultDiagonal;
    outMatrix[15] = defaultDiagonal;
}