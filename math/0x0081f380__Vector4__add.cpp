// FUNC_NAME: Vector4::add
// Function address: 0x0081f380
// Adds this vector to another and stores the result in a third.
void __thiscall Vector4::add(float *other, float *result) {
    float x = this->x;    // +0x0
    float y = this->y;    // +0x4
    float z = this->z;    // +0x8
    float w = this->w;    // +0xc

    *result = x + *other;
    result[1] = y + other[1];
    result[2] = z + other[2];
    result[3] = w + other[3];
}