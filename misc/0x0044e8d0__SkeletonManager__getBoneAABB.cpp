// FUNC_NAME: SkeletonManager::getBoneAABB

// Reconstructed from 0x0044e8d0: Computes axis-aligned bounding box for a bone
// Uses thread-local storage (FS:[0x2c]) to access global skeleton data arrays.
// param_1: bone index
// in_EAX: pointer to output BoneAABB structure (set by caller)
// Skeleton data layout:
//   pBonePositions = gpSkeletonData + 0x30   // array of vec3
//   pBoneRadii    = gpSkeletonData + 0x70   // array of float
// The resulting AABB is defined as [center - radius, center + radius].

struct BoneAABB {
    float pad0[1];        // +0x00 (unused, likely for alignment)
    float radius;         // +0x04
    float pad1[2];        // +0x08 to +0x0F (alignment)
    float center[3];      // +0x10
    float pad2;           // +0x1C (zeroed)
    float min[3];         // +0x20 (center - radius)
    float pad3;           // +0x2C (zeroed)
    float max[3];         // +0x30 (center + radius)
    float pad4;           // +0x3C (zeroed)
};

//-----------------------------------------------------------------------------
// Accessor for global skeleton data via TLS. Typical EARS engine pattern.
//-----------------------------------------------------------------------------
inline void* getSkeletonDataPointer() {
    // FS:[0x2c] -> pointer to thread-local storage -> deref -> +8 -> skeletal data array
    return *(void**)(*(uint32_t*)(*(uint32_t*)(__readfsdword(0x2c)) + 8));
}

void __fastcall SkeletonManager::getBoneAABB(uint32_t boneIndex, BoneAABB* outBox) {
    // Get base of skeleton data arrays (positions + radii)
    uint8_t* pSkelData = (uint8_t*)getSkeletonDataPointer();

    // Read bone position (vec3 at offset 0x30 + boneIndex*12)
    float* pBonePos = (float*)(pSkelData + 0x30 + boneIndex * 12);
    float posX = pBonePos[0];
    float posY = pBonePos[1];
    float posZ = pBonePos[2];

    // Read bone radius (float at offset 0x70 + boneIndex*4)
    float radius = *(float*)(pSkelData + 0x70 + boneIndex * 4);

    // Fill output structure
    outBox->center[0] = posX;
    outBox->center[1] = posY;
    outBox->center[2] = posZ;
    outBox->pad2 = 0.0f;                                  // +0x1C

    outBox->radius = radius;                               // +0x04

    outBox->max[0] = posX + radius;                        // +0x30
    outBox->max[1] = posY + radius;                        // +0x34
    outBox->max[2] = posZ + radius;                        // +0x38
    outBox->pad4 = 0.0f;                                   // +0x3C

    outBox->min[0] = posX - radius;                        // +0x20
    outBox->min[1] = posY - radius;                        // +0x24
    outBox->min[2] = posZ - radius;                        // +0x28
    outBox->pad3 = 0.0f;                                   // +0x2C
}