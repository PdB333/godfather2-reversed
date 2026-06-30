// FUNC_NAME: randomIntScaled
// Address: 0x005fe000
// Role: Generates a random integer scaled by two global floating-point constants.
// Uses glibc rand() and multiplies by two global scalars (likely from data segment).

#include <cstdlib>

// Global scaling factors (likely from data section at 0x00e44590 and 0x00e44670)
extern float g_randomScaleFactorA;
extern float g_randomScaleFactorB;

int randomIntScaled(void)
{
    int rawRand = rand();
    return (int)((float)rawRand * g_randomScaleFactorA * g_randomScaleFactorB);
}