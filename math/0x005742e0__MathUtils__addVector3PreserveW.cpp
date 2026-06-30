// FUNC_NAME: MathUtils::addVector3PreserveW

void __fastcall MathUtils::addVector3PreserveW(float* out, const float* a, const float* b)
{
    float ax = a[1];
    float ay = a[2];
    float az = a[3];
    float bx = b[1];
    float by = b[2];
    float bz = b[3];
    float originalW = out[3];       // Preserve the 4th component (W) of the destination

    out[0] = a[0] + b[0];
    out[1] = ax + bx;
    out[2] = ay + by;
    out[3] = az + bz;

    out[3] = originalW;             // Restore original W (only x,y,z are added)
}