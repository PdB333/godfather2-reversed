// FUNC_NAME: Vector4::addPreserveW
// Function address: 0x005818b0
// Role: Adds the x, y, z components of two 4D vectors, preserving the w component of the destination.
// This is used for operations where the homogeneous coordinate (w) should remain unchanged.

void __fastcall Vector4::addPreserveW(Vector4* this, const Vector4* a, const Vector4* b)
{
    // Read all components first (as in the original assembly)
    float aY = a->y;
    float aZ = a->z;
    float aW = a->w;
    float bY = b->y;
    float bZ = b->z;
    float bW = b->w;
    float origW = this->w; // Save original w of destination

    // Add x, y, z components
    this->x = a->x + b->x;
    this->y = aY + bY;
    this->z = aZ + bZ;
    this->w = aW + bW; // Temporary sum (will be overwritten)

    // Restore original w (preserve it)
    this->w = origW;
}