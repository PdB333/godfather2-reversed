// FUNC_NAME: MathUtils::computeMinBasedScaledFactor
// Address: 0x005e5c60
// Role: Finds minimum of an array of floats, then computes a scaled factor based on param2, param3 and global thresholds.
// Likely used for damage scaling or force calculation in EARS physics/damage system.
// Constants (from global data):
//   s_fMinThreshold = DAT_00e2e50c (0.0f? unknown)
//   s_fDefaultOutput = DAT_00e2b1a4 (default value when condition fails)
//   s_fTimeThreshold = DAT_00e44598 (threshold for param3)
//   s_fScaleFactor = DAT_00e2afb8 (multiplier)
//   s_fBitmask = DAT_00e44680 (used in weird bitwise float check, possibly a threshold)
//   s_fUpperLimit = DAT_00e4472c (upper bound for interpolation)
//   s_fMaxOutput = DAT_00e2b04c (maximum output value)
//   s_fMinOutput = DAT_00e2cd54 (minimum output value)

bool __thiscall MathUtils::computeMinBasedScaledFactor(
    float* array,                // param_1: pointer to array of floats
    int count,                   // unaff_EDI: number of elements (likely member variable)
    float param2,                // param_2: some scalar
    float param3,                // param_3: time or threshold-related
    float* outValue              // param_4: output value
)
{
    bool success = false;        // uVar1
    float minValue = s_fMinThreshold; // fVar6, initial minimum
    uint processed;              // uVar3

    // Optimized loop for 4+ elements: process 4 at a time
    if (count > 3)
    {
        int batches = (count - 4) / 4 + 1; // number of 4-element batches
        float* cursor = array + 2;         // start at offset 8 (2 floats ahead)
        processed = batches * 4;           // number of elements processed in batches

        do
        {
            if (cursor[-2] < minValue) minValue = cursor[-2];
            if (cursor[-1] < minValue) minValue = cursor[-1];
            if (cursor[0]  < minValue) minValue = cursor[0];
            if (cursor[1]  < minValue) minValue = cursor[1];
            cursor += 4;
            batches--;
        } while (batches != 0);
    }
    else
    {
        processed = 0;
    }

    // Process remaining elements
    for (; processed < count; processed++)
    {
        if (array[processed] < minValue)
            minValue = array[processed];
    }

    float output = s_fDefaultOutput; // fVar5

    // Check if param3 is above a threshold
    if (s_fTimeThreshold < param3)
    {
        // Compute scaled difference from minimum
        float scaled = (param2 - minValue) * param3 * s_fScaleFactor; // fVar6
        success = true;

        // Weird check: possibly a guarded division or saturation
        // The decompiler shows (float)((uint)scaled & s_fBitmask), likely a comparison with threshold
        if (s_fTimeThreshold < scaled) // assuming condition is scaled > threshold, not bitwise
        {
            if (s_fUpperLimit <= scaled)
            {
                *outValue = s_fMaxOutput;
                return success;
            }
            // Interpolation: s_fUpperLimit / (s_fUpperLimit - scaled)
            output = s_fUpperLimit / (s_fUpperLimit - scaled);
            // Clamp between s_fMinOutput and s_fMaxOutput
            if (output > s_fMaxOutput) output = s_fMaxOutput;
            else if (output < s_fMinOutput) output = s_fMinOutput;
        }
    }

    *outValue = output;
    return success;
}