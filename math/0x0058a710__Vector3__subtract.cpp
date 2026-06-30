// FUNC_NAME: Vector3::subtract
// Address: 0x0058a710
// Subtracts another Vector3 from this Vector3 and stores result in output vector.
// this -> minuend, param1 -> subtrahend, param2 -> result storage

class Vector3 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C (unused, padding)

    void __thiscall subtract(const Vector3& rhs, Vector3& out) const {
        out.x = this->x - rhs.x;
        out.y = this->y - rhs.y;
        out.z = this->z - rhs.z;
        // w (index 3) ignored; likely unused or padding
    }
};