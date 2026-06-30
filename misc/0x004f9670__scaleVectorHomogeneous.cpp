// FUNC_NAME: scaleVectorHomogeneous
void __fastcall scaleVectorHomogeneous(float* out, const float* in, float scalar)
{
    // Save original w component of output vector (homogeneous coordinate)
    float savedW = out[3];

    // Scale the x, y, z components by scalar from input
    out[0] = scalar * in[0];  // x
    out[1] = scalar * in[1];  // y
    out[2] = scalar * in[2];  // z

    // Multiply the w component but then restore original value to preserve homogeneous scale
    out[3] = scalar * in[3];  // temporary, then overwritten
    out[3] = savedW;          // restore original w
}