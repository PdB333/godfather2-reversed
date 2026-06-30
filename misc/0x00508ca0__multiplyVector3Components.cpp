//FUNC_NAME: multiplyVector3Components
void __fastcall multiplyVector3Components(float *out, float *a, float *b)
{
    // Component-wise multiplication of the first three components (x,y,z) of two 4D vectors.
    // The fourth component (w) of the output is preserved unchanged.
    float ay = a[1];
    float az = a[2];
    float aw = a[3];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];
    float savedW = out[3]; // preserve original w

    out[0] = a[0] * b[0]; // x
    out[1] = ay * by;     // y
    out[2] = az * bz;     // z
    out[3] = aw * bw;     // temporary w product (overwritten)
    out[3] = savedW;      // restore original w
}