// FUNC_NAME: Color::multiplyAndSetAlpha

// Reconstructed from 0x00582ef0: Component-wise multiply of two colors, then force alpha to a constant.
// The class has a pointer to float[4] at offset 8 (this+8).
class Color {
public:
    float* data; // pointer to RGBA floats (at offset +0, but not certain; actually data is at offset +8 in the class? The code dereferences this+8 to get float*)
    // Note: The actual layout may have a float* at +0x8; we treat data as a member at that offset.

    void __fastcall multiplyAndSetAlpha(Color& a, Color& b, float constantAlpha) {
        // this in EAX, a in param_2, b in param_3
        float* srcA = *(float**)((uintptr_t)&a + 8);
        float* srcB = *(float**)((uintptr_t)&b + 8);
        float* dst  = *(float**)((uintptr_t)this + 8);

        dst[0] = srcA[0] * srcB[0];  // R
        dst[1] = srcA[1] * srcB[1];  // G
        dst[2] = srcA[2] * srcB[2];  // B
        dst[3] = srcA[3] * srcB[3];  // A (temp)
        dst[3] = constantAlpha;      // override alpha with constant (e.g., 1.0f)
    }
};

// Global constant referenced at address 0x00e2b1a4 (likely a float, e.g., 1.0f)
extern const float g_colorAlphaOverride;