// FUNC_004f9710: Vector4::crossProduct
// Sets this->x,y,z to cross product of vector parts of a and b, preserves this->w.
// Inputs: a and b are 4-float arrays (x,y,z,w). Only x,y,z used for cross product.
void __thiscall Vector4::crossProduct(float *this, const float *a, const float *b)
{
    float aX = a[0]; // +0x00
    float aY = a[1]; // +0x04
    float aZ = a[2]; // +0x08
    float aW = a[3]; // +0x0C (unused)
    float bX = b[0]; // +0x00
    float bY = b[1]; // +0x04
    float bZ = b[2]; // +0x08
    float bW = b[3]; // +0x0C (unused)
    float origW = this[3]; // preserve original scalar part

    // Cross product: this->xyz = a x b
    this[0] = bY * aZ - bZ * aY; // x
    this[1] = bZ * aX - bX * aZ; // y
    this[2] = bX * aY - bY * aX; // z
    this[3] = 0.0f;               // temporary, overwritten next line
    this[3] = origW;              // restore original scalar component
}