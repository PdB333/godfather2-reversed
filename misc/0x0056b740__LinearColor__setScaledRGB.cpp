// FUNC_NAME: LinearColor::setScaledRGB
// Address: 0x0056b740
// Sets the RGB components from a source color scaled by a factor, preserving the current alpha.
void __thiscall LinearColor::setScaledRGB(const LinearColor* src, float scale) {
    float savedAlpha = this->a; // preserve alpha (+0x0C)
    this->r = src->r * scale;   // +0x00
    this->g = src->g * scale;   // +0x04
    this->b = src->b * scale;   // +0x08
    this->a = savedAlpha;       // restore alpha unchanged
}