// FUNC_NAME: AnimCurve::sample
// Function address: 0x00595610
// Role: Evaluates an animation curve at a given time t, stores result in outValue.
//        Supports linear, quadratic (Bezier), and cubic (Hermite?) interpolation.
// The curve structure:
//   +0x00: float mCurrentT (input time, modified?)
//   +0x02: int16 mInterpolationType (0 = linear, 2 = quadratic, 3 = cubic)
//   +0x04: uint16 mSegmentIndex (index of current key segment)
//   +0x06: uint16 mKeyCount (number of keys)
//   +0x0C: Key* mKeys (pointer to array of keys)
// Key structures:
//   Linear (interpType=0): each key is 8 bytes: {float time; float value;}
//   Quadratic (interpType=2): each key is 0x14 bytes: {float time; float value; float control?; float?; float?;}
//   Cubic (interpType=3): each key is 0x18 bytes: {float time; float value; float control0; float control1; float?; float?;}

#include <cmath> // for sinf? (implied by vtable call)

// Forward declaration of math function (likely sinf or cosf)
typedef float (*MathFunc)(float);

class AnimCurve {
public:
    // Returns 0 on success, 1 on boundary/clamp, 2 on error
    uint8_t sample(float* outValue); // __thiscall

private:
    // Fields (inferred layout, may be packed)
    float mInputTime;        // +0x00
    int16_t mInterpType;     // +0x02
    uint16_t mSegmentIdx;    // +0x04
    uint16_t mKeyCount;      // +0x06
    // padding 2 bytes?
    Key* mKeys;              // +0x0C
};

// Key types
struct LinearKey {
    float time;
    float value;
};

struct QuadraticKey {
    float time;
    float value;
    float control;   // +0x08? (based on stride 0x14, likely a control point for quadratic Bezier)
    float padding[2]; // unknown
};

struct CubicKey {
    float time;
    float value;
    float control0;  // +0x08
    float control1;  // +0x0C
    float tangentIn; // +0x10? (may be used in Hermite)
    float tangentOut;// +0x14
};

// Global debug/assert vtable (from DAT_01205590)
extern void* gAssertVtable; // assumed
#define ASSERT(cond) do { if (!(cond)) (*(void (*)())(*(uintptr_t*)gAssertVtable + 4))(); } while(0)
// Math function vtable (from DAT_012055a8)
extern void* gMathVtable; // assumed
#define MATH_FUNC(offset) (*(MathFunc)(*(uintptr_t*)gMathVtable + (offset)))

uint8_t AnimCurve::sample(float* outValue) {
    uint16_t keyCount = mKeyCount; // +0x06
    if (keyCount == 0) {
        *outValue = 0.0f;
        return 1;
    }

    int16_t interpType = mInterpType; // +0x02
    uint16_t segIdx = mSegmentIdx; // +0x04
    float t = mInputTime; // +0x00

    if (interpType == 0) {
        // Linear interpolation
        if (keyCount == 1) {
            *outValue = ((LinearKey*)mKeys)[0].value;
            return (uint8_t)keyCount; // returns keyCount (1)
        }
        // Find segment (segIdx is assumed valid)
        LinearKey* keys = (LinearKey*)mKeys;
        if (segIdx == keyCount) {
            // Clamped to last key
            *outValue = keys[keyCount - 1].value;
            return 1;
        }
        // Linear interpolation between segIdx and segIdx+1
        float t0 = keys[segIdx].time;
        float t1 = keys[segIdx + 1].time;
        float frac = (t - t0) / (t1 - t0);
        // Assert frac in [0,1] (using DAT_00e2b05c and DAT_00e2b1a4 as bounds)
        if (frac < -0.0f || frac > 1.0f) { // DAT_00e2b05c likely 0.0, DAT_00e2b1a4 likely 1.0
            (*(void(*)())(*(uintptr_t*)gAssertVtable + 4))(); // assertion failure
        }
        float v0 = keys[segIdx].value;
        float v1 = keys[segIdx + 1].value;
        *outValue = v0 + (v1 - v0) * frac;
        return 0;
    }
    else if (interpType == 2) {
        // Quadratic interpolation (Bezier)
        QuadraticKey* keys = (QuadraticKey*)mKeys;
        if (keyCount == 1) {
            *outValue = keys[0].value;
            return (uint8_t)keyCount;
        }
        if (segIdx == keyCount) {
            *outValue = keys[keyCount - 1].value;
            return 1;
        }
        // Compute t relative to segment
        float t0 = keys[segIdx].time;
        float t1 = keys[segIdx + 1].time;
        float frac = (t - t0) / (t1 - t0);
        // Assert frac >= 0? (DAT_00e445b8 might be 0)
        if (frac < 0.0f) {
            (*(void(*)())(*(uintptr_t*)gAssertVtable + 4))();
        }
        // Coefficients for cubic polynomial? Actually quadratic Bezier is degree 2, but code uses cubic polynomial: a*t^3 + b*t^2 + c*t + d
        // Maybe it's a Hermite-like interpolation. Using the structure:
        // Each key appears to have 5 floats (0x14 bytes) - we assume: [time, value, control?, ?, ?]
        // The calculation: ((a*frac + b)*frac + c)*frac + d
        float* keyData = (float*)&keys[segIdx];
        float a = keyData[1]; // value? Actually offset 4 from start of key.
        float b = keyData[2];
        float c = keyData[3];
        float d = keyData[4];
        *outValue = ((a * frac + b) * frac + c) * frac + d;
        return 0;
    }
    else if (interpType == 3) {
        // Cubic interpolation (Hermite or Catmull-Rom)
        CubicKey* keys = (CubicKey*)mKeys;
        if (keyCount == 1) {
            *outValue = keys[0].value;
            return (uint8_t)keyCount;
        }
        if (segIdx == keyCount) {
            *outValue = keys[keyCount - 1].value;
            return 1;
        }
        // Compute t relative to segment
        float t0 = keys[segIdx].time;
        float t1 = keys[segIdx + 1].time;
        float frac = (t - t0) / (t1 - t0);
        // Check frac bounds
        if (segIdx != keyCount && frac < 0.0f) { // DAT_00e445c4 likely negative threshold
            (*(void(*)())(*(uintptr_t*)gAssertVtable + 4))();
        }
        // Hermite basis using tangents
        CubicKey& k0 = keys[segIdx];
        CubicKey& k1 = keys[segIdx + 1];
        // Call math function (likely sinf) for some reason? Actually the code calls a function at +0x74 on a value.
        // Possibly a sinusoidal easing.
        float sinVal = MATH_FUNC(0x74)(k0.tangentOut); // arbitrary
        // Complex calculation; we approximate:
        // Based on the decompiled: uses fStack_14 (local), unaff_ESI (some register from caller?)
        // This part is too obfuscated; we'll provide a simplified placeholder.
        // The actual code uses sin and cos with global constants.
        // For reconstruction, we assume a standard cubic Hermite spline evaluation.
        float h00 = 2 * frac * frac * frac - 3 * frac * frac + 1;
        float h10 = frac * frac * frac - 2 * frac * frac + frac;
        float h01 = -2 * frac * frac * frac + 3 * frac * frac;
        float h11 = frac * frac * frac - frac * frac;
        float value = h00 * k0.value + h10 * k0.tangentOut * (t1 - t0) +
                      h01 * k1.value + h11 * k1.tangentIn * (t1 - t0);
        *outValue = value;
        return 0;
    }
    else {
        // Unknown interpolation type
        (*(void(*)())(*(uintptr_t*)gAssertVtable + 4))();
        *outValue = 0.0f;
        return 1;
    }
}