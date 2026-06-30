// FUNC_NAME: Vector4::crossProduct
// Function address: 0x004f9710
// Computes the 3D cross product of two vectors (stored as 4-float arrays, w ignored).
// Uses __fastcall: in_EAX = destination (this), param_2 = a, param_3 = b.
// The destination's w component is preserved unchanged.

struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

void __fastcall crossProduct(Vector4* this, const Vector4* a, const Vector4* b) {
    float ax = a->x;
    float ay = a->y;
    float az = a->z;
    float aw = a->w; // unused in computation
    float bx = b->x;
    float by = b->y;
    float bz = b->z;
    float bw = b->w; // unused in computation
    float savedW = this->w;

    // Cross product: (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)
    this->x = ay * bz - az * by;
    this->y = az * bx - ax * bz;
    this->z = ax * by - ay * bx;
    this->w = savedW; // preserve original w
}