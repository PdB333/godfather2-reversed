// FUNC_NAME: calculateScaledProductFromGlobal

// Function reads two integer fields from a global manager (offset +0x394 and +0x3a8),
// multiplies them, scales by a float constant, and rounds to int.

extern float DAT_00e44578;   // rounding adjustment for negative products (likely 0.0f or 0.5f)
extern float DAT_00d5ef84;   // scale factor
extern uint DAT_01223484;     // global pointer to manager/singleton

int calculateScaledProductFromGlobal(void)
{
    int val1 = 0;
    int val2 = 0;

    if (DAT_01223484 != 0) {
        val1 = *(int *)(DAT_01223484 + 0x394);  // first field (e.g. width)
        val2 = *(int *)(DAT_01223484 + 0x3a8);  // second field (e.g. height)
    }

    // Compute product as float, handle negative rounding
    float product = (float)(val1 * val2);
    if (val1 * val2 < 0) {
        product = product + DAT_00e44578;   // adjust for negative sign
    }

    // Scale and round to nearest integer
    return (int)(long long)ROUND(product * DAT_00d5ef84);
}