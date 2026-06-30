// FUNC_NAME: subVector3PreserveW
void __fastcall subVector3PreserveW(float *dest, float *a, float *b)
{
    // Preserve original w component of dest
    float origW = dest[3];
    
    // Subtract only x, y, z components
    float ax = a[0], ay = a[1], az = a[2], aw = a[3];
    float bx = b[0], by = b[1], bz = b[2], bw = b[3];
    
    dest[0] = ax - bx;
    dest[1] = ay - by;
    dest[2] = az - bz;
    
    // w component (index 3) is not modified by subtraction
    dest[3] = origW;
}