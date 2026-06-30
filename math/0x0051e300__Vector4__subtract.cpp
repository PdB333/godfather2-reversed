// FUNC_NAME: Vector4::subtract
void __fastcall Vector4::subtract(float *this, float *a, float *b)
{
    float wa, xa, ya, za;
    float wb, xb, yb, zb;
    float wOld;

    xa = a[1];
    ya = a[2];
    za = a[3];
    xb = b[1];
    yb = b[2];
    zb = b[3];
    wOld = this[3]; // +0x0C - preserve original w component

    this[0] = a[0] - b[0]; // x
    this[1] = xa - xb;     // y
    this[2] = ya - yb;     // z
    this[3] = za - zb;     // w
    this[3] = wOld;        // restore w to original value
}