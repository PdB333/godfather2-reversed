// FUNC_NAME: AnimBoneSlot::getBoneTransform
// Address: 0x0042a5a0
// Role: Retrieves per-bone transformation data from a skeleton container and writes to output buffers.
// The function expects the bone index to be stored at this+0x2a, then reads three parallel arrays
// from the skeleton structure (passed in param_2 / EDX):
//   skeleton+0x4  : array of 16-byte elements (local translation/rotation vectors, 4 floats)
//   skeleton+0xc  : array of 2-byte elements (parent bone indices)
//   skeleton+0x10 : array of 32-byte elements (world matrices or other per-bone data)
// It copies a vector (4 dwords) to outVec, a short to outParentIndex, and a dword to outExtraData.
// Additionally, it writes one dword from the 32-byte array to the location pointed by EDI (caller must set).

void __fastcall AnimBoneSlot::getBoneTransform(void* thisPtr,       // ECX assumed, but actually used from EAX
                                                struct SkeletonData* skeleton, // EDX
                                                uint* outVec,        // stack: param_3, 4 dwords = 16 bytes
                                                ushort* outParentIndex, // stack: param_4, 2 bytes
                                                uint* outExtraData)  // stack: param_5, 4 bytes
{
    // thisPtr+0x2a : short bone index
    int boneIndex = *(short*)((int)thisPtr + 0x2a);
    if (boneIndex >= 0)
    {
        // EDI pointer used implicitly – caller must have set EDI to a writable location
        // Read a dword from skeleton's 32-byte element (offset 0xc)
        // skeleton+0x10 : pointer to array of 32-byte structures
        *unaff_EDI = *(uint*)(*(int*)(skeleton + 0x10) + 0xc + boneIndex * 0x20);

        // Copy 16 bytes from skeleton's 16-byte array (local transform vector)
        // skeleton+0x4 : pointer to array of 16-byte elements
        uint* srcVec = (uint*)(*(int*)(skeleton + 4) + boneIndex * 0x10);
        outVec[0] = srcVec[0];
        outVec[1] = srcVec[1];
        outVec[2] = srcVec[2];
        outVec[3] = srcVec[3];

        // Read parent bone index from skeleton+0xc array of shorts
        // skeleton+0xc : pointer to array of 2-byte elements
        *outParentIndex = *(ushort*)(*(int*)(skeleton + 0xc) + boneIndex * 2);

        // Read extra dword from the 32-byte array at offset 0x1c
        *outExtraData = *(uint*)(*(int*)(skeleton + 0x10) + 0x1c + boneIndex * 0x20);
    }
    // If boneIndex < 0, no operation
}