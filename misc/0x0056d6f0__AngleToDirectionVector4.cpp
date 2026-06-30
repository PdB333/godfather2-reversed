// FUNC_NAME: AngleToDirectionVector4
// Address: 0x0056d6f0
// Role: Converts an angle (in some unit) into a 4-float direction vector with two zeros.
// Uses a global scale factor (DAT_00e2cd54) to convert input to radians or similar.
// First callee (0x00b99fcb) yields the cosine, second (0x00b99e20) yields the sine.
// Stores into array: [0]=0, [1]=cos, [2]=0, [3]=sin.

void AngleToDirectionVector4(float angle, float* outVector4)
{
    // Initialize unused components to zero
    outVector4[0] = 0.0f;
    outVector4[2] = 0.0f;

    // Scale the angle by a global conversion factor (likely degrees to radians)
    float scaledAngle = angle * DAT_00e2cd54;
    double dVal = (double)scaledAngle;

    // Compute cosine and store at index 1 (y component)
    outVector4[1] = (float)CosFunc(dVal);      // FUN_00b99fcb

    dVal = (double)scaledAngle;                 // reload for second call
    // Compute sine and store at index 3 (w component)
    outVector4[3] = (float)SinFunc(dVal);      // FUN_00b99e20
}

// External math functions (assumed to take double from FPU stack)
extern "C" double CosFunc(double x);
extern "C" double SinFunc(double x);

// Global scale factor referenced from data
extern float DAT_00e2cd54;