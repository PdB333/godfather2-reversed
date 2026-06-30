// FUNC_NAME: CollisionQuery::testSegment
void __thiscall CollisionQuery::testSegment(int thisPtr, float* offsetArray, undefined4 param3, int param4)
{
    uint result;
    float point1[4];
    float point2[4];
    float unused1, unused2; // local_20, local_1c

    // Clear result flag
    *(uint*)(thisPtr + 0x38) = 0;

    // Check if query function pointer is valid
    if (*(code**)(thisPtr + 0x40) != (code*)0x0)
    {
        // Unused values from offsetArray[8..9]
        unused1 = offsetArray[8];
        unused2 = offsetArray[9];

        // Compute first point: position + offset[0..3]
        point1[0] = *(float*)(thisPtr + 0x20) + offsetArray[0];
        point1[1] = *(float*)(thisPtr + 0x24) + offsetArray[1];
        point1[2] = *(float*)(thisPtr + 0x28) + offsetArray[2];
        point1[3] = *(float*)(thisPtr + 0x2C) + offsetArray[3];

        // Compute second point: position + offset[4..7]
        point2[0] = *(float*)(thisPtr + 0x20) + offsetArray[4];
        point2[1] = *(float*)(thisPtr + 0x24) + offsetArray[5];
        point2[2] = *(float*)(thisPtr + 0x28) + offsetArray[6];
        point2[3] = *(float*)(thisPtr + 0x2C) + offsetArray[7];

        // Call collision query function
        // Signature: uint (*)(void* world, float* segmentPoints, uint flags, void* userData)
        result = (**(code**)(thisPtr + 0x40))(
            *(void**)(thisPtr + 0x34),  // collision world
            point1,                     // pointer to 8 floats (two points)
            *(uint*)(param4 + 4),       // collision flags/mask
            *(void**)(thisPtr + 0x44)   // user data
        );

        // Store inverted result (0 = no collision, non-zero = collision)
        *(uint*)(thisPtr + 0x38) = ~result;

        // If collision detected, process it
        if (result != 0)
        {
            processCollisionResult();  // FUN_00557e20
            applyCollisionEffect(offsetArray, param3, param4);  // FUN_00a73130
        }
    }

    // Clear result flag again (in case no collision or after processing)
    *(uint*)(thisPtr + 0x38) = 0;
}