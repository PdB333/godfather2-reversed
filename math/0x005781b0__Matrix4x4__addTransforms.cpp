// FUNC_NAME: Matrix4x4::addTransforms
void Matrix4x4::addTransforms(Matrix4x4* other)
{
    // Call base function (likely adds translation components)
    FUN_0056cba0(this);

    // Load translation components from this matrix
    float tx = this->translationX;   // +0x14
    float ty = this->translationY;   // +0x18
    float tz = this->translationZ;   // +0x1c

    // Load translation components from other matrix (unaff_EDI)
    float otherTx = other->translationX; // +0x14
    float otherTy = other->translationY; // +0x18
    float otherTz = other->translationZ; // +0x1c

    // Add rotation components (unaff_ESI is likely a temporary or output matrix)
    // Rotation components at +0x10
    output->rotationX = this->rotationX + other->rotationX;   // +0x10
    output->translationX = tx + otherTx;                       // +0x14
    output->translationY = ty + otherTy;                       // +0x18
    output->translationZ = tz + otherTz;                       // +0x1c

    // Override the last translation component with a constant (likely identity or zero)
    output->translationW = DAT_00e2b1a4;                       // +0x1c (overwritten)
}