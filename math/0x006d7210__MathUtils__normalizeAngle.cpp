// FUNC_NAME: MathUtils::normalizeAngle
// Address: 0x006d7210
// Role: Normalizes an angle (in degrees or radians) by adding/subtracting a constant (likely 360.0f).
//       If input pointer is null, it may generate a random angle or return -360.0 based on editor state.

#include <cmath>

// Global data (addresses from Ghidra)
extern void* DAT_012233a0;          // pointer to some engine structure; +4 holds a state flag
extern float DAT_00e44748;          // scale factor (e.g., degrees per radian: 57.2958f)
extern float DAT_00e44600;          // wrap range (e.g., 360.0f)

// Helper functions (unknown implementations)
extern float FUN_00799230();        // likely returns a random float in [0,1) or similar
extern void FUN_00b9a9fa();         // side-effect call, possibly trigonometric or debug

float normalizeAngle(float* angleIn) {
    float result;

    if (angleIn == nullptr) {
        result = 0.0f;
        // Check editor/release flag: if true, jump to wrap without random
        if ((**(int**)((char*)DAT_012233a0 + 4) == 0) || 
            (**(int**)((char*)DAT_012233a0 + 4) == 0x1f30)) {
            goto LAB_006d7281;
        }
        // Generate a random float value
        float randomVal = (float)FUN_00799230();
        result = randomVal;
    } else {
        double valDouble = (double)*angleIn;      // promote to double
        FUN_00b9a9fa();                           // unknown routine
        result = (float)(valDouble * DAT_00e44748); // apply scale (e.g., rad→deg)
    }

    // Wrap angle to range [-DAT_00e44600, DAT_00e44600] by single add/subtract
    if (result < 0.0f) {
        return (float)(result + DAT_00e44600);
    }

LAB_006d7281:
    return (float)(result - DAT_00e44600);
}