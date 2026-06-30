// FUNC_NAME: vector4ScaleAdd
// Function address: 0x0056c9c0
// Description: Performs a scaled addition on the first three components of 4-element vectors,
// preserving the original w-component of the output. Equivalent to:
// out->x = s * a->x + b->x
// out->y = s * a->y + b->y
// out->z = s * a->z + b->z
// out->w unchanged (preserved from previous value)
// This is used in the EARS engine math library for operations like quaternion composite transforms.

void __fastcall vector4ScaleAdd(float* out, float* a, float* b, float s)
{
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float originalOutW = out[3];  // preserve original w

    float bx = b[0];
    float by = b[1];
    float bz = b[2];

    out[0] = s * ax + bx;
    out[1] = s * ay + by;
    out[2] = s * az + bz;
    out[3] = originalOutW;       // restore w
}