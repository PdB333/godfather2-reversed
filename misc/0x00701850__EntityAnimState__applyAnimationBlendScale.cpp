// FUNC_NAME: EntityAnimState::applyAnimationBlendScale
#include <cstddef>

// Scale input vector components by animation blend factors from global animation data.
// The blend factors are selected based on the current animation state at offset +0x2DC.
// The global pointer returned by getAnimationData() provides an array of 3-float groups.
void __thiscall EntityAnimState::applyAnimationBlendScale(void* thisPtr, float* scaleX, float* scaleY, float* scaleZ)
{
    // Global animation data manager (likely a singleton)
    void* animData = getAnimationData();  // FUN_007079c0
    if (animData != nullptr)
    {
        float factorX = 1.0f;
        float factorY = 1.0f;
        float factorZ = 1.0f;

        int animState = *(int*)((char*)thisPtr + 0x2DC);  // Current animation blend state index

        switch (animState)
        {
        case 1:  // State 1: use group A (offset 0x1D94)
            factorX = *(float*)((char*)animData + 0x1D94);
            factorY = *(float*)((char*)animData + 0x1D98);
            factorZ = *(float*)((char*)animData + 0x1D9C);
            break;
        case 2:  // States 2 and 3 share the same group B (offset 0x1DA0)
        case 3:
            factorX = *(float*)((char*)animData + 0x1DA0);
            factorY = *(float*)((char*)animData + 0x1DA4);
            factorZ = *(float*)((char*)animData + 0x1DA8);
            break;
        case 4:  // State 4: use group C (offset 0x1DAC)
            factorX = *(float*)((char*)animData + 0x1DAC);
            factorY = *(float*)((char*)animData + 0x1DB0);
            factorZ = *(float*)((char*)animData + 0x1DB4);
            break;
        default:
            // For unknown states, factors remain 1.0 (no scaling)
            break;
        }

        // Apply scaling to each component of the input vector
        *scaleX *= factorX;
        *scaleY *= factorY;
        *scaleZ *= factorZ;
    }
    // If no animation data, do nothing (scale stays unchanged)
}