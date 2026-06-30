// FUNC_NAME: Vector4::crossProduct

void __thiscall Vector4::crossProduct(const Vector4& other, Vector4& out) const
{
    // Compute cross product of the first three components (x,y,z) of 'this' and 'other'
    // The w component is set to 0, consistent with the quaternion cross product formula
    out.x = this->y * other.z - this->z * other.y;
    out.y = this->z * other.x - this->x * other.z;
    out.z = this->x * other.y - this->y * other.x;
    out.w = 0.0f; // Always zero (component discarded)
}