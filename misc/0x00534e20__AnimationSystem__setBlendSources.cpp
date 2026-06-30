// FUNC_NAME: AnimationSystem::setBlendSources
void __thiscall AnimationSystem::setBlendSources(uint32_t* pSourceA, uint32_t* pSourceB)
{
    // Store first set of 4 uint32 values from pSourceB into global storage
    gBlendStorageB[0] = pSourceB[0]; // +0x0
    gBlendStorageB[1] = pSourceB[1]; // +0x4
    gBlendStorageB[2] = pSourceB[2]; // +0x8
    gBlendStorageB[3] = pSourceB[3]; // +0xC

    // Store second set of 4 uint32 values from pSourceA into global storage
    gBlendStorageA[0] = pSourceA[0]; // +0x0
    gBlendStorageA[1] = pSourceA[1]; // +0x4
    gBlendStorageA[2] = pSourceA[2]; // +0x8
    gBlendStorageA[3] = pSourceA[3]; // +0xC

    // gBlendIndex is a byte index into arrays of 0x3C-byte structures
    uint32_t index = (uint32_t)gBlendIndex;

    // Process first blend target if valid pointer at gBlendTargets1[index]
    if (gBlendTargets1[index] != nullptr)
    {
        applyBlend(gBlendContext, gBlendTargets1[index], &gBlendStorageB);
    }

    // Process second blend target if valid pointer at gBlendTargets2[index]
    if (gBlendTargets2[index] != nullptr)
    {
        applyBlend(gBlendContext, gBlendTargets2[index], &gBlendStorageA);
    }
}