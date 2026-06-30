// FUNC_NAME: Vector4::addXYZ

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

// 0x005339f0 - Adds the first three components of two vectors, preserving the w component of the calling object.
void __thiscall Vector4::addXYZ(Vector4* this, const Vector4* a, const Vector4* b) {
    this->x = a->x + b->x;
    this->y = a->y + b->y;
    this->z = a->z + b->z;
    // w remains unchanged
}