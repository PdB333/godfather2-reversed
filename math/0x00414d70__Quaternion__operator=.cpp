// FUNC_NAME: Quaternion::operator=
// Function address: 0x00414d70
// Copies a 4-component quaternion (16 bytes) from source to this.
// Used extensively in animation/skinning code (called 11 times from 0x00879d90).

class Quaternion {
public:
    float x, y, z, w; // offsets: +0x00, +0x04, +0x08, +0x0C

    // __thiscall: this in ecx, param_2 is source pointer
    Quaternion& operator=(const Quaternion& rhs) {
        // Copy 4 floats (16 bytes)
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return *this;
    }
};