// FUNC_NAME: Vector4::crossProduct
// Address: 0x0066f540
// Role: Cross product of two 4-component vectors (only x,y,z used). The fourth component of result is zero.

class Vector4 {
public:
    float x, y, z, w; // offsets 0x00, 0x04, 0x08, 0x0C

    // Computes cross product of this (implicit) and 'b', stores result in 'result'.
    // (this) is treated as the first vector.
    void __thiscall crossProduct(const Vector4& b, Vector4& result) const {
        float ax = this->x;
        float ay = this->y;
        float az = this->z;
        float aw = this->w; // not used in cross part

        float bx = b.x;
        float by = b.y;
        float bz = b.z;
        float bw = b.w;

        // Standard 3D cross product components
        result.x = ay * bz - az * by;
        result.y = az * bx - ax * bz;
        result.z = ax * by - ay * bx;
        // w component = aw * bw - aw * bw = 0
        result.w = aw * bw - aw * bw; // intentionally zero
    }
};