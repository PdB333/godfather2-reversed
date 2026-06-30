// FUNC_NAME: Vector4::scale
// Function address: 0x0056b770
// Role: Multiplies a 4-component vector by a scalar and writes result to an output vector.
// This is a member function of a Vector4 class (float[4]).
// - this: source vector (in EAX/ECX)
// - param_1 (stack): pointer to destination Vector4
// - param_2 (stack): scalar multiplier

class Vector4 {
public:
    float x, y, z, w; // components, offset 0x00..0x0C

    // Scale this vector by scalar and store result in out.
    void __thiscall scale(Vector4 &out, float scalar) {
        // Read source components from this (using ECX).
        float sx = this->x;
        float sy = this->y;
        float sz = this->z;
        float sw = this->w;

        // Apply scaling and write to destination.
        out.x = scalar * sx;
        out.y = scalar * sy;
        out.z = scalar * sz;
        out.w = scalar * sw;
    }
};