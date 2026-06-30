// FUNC_NAME: Vector4::scaleAndAddPreserveW
// Address: 0x00473510
// Returns: void
// This function computes: result = scalar * a + b
// Then restores result.w to its original value (i.e., preserves the w component of the output vector)
// Arguments:
//   this (ecx): pointer to the result vector (4 floats)
//   a (edx?): pointer to first source vector (4 floats)
//   b (stack): pointer to second source vector (4 floats)
//   scalar (stack): scaling factor

void __thiscall Vector4::scaleAndAddPreserveW(float* result, float* a, float* b, float scalar)
{
    float origW = result[3]; // save original w component

    result[0] = scalar * a[0] + b[0];
    result[1] = scalar * a[1] + b[1];
    result[2] = scalar * a[2] + b[2];
    result[3] = scalar * a[3] + b[3]; // compute as usual

    result[3] = origW; // restore original w
}