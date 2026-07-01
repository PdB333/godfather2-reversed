// FUNC_NAME: vector3Subtract
void vector3Subtract(const float* a, const float* b, float* out)
{
    // Subtract 3D vectors (x, y, z) while preserving the 4th component (w) of the output.
    // a and b are assumed to be 4-component float arrays (x, y, z, w).
    // out[3] is left unchanged.
    float ax = a[0], ay = a[1], az = a[2];
    float bx = b[0], by = b[1], bz = b[2];
    float savedW = out[3]; // preserve original w component

    out[0] = ax - bx;
    out[1] = ay - by;
    out[2] = az - bz;
    out[3] = savedW; // restore w (not part of subtraction)
}