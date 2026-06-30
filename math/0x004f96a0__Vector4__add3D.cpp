// FUNC_NAME: Vector4::add3D
class Vector4 {
public:
    float mData[4];  // +0x00: x, +0x04: y, +0x08: z, +0x0C: w

    // Adds first three components of a and b into this->mData[0..2].
    // The w component (mData[3]) is preserved unchanged.
    void __thiscall add3D(const float* a, const float* b) {
        float savedW = mData[3];
        mData[0] = a[0] + b[0];
        mData[1] = a[1] + b[1];
        mData[2] = a[2] + b[2];
        mData[3] = savedW;
    }
};