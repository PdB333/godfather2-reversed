// FUNC_NAME: Vector3::subtract
void __fastcall Vector3::subtract(float *this, float *a, float *b)
{
    float x1 = a[0];
    float y1 = a[1];
    float z1 = a[2];
    float w1 = a[3]; // +0x0C (unused, likely padding or homogeneous component)
    float x2 = b[0];
    float y2 = b[1];
    float z2 = b[2];
    float w2 = b[3]; // +0x0C
    float thisW = this[3]; // preserve original w component

    this[0] = x1 - x2;
    this[1] = y1 - y2;
    this[2] = z1 - z2;
    this[3] = thisW; // restore original w component (not overwritten by subtraction)
}