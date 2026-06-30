// FUNC_NAME: MathUtils::scaleVec3KeepW
// Function at 0x004fecf0: Scales the first three components (x, y, z) of a vector by a scalar, preserving the fourth component (w) unchanged.
// This is a member function of a class containing at least a 4‑float array (likely Vector4 or Quaternion).
void __thiscall MathUtils::scaleVec3KeepW(const float *src, float scale) {
    float savedW = this->m_data[3]; // +0x0C: save original w
    this->m_data[0] = src[0] * scale; // +0x00: x = src.x * scale
    this->m_data[1] = src[1] * scale; // +0x04: y = src.y * scale
    this->m_data[2] = src[2] * scale; // +0x08: z = src.z * scale
    this->m_data[3] = savedW;         // +0x0C: restore original w
}