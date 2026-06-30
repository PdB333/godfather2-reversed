// FUNC_NAME: Vector4::scaleAndAdd
void __thiscall Vector4::scaleAndAdd(const Vector4 &other, float scale, Vector4 &dest)
{
    float thisX = this->x; // +0x00
    float thisY = this->y; // +0x04
    float thisZ = this->z; // +0x08
    float thisW = this->w; // +0x0C

    float otherX = other.x;
    float otherY = other.y;
    float otherZ = other.z;
    float otherW = other.w;

    dest.x = scale * thisX + otherX;
    dest.y = scale * thisY + otherY;
    dest.z = scale * thisZ + otherZ;
    dest.w = scale * thisW + otherW;
}