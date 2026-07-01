// FUNC_NAME: Vector4::setScaled
// Function address: 0x007f3520
// Role: Scales a source vector by a scalar and stores in this vector, preserving the w component.
// Used for vector operations where w (homogeneous coordinate) should remain unchanged.

class Vector4 {
public:
    float x, y, z, w;

    // Sets this vector to a scaled version of src, keeping w unchanged.
    // Equivalent to: this = (src * scalar) with w preserved.
    void __thiscall setScaled(const Vector4& src, float scalar) {
        x = scalar * src.x;
        y = scalar * src.y;
        z = scalar * src.z;
        // w is intentionally left unchanged (preserves homogeneous coordinate)
    }
};