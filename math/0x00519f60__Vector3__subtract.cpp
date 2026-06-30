// FUNC_NAME: Vector3::subtract
void __fastcall Vector3::subtract(float *thisResult, float *a, float *b)
{
    // Subtract two 3D vectors (a - b) and store result in thisResult
    // Note: The 4th component (w) is preserved from the original thisResult value
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // w component (may be used for homogeneous coordinates)
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // w component (unused in subtraction)
    float originalW = thisResult[3]; // Preserve original w component

    thisResult[0] = ax - bx;
    thisResult[1] = ay - by;
    thisResult[2] = az - bz;
    thisResult[3] = aw - bw; // Subtract w components
    thisResult[3] = originalW; // Restore original w component (overwrites subtraction)
}