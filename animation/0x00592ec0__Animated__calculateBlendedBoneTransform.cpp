// FUNC_NAME: Animated::calculateBlendedBoneTransform

int __thiscall Animated::calculateBlendedBoneTransform(
    Animated *this,
    float *outPos,
    float param_3,
    float param_4,
    float param_5
)
{
    float scaleFactor;
    uint flags;
    int result;
    Quaternion identityQuat1;  // local_b0
    Quaternion identityQuat2;  // local_a0
    Quaternion quatBlendA;     // local_90
    Quaternion quatBlendB;     // local_70
    Quaternion quatSource1;    // local_50
    Quaternion quatTemp1;      // local_30
    Quaternion quatTemp2;      // local_20
    BoneID boneIndex;          // local_dc
    Matrix4x4 matInput;        // local_c4 (assumed 4x4)
    Matrix4x4 matBlend;        // local_d8

    // Initialize two identity quaternions
    identityQuat1.x = 0.0f;
    identityQuat1.y = 0.0f;
    identityQuat1.z = 0.0f;
    identityQuat1.w = *(float *)&DAT_00e2b1a4;  // likely 1.0f
    identityQuat2.x = 0.0f;
    identityQuat2.y = 0.0f;
    identityQuat2.z = 0.0f;
    identityQuat2.w = *(float *)&DAT_00e2b1a4;

    // Process flags and extract bone index from in_EAX
    boneIndex = (flags >> 5) & 0xFF;  // assumed from in_EAX
    boneIndex &= 0xFFFFFF01;

    // Reset input matrices
    memset(&matInput, 0, sizeof(matInput));
    memset(&matBlend, 0, sizeof(matBlend));

    // Convert param_5 to time (or rotation?) and reset quaternion
    FUN_00593910(param_5);  // assume conversion
    FUN_00593210(&identityQuat1, 0);

    // If bit is set, use secondary bone data
    if ((flags >> 5) & 1)
    {
        int boneDataPtr = this->boneDataPtr;  // param_1[1]
        quatTemp1 = identityQuat1;
        quatTemp2 = identityQuat2;

        // Choose source based on bone count
        if ((*(uint8 *)(boneDataPtr + 4) & 0xFF) < 10)
            boneIndex = *(int *)(boneDataPtr + 0xC);
        else
            boneIndex = *(int *)(boneDataPtr + 0x20);

        result = FUN_00586df0(&quatSource1, boneIndex);
        if (result == 0)
            return 0;
    }

    // Get two bone transforms from matrices
    result = FUN_005934f0(&quatBlendB, &matInput);  // first blend
    if ((result != 0) && 
        (result = FUN_005934f0(&quatBlendA, &matBlend), result != 0))
    {
        // Apply the final transformation
        FUN_00586fa0(outPos, &quatSource1, boneIndex);

        // Apply global scale if set
        if (this->basePtr != nullptr)
        {
            scaleFactor = *(float *)(this->basePtr + 0x104);
            if (scaleFactor != *(float *)&DAT_00e2b1a4)
            {
                outPos[4] *= scaleFactor;   // offset 0x10
                outPos[5] *= scaleFactor;   // offset 0x14
                outPos[6] *= scaleFactor;   // offset 0x18
            }
        }
        return outPos;
    }
    return 0;
}