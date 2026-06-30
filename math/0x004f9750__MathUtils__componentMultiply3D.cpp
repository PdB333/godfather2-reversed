// FUNC_NAME: MathUtils::componentMultiply3D
// Address: 0x004f9750
// Role: Component-wise multiplication of two 4-component vectors, but only first three components are multiplied.
// The fourth component of the output (destination) is left unchanged.
// Note: The original calling convention uses __fastcall with the output pointer in EAX (unusual), but here reconstructed for clarity.

void __fastcall componentMultiply3D(float *out, const float *a, const float *b)
{
    // out is the destination pointer (original EAX)
    // a and b are input vectors (original param_2, param_3)
    // param_1 (ECX) is unused

    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    // out[3] remains unchanged (preserved from prior value)
}