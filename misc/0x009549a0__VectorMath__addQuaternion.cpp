// FUNC_NAME: VectorMath::addQuaternion
void __fastcall VectorMath::addQuaternion(undefined4 param_1, float *pQ1, float *pQ2)
{
    float x1, y1, z1, w1;
    float x2, y2, z2, w2;
    float *outQ; // in_EAX

    // Load first quaternion components
    x1 = pQ1[1]; // +0x04 (quaternion x)
    y1 = pQ1[2]; // +0x08 (quaternion y)
    z1 = pQ1[3]; // +0x0C (quaternion z)
    // Note: pQ1[0] is the real part (w) but appears unused in vector addition

    // Load second quaternion components
    x2 = pQ2[1]; // +0x04 (quaternion x)
    y2 = pQ2[2]; // +0x08 (quaternion y)
    z2 = pQ2[3]; // +0x0C (quaternion z)

    // Save output quaternion's real part (w) before overwriting
    w1 = outQ[3]; // +0x0C (quaternion w component to preserve)

    // Perform element-wise addition of quaternion vector parts (x, y, z)
    // Note: This only adds the vector components, not the scalar (w) part
    outQ[0] = pQ1[0] + pQ2[0]; // +0x00 (quaternion w: scalar part sum) - actually pQ1[0] is w, but this mismatches typical quaternion conventions
    outQ[1] = x1 + x2; // +0x04 (x component)
    outQ[2] = y1 + y2; // +0x08 (y component)
    outQ[3] = z1 + z2; // +0x0C (z component)

    // Restore the output's original w component (preserves w from output, not sum)
    outQ[3] = w1;
    return;
}