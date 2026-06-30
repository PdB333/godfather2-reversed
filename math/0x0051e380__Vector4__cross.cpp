// FUNC_NAME: Vector4::cross
// Input pointers are treated as Vector4 (x,y,z,w). This sets this->xyz to cross(a.xyz, b.xyz) and preserves this->w.
void Vector4::cross(const Vector4& a, const Vector4& b)
{
    // Load a components
    float ax = a.x;
    float ay = a.y;
    float az = a.z;
    float aw = a.w; // unused for cross product

    // Load b components
    float bx = b.x;
    float by = b.y;
    float bz = b.z;
    float bw = b.w; // unused for cross product

    // Save original w
    float oldW = this->w;

    // Cross product: this.xyz = a.xyz × b.xyz
    this->x = by * az - bz * ay;
    this->y = bz * ax - bx * az;
    this->z = bx * ay - by * ax;

    // Preserve original w (handled by compiler as a no-op in original)
    this->w = oldW;
}