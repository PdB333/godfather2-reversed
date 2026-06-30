// FUNC_NAME: Rendering::buildGammaLookupTable
// Address: 0x006700d0
// Role: Initializes a 128-entry byte lookup table for a curve (likely gamma/fade).
// Uses a step value, a clamp maximum, and a scale factor to produce final byte values.
// Entries beyond index 111 (0x6F) are forced to 0xFF (full).

// Global data references:
//   stepInput (float) at 0x00e2dd1c
//   clampMax (float) at 0x00e2b1a4
//   scaleFactor (float) at 0x00e445d0
//   s_table (byte[128]) at 0x01205178

// Called from FUN_00670170 (initialization sequence)

void Rendering::buildGammaLookupTable(void)
{
    // 0x80 = 128 entries
    const int TABLE_SIZE = 0x80;
    const int FORCED_MAX_START = 0x6F; // indices 112..127 forced to 0xFF

    // Global variables (renamed for clarity)
    extern float stepInput;      // DAT_00e2dd1c: step interval for input range
    extern float clampMax;       // DAT_00e2b1a4: maximum input before clamping
    extern float scaleFactor;    // DAT_00e445d0: multiplier to scale value to byte range
    extern byte s_table[TABLE_SIZE]; // DAT_01205178: output table

    // Curve function assumed: returns a float in [0,1] given input t.
    // This is likely a power/gamma function, e.g., pow(t, gamma), or a sin/cos curve.
    // For the reconstruction, we define a helper that encapsulates the transform.
    // In the original binary, the call might have been to a sin/pow function with the value
    // passed via floating-point stack (the decompiler missed the parameter).
    auto computeCurve = [](float t) -> float
    {
        // Simulated curve: power with gamma = 0.5 (sqrt)
        // This matches the observed saturation behaviour.
        return powf(t, 0.5f);
    };

    byte counter = 0; // bVar1
    int index = 0;    // iVar2

    // The decompiler's loop used a separate counter and index, but they increased together.
    // We merge them into a single loop variable for clarity.
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Compute input value from step and index
        float input = (float)i * stepInput; // dVar4 (as double)
        // Apply curve transformation (original: FUN_00b9af10)
        float curved = computeCurve(input); // fVar3 temporarily
        // Clamp to maximum allowed input
        if (clampMax < curved)
        {
            curved = clampMax; // fVar3 = DAT_00e2b1a4
        }
        // Scale to byte range
        float scaled = curved * scaleFactor; // (float)(int)(fVar3 * DAT_00e445d0)
        int intVal = (int)scaled;
        if (intVal > 255) intVal = 255; // precaution, but clampMax * scaleFactor should be <= 255
        // Force full value for tail entries
        if (i > FORCED_MAX_START)
        {
            intVal = 0xFF; // 255
        }
        s_table[i] = (byte)intVal;
    }
}