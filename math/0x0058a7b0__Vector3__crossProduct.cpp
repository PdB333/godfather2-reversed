// FUNC_NAME: Vector3::crossProduct
void __fastcall Vector3::crossProduct(float* out, const float* a, const float* b)
{
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // preserved but not used in cross
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // preserved but not used in cross
    float savedW = out[3]; // preserve original w component of output

    // 3D cross product: out = a × b
    out[0] = by * az - bz * ay; // cross.x
    out[1] = bz * ax - bx * az; // cross.y
    out[2] = bx * ay - by * ax; // cross.z
    out[3] = 0.0f; // temporary zero (bw*aw - bw*aw = 0)
    out[3] = savedW; // restore original w component
}