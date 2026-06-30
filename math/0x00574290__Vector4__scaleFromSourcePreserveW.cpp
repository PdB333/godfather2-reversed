// FUNC_NAME: Vector4::scaleFromSourcePreserveW

// Represents a 4-component vector (x, y, z, w) common in EA's EARS engine math.
struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C
};

// Scales the first three components (x, y, z) of this vector by 'scale' using values from 'src',
// while preserving the original w component unchanged.
// __thiscall: ECX = this, EDX = &src, stack = scale
void __thiscall Vector4::scaleFromSourcePreserveW(const Vector4& src, float scale)
{
    float originalW = this->w;

    this->x = scale * src.x;
    this->y = scale * src.y;
    this->z = scale * src.z;

    this->w = originalW;
}