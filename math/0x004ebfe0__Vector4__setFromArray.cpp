// FUNC_NAME: Vector4::setFromArray
void __thiscall Vector4::setFromArray(Vector4 *this, float *src) {
    // Copy 4 float components from source array into object offsets
    // Offset +0x10: x (first component)
    // Offset +0x14: y (second component)
    // Offset +0x18: z (third component)
    // Offset +0x1c: w (fourth component)
    this->x = src[0];
    this->y = src[1];
    this->z = src[2];
    this->w = src[3];
}