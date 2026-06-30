// FUNC_NAME: Vector3::normalize
void __fastcall Vector3::normalize(float *outVec)
{
    float fVar1;
    float *inVec;
    float invLen;
    
    fVar1 = *inVec;
    invLen = fVar1 * fVar1 + inVec[1] * inVec[1] + inVec[2] * inVec[2];
    if (invLen <= DAT_00e2cbe0) { // likely zero threshold constant
        invLen = 0.0;
    }
    else {
        invLen = DAT_00e2b1a4 / SQRT(invLen); // DAT_00e2b1a4 = 1.0f (inverse sqrt)
    }
    *outVec = fVar1 * invLen;
    outVec[1] = invLen * inVec[1];
    outVec[2] = invLen * inVec[2];
    return;
}