// FUNC_NAME: evaluateCurveValue
// Function address: 0x005903d0
// Reconstructed from Ghidra decompilation.
// Likely evaluates a simple two-point curve function.
// Structure at param_2:
//   +0x01: byte - count or type flag (if < 2, returns 1.0f)
//   +0x04: float* - pointer to array of floats (at least 4 floats: [x0, y0, x1, y1] or similar)
// The function also takes a float parameter passed in XMM0 (inputValue).
// If the fourth float (index 3) equals 1.4013e-45 (sentinel), returns x0 + y0 + inputValue.
// Otherwise, if inputValue < y0, returns x0 + y0; else returns x0 + inputValue.

float __cdecl evaluateCurveValue(void* unused, struct CurveData* curve, float inputValue)
{
    float fVar1;
    float* points;
    
    // Check if the curve has less than 2 points (or type < 2)
    if (*(char*)(curve + 1) < 2) {
        return 1.0f;
    }
    
    // Two calls to an unknown function (possibly debug lock or assertion)
    FUN_00591160();
    points = *(float**)(curve + 4);
    FUN_00591160();
    
    // Read the first two floats from the points array
    fVar1 = points[1]; // Second float (y0 if pair is [x,y] or first y)
    
    // Check sentinel on fourth float
    if (points[3] == 1.4013e-45f) {
        return points[0] + fVar1 + inputValue;
    }
    
    if (inputValue < fVar1) {
        return points[0] + fVar1;
    }
    
    return points[0] + inputValue;
}