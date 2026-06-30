// FUNC_NAME: Vector4::lerp
// Reconstructed C++ function for linear interpolation of a 4-element vector.
// Input: this (start vector), target (end vector), t (interpolation factor), out (result vector).

void __thiscall Vector4::lerp(const Vector4* this, const Vector4* target, float t, Vector4* out)
{
    // Load components of this vector
    float startX = this->x;   // +0x00
    float startY = this->y;   // +0x04
    float startZ = this->z;   // +0x08
    float startW = this->w;   // +0x0C

    // Load components of target vector
    float endX = target->x;   // +0x00
    float endY = target->y;   // +0x04
    float endZ = target->z;   // +0x08
    float endW = target->w;   // +0x0C

    // Perform linear interpolation: out = start + (end - start) * t
    out->x = (endX - startX) * t + startX;
    out->y = (endY - startY) * t + startY;
    out->z = (endZ - startZ) * t + startZ;
    out->w = (endW - startW) * t + startW;
}