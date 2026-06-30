// FUNC_NAME: Math::Vector4::subtract3D
// Address: 0x0045c020
// Purpose: Subtract two 4D vectors (x,y,z only; w component of destination is preserved).
//          Uses a non-standard calling convention where the destination pointer is passed in EAX,
//          first input in EDX (param_2), second input on stack (param_3). The 'this' parameter (ECX) is unused.
void __fastcall Math::Vector4::subtract3D(float *dest, float *src1, float *src2) // dest=in_EAX, src1=param_2, src2=param_3
{
    // dest = src1 - src2 for (x,y,z) only; w component of dest unchanged.
    float savedW = dest[3];                     // preserve original w (homogeneous coordinate)
    dest[0] = src1[0] - src2[0];                // +0x00: x
    dest[1] = src1[1] - src2[1];                // +0x04: y
    dest[2] = src1[2] - src2[2];                // +0x08: z
    dest[3] = src1[3] - src2[3];                // +0x0C: w (temporary)
    dest[3] = savedW;                           // restore original w
}