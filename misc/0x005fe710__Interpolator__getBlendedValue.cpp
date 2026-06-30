// FUNC_NAME: Interpolator::getBlendedValue
// Function at 0x005fe710: returns an interpolated float from two cached sources, with blending
// Class fields (relative to this):
// +0x7c: SourceA* (may be nullptr)
// +0x84: float* (cached pointer to float inside SourceA at offset +0xc)
// +0x88: SourceB* (may be nullptr)
// +0x90: float* (cached pointer to float inside SourceB at offset +0xc)
// +0xc0: blendFactorA (float, used as numerator in lerp, must be >0)
// +0xc4: blendFactorB (float, used as denominator in lerp, must be >0)
float __fastcall Interpolator::getBlendedValue(void* thisPtr) {
    float valueA = 0.0f;
    float valueB = 0.0f;

    // Determine value from source A
    if (*(void**)((char*)thisPtr + 0x7c) != nullptr) {
        valueA = *(float*)(*(int*)((char*)thisPtr + 0x84) + 0xc);
    }

    // Determine value from source B
    if (*(void**)((char*)thisPtr + 0x88) != nullptr) {
        valueB = *(float*)(*(int*)((char*)thisPtr + 0x90) + 0xc);
    }

    // If only one source exists, use its value directly
    if (*(void**)((char*)thisPtr + 0x7c) == nullptr) {
        if (*(void**)((char*)thisPtr + 0x88) != nullptr) {
            return valueB;
        }
        return 0.0f;
    }
    if (*(void**)((char*)thisPtr + 0x88) == nullptr) {
        return valueA;
    }

    // Both sources exist. Blend if values differ and both factors are positive.
    float factorA = *(float*)((char*)thisPtr + 0xc0);
    float factorB = *(float*)((char*)thisPtr + 0xc4);

    if (valueA != valueB && factorA > 0.0f && factorB > 0.0f) {
        if (factorB <= factorA) {
            return valueB;
        }
        // Linear interpolation: t = factorA / factorB
        return (factorA / factorB) * (valueB - valueA) + valueA;
    }

    return valueA;
}