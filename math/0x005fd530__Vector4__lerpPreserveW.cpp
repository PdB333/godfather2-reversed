// FUNC_NAME: Vector4::lerpPreserveW
// Function address: 0x005fd530
// Role: Linear interpolation of the first three components (x,y,z) of a vector,
// preserving the fourth component (w). This is likely used for quaternion
// interpolation (where w is the scalar part) or color interpolation (where w is alpha).

class Vector4 {
public:
    float x, y, z, w;

    // Interpolates from source1 to source2 by factor t, keeping the current w unchanged.
    void __thiscall lerpPreserveW(const float* from, const float* to, float t) {
        x = (to[0] - from[0]) * t + from[0];
        y = (to[1] - from[1]) * t + from[1];
        z = (to[2] - from[2]) * t + from[2];
        // w remains the same (saved before interpolation and restored)
    }
};