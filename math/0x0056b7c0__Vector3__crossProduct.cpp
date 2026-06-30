// FUNC_NAME: Vector3::CrossProduct
// Function address: 0x0056b7c0
// Role: Compute the cross product of two 3D vectors (stored in 4-float arrays, w ignored) and store the result.
// The function takes two Vector3 inputs: one via this pointer (in_ECX), one via the first explicit parameter (param_1),
// and writes the result to the second explicit parameter (param_2). The w component of the result is set to zero.

struct Vector3 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

void __thiscall Vector3::CrossProduct(const Vector3& other, Vector3& out) {
    // this is the first vector (implicit via ECX)
    // other is the second vector (explicit param_1)
    // out receives the cross product result (explicit param_2)

    float ax = other.x;
    float ay = other.y;
    float az = other.z;
    float aw = other.w; // unused in cross product

    float bx = this->x;
    float by = this->y;
    float bz = this->z;
    float bw = this->w; // unused in cross product

    // Cross product: result = a × b
    out.x = ay * bz - az * by; // [1] * [2] - [2] * [1]
    out.y = az * bx - ax * bz; // [2] * [0] - [0] * [2]
    out.z = ax * by - ay * bx; // [0] * [1] - [1] * [0]
    out.w = aw * bw - aw * bw; // always zero (w component set to 0)
}