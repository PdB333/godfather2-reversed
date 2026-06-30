// FUNC_NAME: AnimationBlender::getBlendedFloatValue

// Address: 0x005fe710
// Role: Computes a blended float value from two potential animation nodes/keys.
// The object contains flags/pointers to two elements (perhaps animation clips or keys),
// each storing a float at offset +0x0C. If only one element is present, its value is returned.
// If both are present, a linear interpolation is performed using blend factors at +0xC0 and +0xC4.
// The blend factor (fBlendFactor / fBlendThreshold) is used as lerp weight, but if the threshold
// is reached (fBlendFactor >= fBlendThreshold), the second element's value is used directly.

#include <cmath> // for fabs if needed, but not used directly

class AnimationBlender {
public:
    // Offsets relative to this object:
    // +0x7C: m_bFirstActiveFlag (int, 0 or non-zero)
    // +0x84: m_pFirstElement (float*)
    // +0x88: m_bSecondActiveFlag (int, 0 or non-zero)
    // +0x90: m_pSecondElement (float*)
    // +0xC0: m_fBlendFactor (float)
    // +0xC4: m_fBlendThreshold (float)

    float __fastcall getBlendedFloatValue() const;
};

float __fastcall AnimationBlender::getBlendedFloatValue() const {
    // Obtain pointers to the two elements, respecting their activation flags.
    float* pFirst = nullptr;
    if (*(int*)((char*)this + 0x7C) != 0) {
        pFirst = *(float**)((char*)this + 0x84);
    }

    float* pSecond = nullptr;
    if (*(int*)((char*)this + 0x88) != 0) {
        pSecond = *(float**)((char*)this + 0x90);
    }

    // Case: only one element is valid, return its value directly.
    if (pFirst == nullptr) {
        if (pSecond != nullptr) {
            return *(pSecond + 3);  // +0x0C (3 floats offset)
        }
        return 0.0f; // neither element active
    }

    if (pSecond == nullptr) {
        return *(pFirst + 3); // +0x0C
    }

    // Both elements are present. Use the blend factor if blending is active.
    float firstValue = *(pFirst + 3);
    float secondValue = *(pSecond + 3);

    float blendFactor = *(float*)((char*)this + 0xC0);
    float blendThreshold = *(float*)((char*)this + 0xC4);

    // If the blend factor is positive and the threshold is positive, apply a cross-fade.
    if ((blendFactor > 0.0f) && (blendThreshold > 0.0f)) {
        if (blendFactor >= blendThreshold) {
            // Fully blended to the second element.
            return secondValue;
        }
        // Linear interpolation: weight = blendFactor / blendThreshold
        float weight = blendFactor / blendThreshold;
        return firstValue + weight * (secondValue - firstValue);
    }

    // No valid blend input, return the first element's value.
    return firstValue;
}