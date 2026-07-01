// FUNC_NAME: Vector3::subtract
void __fastcall Vector3::subtract(float *result, float *a, float *b)
{
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // w component (unused in subtraction, preserved)
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // w component (unused in subtraction)

    result[0] = ax - bx;
    result[1] = ay - by;
    result[2] = az - bz;
    result[3] = aw; // preserve original w component
}