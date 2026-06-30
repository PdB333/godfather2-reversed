// FUNC_NAME: Animation::processNonPowerOfTwoValue
// Function address: 0x0061aad0
// Role: Processes a non-power-of-two integer value by scaling it against a global constant.
// The function calls a series of math helpers to compute a scaled double and apply it.
// The condition (value & (value - 1)) != 0 ensures the input is not a power of two.

#include <cmath>

// External math helpers (addresses in comments)
extern void mathInitHelper();          // FUN_00d3d41f
extern void mathPrepareHelper();       // FUN_00b9af10
extern void setScaledValue(double);    // FUN_00b9cce0
extern void applyScaledValue();        // FUN_00b9a7b0

// Global constant at 0x00e44650
extern double g_scaleConstant;

void Animation::processNonPowerOfTwoValue(void* thisPtr, unsigned int value)
{
    // Check this pointer and that value is NOT a power of two
    if (thisPtr != nullptr && (value & (value - 1)) != 0) {
        double dVal = static_cast<double>(static_cast<int>(value)); // convert to int then double
        mathInitHelper();                                            // 0x00d3d41f
        double dConst = g_scaleConstant;                            // 0x00e44650
        mathInitHelper();                                            // 0x00d3d41f
        mathPrepareHelper();                                         // 0x00b9af10
        // Compute (float division) as float, then promote to double
        double finalVal = static_cast<double>(
            static_cast<float>(dVal) / static_cast<float>(dConst)
        );
        setScaledValue(finalVal);                                    // 0x00b9cce0
        applyScaledValue();                                          // 0x00b9a7b0
    }
}