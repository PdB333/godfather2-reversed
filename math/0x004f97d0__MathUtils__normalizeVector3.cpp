// FUNC_NAME: MathUtils::normalizeVector3
void __fastcall MathUtils::normalizeVector3(float *outVec, float *inVec)
{
    float fVar1;
    float fVar2;
    
    fVar1 = *inVec;
    fVar2 = fVar1 * fVar1 + inVec[1] * inVec[1] + inVec[2] * inVec[2]; // Compute squared length
    if (fVar2 <= DAT_00e2cbe0) { // Compare to epsilon (likely 0.0f or very small)
        fVar2 = 0.0f; // Zero vector, set length to 0
    }
    else {
        fVar2 = DAT_00e2b1a4 / SQRT(fVar2); // Compute 1/length (DAT_00e2b1a4 is likely 1.0f)
    }
    *outVec = fVar1 * fVar2; // Normalize x component
    outVec[1] = fVar2 * inVec[1]; // Normalize y component
    outVec[2] = fVar2 * inVec[2]; // Normalize z component
    return;
}