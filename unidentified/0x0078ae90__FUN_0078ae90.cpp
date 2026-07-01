// FUNC_NAME: UnknownClass::computeClampedBlendValue

float __fastcall UnknownClass::computeClampedBlendValue(void* thisPtr)
{
    // Read two float fields from the object: +0x54 and +0x58
    float valueA = *(float*)((uintptr_t)thisPtr + 0x54);
    float valueB = *(float*)((uintptr_t)thisPtr + 0x58);

    // Global pointer at 0x012233a4 holds a pointer to an integer state
    int* statePtr = *(int**)0x012233a4;
    int stateId = *statePtr;

    // Only perform blending if the state is neither 0 nor a specific value (0x1f30 = 7984)
    if (stateId != 0 && stateId != 0x1f30)
    {
        // Blend using global scaling factor at 0x00d5c458
        float factor = *(float*)0x00d5c458;
        float blended = (valueA + valueB) * factor;

        // Apply a non‑linear transformation: result = 2*blended - valueB
        valueA = blended - (valueB - blended);

        // Clamp to zero
        if (valueA < 0.0f)
            valueA = 0.0f;
    }

    // If the state condition failed, return the original valueA unchanged
    return valueA;
}