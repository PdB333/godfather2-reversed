// FUNC_NAME: vectorCrossProduct
// Function at 0x004f30e0: Computes the cross product of two 4-component vectors, ignoring the w components.
// The result is stored in the output pointer (passed in EAX), preserving the output's original w.
// Cross product order: (b x a), i.e., param_3 cross param_2.

void __fastcall vectorCrossProduct(float* out, const float* a, const float* b)
{
    float ax = a[0];   // +0x00
    float ay = a[1];   // +0x04
    float az = a[2];   // +0x08
    // a[3] ignored
    float bx = b[0];   // +0x00
    float by = b[1];   // +0x04
    float bz = b[2];   // +0x08
    float bw = b[3];   // +0x0C, not used in cross product
    float wOriginal = out[3]; // preserve output w

    out[0] = by * az - bz * ay; // y2*z1 - z2*y1
    out[1] = bz * ax - bx * az; // z2*x1 - x2*z1
    out[2] = bx * ay - by * ax; // x2*y1 - y2*x1
    out[3] = wOriginal;
}