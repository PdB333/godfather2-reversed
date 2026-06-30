// FUNC_NAME: TransformHelper::initTransform
void __fastcall TransformHelper::initTransform(const float (*srcMatrix)[4], const float (*srcData)[2], Transform* dest)
{
    // Copy 32 bytes of source data (srcData) into the "rotation/orientation" region at offset 0x10
    // srcData is interpreted as 4 groups of 2 floats (8 floats total)
    *(uint64_t*)(dest + 0x10) = *(uint64_t*)srcData;
    *(uint64_t*)(dest + 0x18) = *(uint64_t*)(srcData + 1);
    *(uint64_t*)(dest + 0x20) = *(uint64_t*)(srcData + 2);
    *(uint64_t*)(dest + 0x28) = *(uint64_t*)(srcData + 3);

    // Set the flag at offset 0xDC to 1 (indicating this transform is initialized)
    *(int*)(dest + 0xDC) = 1;

    if (srcMatrix != nullptr)
    {
        // Copy the 4x4 matrix (16 floats, 64 bytes) from srcMatrix into dest at offset 0x70
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                *(float*)(dest + 0x70 + (i*4 + j)*4) = srcMatrix[i][j];
            }
        }
    }
    else
    {
        // Default: set matrix to identity (diagonal = DAT_00e2b1a4, presumably 1.0f)
        float defaultDiag = *(float*)0x00e2b1a4;  // global constant (likely 1.0f)
        // Set all 16 elements to 0, then diagonal to defaultDiag
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                    *(float*)(dest + 0x70 + (i*4 + j)*4) = defaultDiag;
                else
                    *(float*)(dest + 0x70 + (i*4 + j)*4) = 0.0f;
            }
        }
    }
}