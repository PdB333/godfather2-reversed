// FUNC_NAME: computeSquaresAndScaledSum
// Address: 0x00768f80
// Role: Computes squares of two parameters and the square of their sum, 
//       and a scaled version of the square of the sum using a global multiplier.
//       Stores results into global variables used elsewhere (likely for distance/damage falloff).

// Global variables (addresses from Ghidra):
extern float gSqrParam1;      // 0x00e51bb8
extern float gSqrParam2;      // 0x00e51bc0
extern float gScaledSqrSum;   // 0x00e51bbc
extern float gSqrSum;         // 0x00e51bc4
extern float gSomeMultiplier; // 0x00d5c458

void computeSquaresAndScaledSum(float param1, float param2)
{
    float sum = param1 + param2;

    gSqrParam2 = param2 * param2;                    // param2^2
    gSqrParam1 = param1 * param1;                    // param1^2
    gScaledSqrSum = (sum * gSomeMultiplier) * (sum * gSomeMultiplier); // (sum * multiplier)^2
    gSqrSum = sum * sum;                             // sum^2
}