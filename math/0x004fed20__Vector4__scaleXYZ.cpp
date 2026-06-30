// FUNC_NAME: Vector4::scaleXYZ
// Function at 0x004fed20: Component-wise multiplication of two source vectors (a and b) into this vector,
// storing the product in the first three components (x, y, z) and preserving the original w component.
// In EARS engine, this is likely a method of a 4D vector class (Vector4) used for scaling direction/point vectors
// without affecting homogeneous coordinate.
// Offsets: +0x00 = x, +0x04 = y, +0x08 = z, +0x0c = w

class Vector4 {
public:
    float x, y, z, w; // matching layout: 4 floats

    // __thiscall: this in ECX, a and b passed on stack
    void scaleXYZ(const float* a, const float* b) {
        // Load source components
        float ax = a[0];
        float ay = a[1];
        float az = a[2];
        float aw = a[3]; // loaded but not used in final assignment

        float bx = b[0];
        float by = b[1];
        float bz = b[2];
        float bw = b[3];

        // Result components: x = a.x * b.x, y = a.y * b.y, z = a.z * b.z
        x = ax * bx;
        y = ay * by;
        z = az * bz;

        // w is preserved (original w value before modification)
        // The product a.w * b.w is computed but then overwritten with the original this->w
        w = this->w; // fVar1 was saved before modification: in_EAX[3] initial value
    }
};