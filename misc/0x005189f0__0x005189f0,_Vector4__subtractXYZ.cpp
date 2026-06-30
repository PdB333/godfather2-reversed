// FUNC_NAME: 0x005189f0, Vector4::subtractXYZ
// Role: Subtracts the 3D components (x,y,z) of two 4D vectors, storing result in this vector while preserving the original w component.
// This function takes two Vector4 inputs (a and b) and computes a - b for the x,y,z elements.
// The w element of 'this' is left unchanged.
// Source: EA EARS engine, The Godfather 2 (2008)

void __thiscall Vector4::subtractXYZ(const Vector4& a, const Vector4& b)
{
    float savedW = this->w;        // +0x0C (w component, preserved)
    this->x = a.x - b.x;           // +0x00
    this->y = a.y - b.y;           // +0x04
    this->z = a.z - b.z;           // +0x08
    this->w = savedW;              // restore original w
}