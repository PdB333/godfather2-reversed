// FUNC_NAME: Vector4::weightedAdd
// Function address: 0x0056c990
// Performs a weighted addition: result = scalar * this + other
// Where this and other are 4-component vectors.

class Vector4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

void __thiscall Vector4::weightedAdd(Vector4* other, float scalar, Vector4* result) {
    // Access fields from 'this' (passed via ECX)
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    // Access fields from 'other' (first parameter)
    float otherX = other->x;
    float otherY = other->y;
    float otherZ = other->z;
    float otherW = other->w;

    // Compute result = scalar * this + other
    result->x = scalar * thisX + otherX;
    result->y = scalar * thisY + otherY;
    result->z = scalar * thisZ + otherZ;
    result->w = scalar * thisW + otherW;
}