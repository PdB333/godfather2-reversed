// FUNC_NAME: Vec4::crossProduct

void __thiscall Vec4::crossProduct(const Vec4& other, Vec4& out) const
{
    // this: first vector (x +0x00, y +0x04, z +0x08, w +0x0C)
    // other: second vector (same layout)
    // out: result cross product (3D cross of xyz, w set to 0)

    float this_x = this->x;
    float this_y = this->y;
    float this_z = this->z;
    float this_w = this->w;  // unused in cross product

    float other_x = other.x;
    float other_y = other.y;
    float other_z = other.z;
    float other_w = other.w; // unused

    out.x = this_y * other_z - this_z * other_y;
    out.y = this_z * other_x - this_x * other_z;
    out.z = this_x * other_y - this_y * other_x;
    out.w = 0.0f;
}