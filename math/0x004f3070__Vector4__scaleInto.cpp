// FUNC_NAME: Vector4::scaleInto
void Vector4::scaleInto(float* dest, float scalar) {
    // Source vector (this) has 4 components at offsets 0x00, 0x04, 0x08, 0x0C
    dest[0] = scalar * this->data[0];
    dest[1] = scalar * this->data[1];
    dest[2] = scalar * this->data[2];
    dest[3] = scalar * this->data[3];
}