// FUNC_NAME: Vector4::subtractPreservingW
// Address: 0x005e4170
// Role: Subtracts the first three components of two 4D vectors, preserving the fourth (w) component of the destination.

class Vector4 {
public:
    float x, y, z, w;  // offsets: +0x00, +0x04, +0x08, +0x0C

    // Compute: this.xyz = a.xyz - b.xyz; this.w is unchanged.
    // Original implementation uses EAX as the hidden 'this' pointer (not ECX).
    void subtractPreservingW(const Vector4& a, const Vector4& b) {
        float savedW = this->w;          // preserve original w
        this->x = a.x - b.x;             // component-wise subtraction of x
        this->y = a.y - b.y;             // component-wise subtraction of y
        this->z = a.z - b.z;             // component-wise subtraction of z
        this->w = savedW;                // restore original w (unchanged)
        // a.w and b.w are loaded but not used in the subtraction.
    }
};