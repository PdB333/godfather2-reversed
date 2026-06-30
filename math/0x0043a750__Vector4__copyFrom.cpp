// FUNC_NAME: Vector4::copyFrom
void __thiscall Vector4::copyFrom(Vector4* this, const Vector4* other)
{
    // Copy 16 bytes (4 floats) from other to this
    // Offsets: this[0]=x, this[4]=y, this[8]=z, this[12]=w
    this->x = other->x;  // +0x00
    this->y = other->y;  // +0x04
    this->z = other->z;  // +0x08
    this->w = other->w;  // +0x0C
}