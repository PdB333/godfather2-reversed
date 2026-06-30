// FUNC_NAME: VectorMath::computeScaledDifference
// Function at 0x005c70c0: Computes a scaled difference between two 4-component vectors.
// Subtracts 'src' from 'this', then multiplies each component by a global scale factor.
// This is likely used for coordinate system conversions (e.g., world-to-local).
// Global scale factors at 0x00e3eb50, 0x00e3eb54, 0x00e3eb58, 0x00e3eb5c.

extern float g_scaleX; // +0x00e3eb50
extern float g_scaleY; // +0x00e3eb54
extern float g_scaleZ; // +0x00e3eb58
extern float g_scaleW; // +0x00e3eb5c

// Assuming Vector4 is a struct with x, y, z, w
struct Vector4 {
    float x, y, z, w;
};

void __thiscall VectorMath::computeScaledDifference(const Vector4& src, Vector4& dst) const {
    // Subtract src from this (implicit 'this' pointer), scale each component.
    dst.x = (this->x - src.x) * g_scaleX;
    dst.y = (this->y - src.y) * g_scaleY;
    dst.z = (this->z - src.z) * g_scaleZ;
    dst.w = (this->w - src.w) * g_scaleW;
}