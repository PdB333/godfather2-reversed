// FUNC_NAME: multiplyBigIntByScalar (TNL/BigNum multiplication)
// Function address: 0x00668f50
// Description: Multiplies a big integer (stored as 28-bit limbs in 32-bit words) by a 32-bit scalar.
// Uses base 2^28 representation. The input is described by param_1 (pointer to struct with length, capacity, unused?, data pointer).
// The output is written to param_3 (similar struct). Helper FUN_00667740 likely handles reallocation/capacity checking.
// Returns 0 on success, non-zero if capacity check fails.

#include <cstdint>

int multiplyBigIntByScalar(int *inputStruct, uint32_t multiplier, int *outputStruct)
{
    int iVar1;
    uint32_t carry;
    int iVar3;
    uint32_t *inputData;
    uint32_t *outputData;
    uint64_t product;
    uint32_t temp;
    uint32_t limbCount;

    // Check if we have room in the output: input length+1 <= output capacity, or call helper to expand.
    if ((*inputStruct + 1 <= outputStruct[1]) || (iVar1 = FUN_00667740(), iVar1 == 0))
    {
        // Perform multiplication for each limb
        iVar1 = *outputStruct;                    // output length (will be overwritten)
        outputStruct[2] = inputStruct[2];          // copy some field (likely overflow/exponent?)
        inputData = (uint32_t *)inputStruct[3];    // pointer to input limb array
        outputData = (uint32_t *)outputStruct[3];  // pointer to output limb array
        iVar3 = 0;
        carry = 0;
        limbCount = *inputStruct;                  // number of input limbs

        if (0 < limbCount)
        {
            do
            {
                // Multiply current limb by multiplier, add previous carry
                product = (uint64_t)(*inputData) * (uint64_t)(multiplier);
                temp = (uint32_t)(product + (uint64_t)carry);
                carry = (temp >> 28) | (uint32_t)((product >> 32) << 4);
                *outputData = temp & 0xFFFFFFF;    // store only 28 bits
                iVar3++;
                inputData++;
                outputData++;
            } while (iVar3 < limbCount);
        }

        // Store final carry as last limb (only if not zero)
        *outputData = carry;

        // If output was longer than input, zero remaining limbs
        if (iVar3 < iVar1)
        {
            for (int i = iVar1 - iVar3; i != 0; i--)
            {
                outputData++;
                *outputData = 0;
            }
        }

        // Update output length (input length + 1)
        *outputStruct = limbCount + 1;

        // Trim trailing zero limbs (but keep at least one)
        if (0 < limbCount + 1)
        {
            do
            {
                if (*(int *)(outputStruct[3] + -4 + *outputStruct * 4) != 0) break;
                iVar1 = *outputStruct - 1;
                *outputStruct = iVar1;
            } while (0 < iVar1);
        }

        // If result is zero, clear the exponent/overflow field
        if (*outputStruct == 0)
        {
            outputStruct[2] = 0;
        }

        iVar1 = 0; // success
    }

    return iVar1; // 0 on success, non-zero if capacity check failed
}