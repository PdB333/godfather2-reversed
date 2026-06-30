// FUNC_NAME: Vector4::scaleXYZ
void __fastcall Vector4::scaleXYZ(float *const this, const float *src, float scale) {
    // Save original w component
    float savedW = this[3];
    // Scale x, y, z from src
    this[0] = scale * src[0];
    this[1] = scale * src[1];
    this[2] = scale * src[2];
    // Restore w (keep original 4th component)
    this[3] = savedW;
}