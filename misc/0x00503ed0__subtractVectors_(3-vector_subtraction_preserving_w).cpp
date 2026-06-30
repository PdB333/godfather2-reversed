// FUNC_NAME: subtractVectors (3-vector subtraction preserving w)
// Function address: 0x00503ed0
// Performs 3-component vector subtraction (a - b) into output, leaving the fourth component unchanged.
void __fastcall subtractVectors(float* pOut, const float* pA, const float* pB)
{
    float savedW = pOut[3]; // Preserve original w component
    pOut[0] = pA[0] - pB[0];
    pOut[1] = pA[1] - pB[1];
    pOut[2] = pA[2] - pB[2];
    pOut[3] = savedW; // Restore original w
}