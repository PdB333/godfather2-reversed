// FUNC_NAME: lerpVector4PreservingW
// Address: 0x00508b30
// Role: Interpolates the x,y,z components of two 4-component vectors (float[4]) into the output vector,
// preserving the original w component of the output. Used for blending positions or colors while keeping
// a separate homogeneous coordinate or alpha channel unchanged.
void __fastcall lerpVector4PreservingW(float* output, const float* input1, const float* input2, float t)
{
    float origW = output[3]; // save output's original w component (+0x0C)

    // Blend x, y, z components: output = input1 * t + input2
    output[0] = t * input1[0] + input2[0]; // +0x00
    output[1] = t * input1[1] + input2[1]; // +0x04
    output[2] = t * input1[2] + input2[2]; // +0x08

    // Preserve the original w component (ignoring the computed blend for w)
    output[3] = origW; // +0x0C
}