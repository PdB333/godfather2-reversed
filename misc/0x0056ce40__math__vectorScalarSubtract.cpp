// FUNC_NAME: math::vectorScalarSubtract
void __cdecl vectorScalarSubtract(float *inVec, float *outVec)
{
    // Global scalar constant (likely from data section; possibly a fixed point like world center)
    float constVal = DAT_00e44564;  // +0x0 constant value used for x,y,z subtraction

    outVec[0] = constVal - inVec[0];
    outVec[1] = constVal - inVec[1];
    outVec[2] = constVal - inVec[2];
    outVec[3] = inVec[3];  // w component passes through unmodified
}