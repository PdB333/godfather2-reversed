// FUNC_NAME: Vector4::crossProduct
// Address: 0x00613010
// Computes the 3D cross product of this vector and another vector, storing result into out.
// The fourth component (w) of the result is set to 0, representing a direction vector.
void __thiscall Vector4::crossProduct(const Vector4* this, const Vector4& other, Vector4& out)
{
    float ax = this->x;
    float ay = this->y;
    float az = this->z;
    float aw = this->w; // unused in cross, but read

    float bx = other.x;
    float by = other.y;
    float bz = other.z;
    float bw = other.w; // unused

    // Compute cross product: out = other × this  (i.e., param_1 × this)
    // Equivalent to - (this × other)
    out.x = (ay * bz) - (az * by);   // b.y*a.z - b.z*a.y
    out.y = (az * bx) - (ax * bz);   // b.z*a.x - b.x*a.z
    out.z = (ax * by) - (ay * bx);   // b.x*a.y - b.y*a.x
    out.w = 0.0f;                    // fourth component zero for vector
}