// FUNC_NAME: Math::Vector4::setFromSubtractPreserveW
void __thiscall Math::Vector4::setFromSubtractPreserveW(const float* a, const float* b)
{
    // Subtract two 4‑component vectors, but only store the first three components
    // of the result, leaving this->w unchanged. Used for operations where the
    // scalar part (w) must be preserved (e.g., quaternion vector part subtraction).
    float savedW = this->w;                       // +0x0C

    this->x = a[0] - b[0];                        // +0x00
    this->y = a[1] - b[1];                        // +0x04
    this->z = a[2] - b[2];                        // +0x08
    this->w = savedW;                             // +0x0C
}