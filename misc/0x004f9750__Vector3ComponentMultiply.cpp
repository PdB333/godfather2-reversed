// FUNC_NAME: Vector3ComponentMultiply
// Address: 0x004f9750
// Role: Component-wise multiplication of two 4-element vectors, preserving the 4th (w) component.
// Assumes x86 fastcall with out pointer in EAX, first vector in EDX, second vector on stack.

void __fastcall Vector3ComponentMultiply(float* out, int unused /*ECX*/, const float* a /*EDX*/, const float* b /*stack*/)
{
    // Save original w value of output vector
    float savedW = out[3];

    // Multiply first three components
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];

    // Restore w – preserves original value (only x,y,z are multiplied)
    out[3] = savedW;
}