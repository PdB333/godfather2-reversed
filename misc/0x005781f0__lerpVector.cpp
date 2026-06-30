// FUNC_NAME: lerpVector
// Address: 0x005781f0
// Role: Performs linear interpolation between two 4D vectors (from, to) and stores result in out.
// The vectors are assumed to be 4 floats at offset +0x10 in their respective structures.
// The interpolation factor t is clamped to [0,1] via an external function (likely clamp).
// Note: The caller passes the start and end vector pointers in registers EDI (start) and ESI (to).

struct Vector4 {
    float pad[4]; // offset 0x0 - 0xf (padding, values before +0x10)
    float x;  // offset 0x10
    float y;  // offset 0x14
    float z;  // offset 0x18
    float w;  // offset 0x1c
};

// External clamp function (address 0x0056cc80)
extern float clampToRange0to1(float value);

// Interpolation function
void lerpVector(Vector4* out, float t, Vector4* from, Vector4* to) {
    // Clamp interpolation factor
    t = clampToRange0to1(t);

    // Linear interpolation for each component
    out->x = from->x + (to->x - from->x) * t;
    out->y = from->y + (to->y - from->y) * t;
    out->z = from->z + (to->z - from->z) * t;
    out->w = from->w + (to->w - from->w) * t;
}