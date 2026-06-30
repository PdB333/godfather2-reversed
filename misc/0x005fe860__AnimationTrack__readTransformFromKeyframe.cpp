// FUNC_NAME: AnimationTrack::readTransformFromKeyframe
void __thiscall AnimationTrack::readTransformFromKeyframe(uint* keyframeData, float* outMatrix)
{
    // Offsets are in bytes relative to keyframeData.
    // Assume keyframeData points to a packed keyframe structure.
    // outMatrix is a 4x4 or 3x4 matrix (first 3 rows as rotation? Actually only 12 bytes copied).
    // Copy rotation matrix columns/rows from offsets 0, 4, 8 to outMatrix+0x30, +0x34, +0x38
    *(float*)((char*)outMatrix + 0x30) = (float)keyframeData[0];   // offset 0x00
    *(float*)((char*)outMatrix + 0x34) = (float)keyframeData[1];   // offset 0x04
    *(float*)((char*)outMatrix + 0x38) = (float)keyframeData[2];   // offset 0x08

    float transX, transY, transZ;
    uint32_t flags = keyframeData[0x2d];  // offset 0xB4

    // Bit6: if set, translation X is zero; else read from keyframeData[0x3e] (offset 0xF8)
    if ((flags >> 6) & 1)
        transX = 0.0f;
    else
        transX = *(float*)&keyframeData[0x3e];  // offset 0xF8

    // Bit5: if set, translation Y and Z are zero; else read from keyframeData[0x41] and [0x44] (offsets 0x104 and 0x110)
    if ((flags >> 5) & 1)
    {
        transY = 0.0f;
        transZ = 0.0f;
    }
    else
    {
        transY = *(float*)&keyframeData[0x41];  // offset 0x104
        transZ = *(float*)&keyframeData[0x44];  // offset 0x110
    }

    // Apply translation to the output matrix (likely combining rotation and translation)
    // Function at 0x0056b8a0 probably handles matrix composition or copy.
    FUN_0056b8a0(transX, transY, transZ, outMatrix);
}