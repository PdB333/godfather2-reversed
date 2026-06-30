// FUNC_NAME: Vector4::add
void __fastcall Vector4::add(float *thisResult, float *vecA, float *vecB)
{
    float a1, a2, a3, a4;
    float b1, b2, b3, b4;

    a1 = vecA[1]; // +0x04
    a2 = vecA[2]; // +0x08
    a3 = vecA[3]; // +0x0C
    b1 = vecB[1]; // +0x04
    b2 = vecB[2]; // +0x08
    b3 = vecB[3]; // +0x0C
    a4 = thisResult[3]; // +0x0C - preserve original w component

    thisResult[0] = vecA[0] + vecB[0]; // x = ax + bx
    thisResult[1] = a1 + b1;           // y = ay + by
    thisResult[2] = a2 + b2;           // z = az + bz
    thisResult[3] = a3 + b3;           // w = aw + bw
    thisResult[3] = a4;                // restore original w (overwrites previous w)
}