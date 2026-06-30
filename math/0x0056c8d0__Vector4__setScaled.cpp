// FUNC_NAME: Vector4::setScaled
// Function address: 0x0056c8d0
// Scale a Vector4 (first three components) from a source vector and scalar, preserving the fourth component.

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

void __thiscall Vector4::setScaled(const Vector4* src, float scale) {
    // Save the fourth component (w) before overwriting
    float savedW = this->w;

    // Scale first three components from source
    this->x = scale * src->x;
    this->y = scale * src->y;
    this->z = scale * src->z;

    // The fourth component is set to scaled source w then restored to original
    // (ultimately unchanged)
    this->w = scale * src->w;
    this->w = savedW;
}