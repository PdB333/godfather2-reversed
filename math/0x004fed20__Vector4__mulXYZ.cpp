// FUNC_NAME: Vector4::mulXYZ
// Function at 0x004fed20 - component-wise multiplication of x, y, z components, leaving w unchanged
// Reconstructed C++

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

void __thiscall Vector4::mulXYZ(const Vector4& a, const Vector4& b) {
    // Preserve original w (the compiler loaded and stored it explicitly)
    float originalW = this->w;

    // Multiply first three components
    this->x = a.x * b.x;
    this->y = a.y * b.y;
    this->z = a.z * b.z;

    // w is not modified
    this->w = originalW;
}