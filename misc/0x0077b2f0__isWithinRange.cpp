// FUNC_NAME: isWithinRange
// Function address: 0x0077b2f0
// Role: Checks if a float value falls within a predefined range defined by game globals.
// Returns false (0) if value is within [gLowerBound, gBase - gTolerance], true (1) otherwise.

// Global addresses (from Ghidra):
// 0x00d577a0 - Lower bound of the range.
// 0x01205228 - Base value used to compute upper bound.
// 0x00d68540 - Tolerance subtracted from base to form effective upper bound.

extern float gLowerBound;   // +0x00d577a0
extern float gBase;         // +0x01205228
extern float gTolerance;    // +0x00d68540

bool isWithinRange(float* value) {
    if ((gLowerBound <= *value) && ((gBase - *value) <= gTolerance)) {
        return false; // value is inside the acceptable range
    }
    return true; // value is outside the acceptable range
}