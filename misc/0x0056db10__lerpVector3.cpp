// FUNC_NAME: lerpVector3
// Address: 0x0056db10
// Role: Linear interpolation of a 3D vector (stored as 4 floats, w set to 0)
// Parameters:
//   this (param_1) - pointer to source vector A (at +0x10)
//   param_2 - pointer to source vector B (at +0x10)
//   t (in_XMM1_Da) - interpolation factor (0.0 to 1.0)
//   out (in_EAX) - destination vector (at +0x10)
// Note: The function uses a global constant DAT_00e2b1a4 which is assumed to be 1.0f.

void __thiscall lerpVector3(void* this, void* param_2)
{
    float t; // Interpolation factor passed in XMM1 register
    float oneMinusT;
    float ax, ay, az, aw; // Components of vector A (at this+0x10)
    float bx, by, bz, bw; // Components of vector B (at param_2+0x10)
    float resultX, resultY, resultZ, resultW;
    void* out; // Destination pointer in EAX (output)

    // Assume DAT_00e2b1a4 is 1.0f
    const float one = 1.0f;
    t = in_XMM1_Da; // The float passed in XMM1 register
    oneMinusT = one - t;

    // Load components from source A (at this+0x10)
    ax = *(float*)((int)this + 0x10);
    ay = *(float*)((int)this + 0x14);
    az = *(float*)((int)this + 0x18);
    aw = *(float*)((int)this + 0x1c);

    // Compute (1-t) * A
    resultX = oneMinusT * ax;
    resultY = oneMinusT * ay;
    resultZ = oneMinusT * az;
    resultW = oneMinusT * aw;

    // Load components from source B (at param_2+0x10)
    bx = *(float*)((int)param_2 + 0x10);
    by = *(float*)((int)param_2 + 0x14);
    bz = *(float*)((int)param_2 + 0x18);
    bw = *(float*)((int)param_2 + 0x1c);

    // Add t * B to the result
    resultX = t * bx + resultX;
    resultY = t * by + resultY;
    resultZ = t * bz + resultZ;
    resultW = t * bw + resultW;

    // Store result to output (in_EAX+0x10)
    *(float*)((int)out + 0x10) = resultX;
    *(float*)((int)out + 0x14) = resultY;
    *(float*)((int)out + 0x18) = resultZ;
    *(float*)((int)out + 0x1c) = resultW;

    // Force the fourth component (w) to 0 (typical for 3D vectors)
    *(float*)((int)out + 0x1c) = 0.0f;

    return;
}