// FUNC_NAME: Vector4::subtractAndPreserveW
// Function address: 0x00975e20
// Subtracts two 4-component vectors, storing the difference in x,y,z but preserving the original w of 'this'.
void __fastcall Vector4::subtractAndPreserveW(float *this, const float *a, const float *b)
{
    float savedW = this[3];          // +0x0C: w component
    this[0] = a[0] - b[0];           // +0x00: x
    this[1] = a[1] - b[1];           // +0x04: y
    this[2] = a[2] - b[2];           // +0x08: z
    this[3] = a[3] - b[3];           // compute difference for w
    this[3] = savedW;                // restore original w (ignoring the subtraction result)
}