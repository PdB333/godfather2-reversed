// FUNC_NAME: crossProduct (3D vector cross product, preserving w component)
void crossProduct(float* out, const float* a, const float* b)
{
    // Load input vectors (assumed to be 4-component, but only xyz used for cross)
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // unused in cross, but loaded
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // unused in cross, but loaded

    // Save original w component of output (to preserve it)
    float originalOutW = out[3];

    // Compute cross product: out = a × b
    out[0] = bz * ay - by * az; // out.x = b.z*a.y - b.y*a.z
    out[1] = bx * az - bz * ax; // out.y = b.x*a.z - b.z*a.x
    out[2] = by * ax - bx * ay; // out.z = b.y*a.x - b.x*a.y

    // The original code computed aw*bw - aw*bw = 0, then restored originalOutW
    // This effectively leaves out.w unchanged.
    out[3] = originalOutW;
}