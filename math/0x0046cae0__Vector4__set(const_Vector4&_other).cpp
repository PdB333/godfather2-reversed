// FUNC_NAME: Vector4::set(const Vector4& other)
// Address: 0x0046cae0
// Role: Copies four floats from source to destination, returns true if any component changed.
// The function uses SIMD comparison (movmskps) to check all components simultaneously.
// Calling convention: __fastcall (this in ECX, 'other' pointer in EDX)
// Structure: Vector4 contains 4 floats at offsets 0x00, 0x04, 0x08, 0x0C

class Vector4 {
public:
    float x, y, z, w;  // +0x00, +0x04, +0x08, +0x0C

    // Copy from another Vector4 and return true if the value changed
    bool __fastcall set(const Vector4& other) {
        // Save original values
        float oldX = this->x;
        float oldY = this->y;
        float oldZ = this->z;
        float oldW = this->w;

        // Copy new values
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;

        // Check if any component differs (SIMD: compare and movemask)
        // Equivalent to: return (x != oldX) || (y != oldY) || (z != oldZ) || (w != oldW);
        // The original code used movmskps on a packed comparison result.
        return (oldX != this->x) || (oldY != this->y) || (oldZ != this->z) || (oldW != this->w);
    }
};