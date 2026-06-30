// FUNC_NAME: Vector4::setScaledPreserveW
void __thiscall Vector4::setScaledPreserveW(const Vector4& source, float scalar) {
    // Save the original w component (homogeneous coordinate) so it remains unchanged.
    float savedW = this->w;  // +0x0C
    // Scale x, y, z components from source by scalar.
    this->x = scalar * source.x; // +0x00
    this->y = scalar * source.y; // +0x04
    this->z = scalar * source.z; // +0x08
    // Restore w – only the 3D vector part is scaled.
    this->w = savedW;            // +0x0C
}