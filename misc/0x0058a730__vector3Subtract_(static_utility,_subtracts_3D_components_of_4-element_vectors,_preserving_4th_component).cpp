// FUNC_NAME: vector3Subtract (static utility, subtracts 3D components of 4-element vectors, preserving 4th component)
void __fastcall vector3Subtract(float* out, float* a, float* b)
{
    // a and b are 4-element float arrays (x,y,z,w)
    // out is destination, also 4-element; its w component is preserved.

    float ax = a[1]; // a[1] = a->y
    float ay = a[2]; // a->z
    float aw = a[3]; // a->w

    float bx = b[1]; // b->y
    float by = b[2]; // b->z
    float bw = b[3]; // b->w

    float savedW = out[3]; // preserve original w

    out[0] = a[0] - b[0]; // x
    out[1] = ax - bx;     // y
    out[2] = ay - by;     // z
    out[3] = aw - bw;     // temporary store w difference (overwritten next line)

    out[3] = savedW;      // restore original w component
}