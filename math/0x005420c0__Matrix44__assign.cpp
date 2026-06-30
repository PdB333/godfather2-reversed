// FUNC_NAME: Matrix44::assign
// Address: 0x005420c0
// Copies 16 floats (64 bytes) from source to this.
// This is a member function of a 4x4 matrix (16 floats).

struct Matrix44 {
    float data[16]; // +0x00 to +0x3F

    void __thiscall assign(const Matrix44& other) {
        // Copy 16 floats from source to this
        for (int i = 0; i < 16; ++i) {
            data[i] = other.data[i];
        }
    }
};