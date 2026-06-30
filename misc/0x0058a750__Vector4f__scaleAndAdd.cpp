// FUNC_NAME: Vector4f::scaleAndAdd
class Vector4f {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    // result = scalar * this + other
    void scaleAndAdd(const Vector4f& other, float scalar, Vector4f& result) const {
        result.x = scalar * x + other.x;
        result.y = scalar * y + other.y;
        result.z = scalar * z + other.z;
        result.w = scalar * w + other.w;
    }
};