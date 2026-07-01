// FUNC_NAME: ComputeAABB
void ComputeAABB(void* entity, int boneIndex, float* outAABB)
{
    float localX, localY, localZ;
    float stackX, stackY, stackZ;
    float bonePositions[10][2]; // Actually 7 bone positions, each as two 4-byte floats packed? But decompiled as 8-byte reads.

    // Get initial position from entity's bone (index 8)
    GetBonePosition(&localX, entity, 8, boneIndex); // FUN_00720980: likely GetBonePosition or similar

    outAABB[0] = localX;   // min.x
    outAABB[1] = stackY;   // min.y (but stackY uninitialized? Actually from GetBonePosition, stackY is set as second component?)
    outAABB[2] = localZ;   // min.z
    outAABB[4] = localX;   // max.x initially same
    outAABB[5] = stackY;   // max.y
    outAABB[6] = localZ;   // max.z

    // Iterate over 7 additional bone positions (likely from array boneIndex+1 to +7)
    int count = 7;
    float* pBone = (float*)bonePositions; // treat as three-float structs
    float minX = localX, minY = stackY, minZ = localZ;
    float maxX = localX, maxY = stackY, maxZ = localZ;

    while (count--) {
        float bx = *pBone;          // first float from 8-byte read (low 32 bits)
        float by = *(pBone + 2);    // second float from 8-byte read (high 32 bits)?? Actually offset is +8 bytes in 12-byte struct
        float bz = *(pBone + 4);    // third float at offset 8? No, decompiler shows fVar2 = *(float*)(puVar3+1) on undefined8*, so it's 8 bytes offset.
        // Reinterpreting: each bone position is 12 bytes (3 floats). First 8 bytes are read as a 64-bit integer then split into two floats.
        // So bx = low 32 bits as float, by = high 32 bits as float, bz = next 4 bytes (offset 8).
        if (bx < minX) minX = bx;
        if (bx > maxX) maxX = bx;
        if (by < minY) minY = by;
        if (by > maxY) maxY = by;
        if (bz < minZ) minZ = bz;
        if (bz > maxZ) maxZ = bz;
        pBone += 3; // advance 12 bytes
    }

    outAABB[0] = minX;
    outAABB[1] = minY;
    outAABB[2] = minZ;
    outAABB[4] = maxX;
    outAABB[5] = maxY;
    outAABB[6] = maxZ;
}