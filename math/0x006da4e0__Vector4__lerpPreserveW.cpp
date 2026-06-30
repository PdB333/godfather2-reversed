// FUNC_NAME: Vector4::lerpPreserveW
// Function address: 0x006da4e0
// Interpolates the x,y,z components of this Vector4 from two source vectors,
// leaving the w component unchanged.

class Vector4 {
public:
    float x, y, z, w;

    void lerpPreserveW(const Vector4& from, const Vector4& to, float t)
    {
        // Save current w before modifying
        float originalW = w;

        // Linear interpolation on x, y, z
        x = (to.x - from.x) * t + from.x;
        y = (to.y - from.y) * t + from.y;
        z = (to.z - from.z) * t + from.z;

        // Preserve w unchanged
        w = originalW;
    }
};