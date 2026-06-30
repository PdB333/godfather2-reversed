// FUNC_NAME: addVec3PreserveW
void __fastcall addVec3PreserveW(float *out, float *a, float *b)
{
    // Adds the x,y,z components of a and b, storing result in out.
    // The w component (index 3) of out is NOT modified.
    out[0] = a[0] + b[0]; // x
    out[1] = a[1] + b[1]; // y
    out[2] = a[2] + b[2]; // z
    // out[3] is preserved – typically homogeneous w or padding
}