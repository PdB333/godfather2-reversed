// FUNC_NAME: Vector4::setScaledXYZ
// Address: 0x00527f70
// This function scales the xyz components of a Vector4 from a source vector by a scalar,
// while preserving the w component of the destination (this).
// Parameters:
//   src: source vector (passed in EDX)
//   scale: scalar multiplier (passed on stack)
// Call convention: __thiscall (this in ECX)

class Vector4 {
public:
    float x, y, z, w; // +0x00, +0x04, +0x08, +0x0C

    void setScaledXYZ(const Vector4& src, float scale) {
        float originalW = this->w;

        this->x = src.x * scale;
        this->y = src.y * scale;
        this->z = src.z * scale;
        // w is intentionally not scaled from src; keep original
        this->w = originalW;
    }
};