// FUNC_NAME: AngularSpline::evaluate

// Address: 0x0058c8e0
// Spline evaluation for angular curves with modulo/wrapping support.
// Computes a blended value from 2 or 3 control points using an input parameter t and a blend delta.
// The curve data pointer (aCurve) contains:
//   +0x00: (unused here)
//   +0x01: number of segments (numPoints)
//   +0x0C: pointer to array of segment structures (first)
//   +0x10: pointer to array of segment structures (second)
//   +0x14: pointer to array of segment structures (third, only if numPoints >= 3)
// Each segment structure at offset +0x02 holds an index into the value array.
// The value array (pValues) is a base pointer to floats, with a count at pValues[1].

float AngularSpline::evaluate(
    void* this,                    // ECX – class instance (unused in this function)
    CurveData* aCurve,             // curve definition
    FloatArrayDesc* pValues,       // array of float control values and its size
    float t,                       // input parameter
    float blendDelta,              // delta for blending
    void* output1,                 // unknown pointer (could be output)
    void* output2                  // unknown pointer
)
{
    int numPoints;
    short index1, index2, index3;
    float val1, val2, val3;
    float argLocal, segLocal[2];
    float modVal;
    int result1, result2, result3;

    // Minimum 2 points required
    numPoints = *(char*)((int)aCurve + 1);
    if (numPoints < 2)
        return 0.0f;

    // Get pointers to segment index arrays
    int* segArr1 = *(int**)((int)aCurve + 0x0C);
    int* segArr2 = *(int**)((int)aCurve + 0x10);

    // First index: segment 1
    index1 = *(short*)((int)segArr1 + 2);
    if ((unsigned int)pValues[1] <= (unsigned int)(int)index1)
    {
        // Out of bounds – trap or log
        float dummy = 0.0f;
        FUN_00591c00(&dummy);
    }
    val1 = *(float*)(pValues[0] + index1 * 4);   // pValues->base + index*4

    // Second index: segment 2
    index2 = *(short*)((int)segArr2 + 2);
    if ((unsigned int)pValues[1] <= (unsigned int)(int)index2)
    {
        float dummy = 0.0f;
        FUN_00591c00(&dummy);
    }
    val2 = *(float*)(pValues[0] + index2 * 4);

    // Compute angular ranges: val1 and val2 relative to a global wrapping constant (likely 2*PI)
    float twoPi = DAT_00e2b1a4;   // 6.283185f
    float range1 = val1 - twoPi;
    float range2 = val2 - twoPi;

    // Adjust the input parameter t to be within the range of interest
    // (wrap handling for angles)
    if (t == range1)
    {
        argLocal = t;
    }
    else
    {
        // The following int casts are questionable – likely a float comparison trick
        // Original: if (|t - range1| > 2) then goto (set argLocal = t) else fallthrough
        // We'll approximate as epsilon check:
        float diff = t - range1;
        if (diff < 0.0f) diff = -diff;
        if (diff > 2.0f)   // arbitrary threshold, likely 2.0f units (maybe degrees?)
            argLocal = range1;
        else
            argLocal = t;
    }

    if (t == range2)
    {
        modVal = t;
    }
    else
    {
        float diff = t - range2;
        if (diff < 0.0f) diff = -diff;
        if (diff > 2.0f)
            modVal = range2;
        else
            modVal = t;
    }

    // If val1 equals the angular constant, treat as fractional part (no range)
    if (val1 == twoPi)
    {
        argLocal = argLocal - floorf(argLocal);
    }
    else if (range1 < argLocal)
    {
        // Wrap argLocal into [0, range1) by subtracting multiples of range1
        argLocal = argLocal - floorf(argLocal / range1) * range1;
    }

    if (val2 == twoPi)
    {
        modVal = floorf(modVal);
    }
    else
    {
        if (modVal <= range2)
            ; // nothing
        else
            modVal = modVal - floorf(modVal / range2) * range2;
    }
    // modVal now lies in [0, range2)

    // Three-point path (when numPoints >= 3)
    if (numPoints >= 3)
    {
        int* segArr3 = *(int**)((int)aCurve + 0x14);
        index3 = *(short*)((int)segArr3 + 2);
        if ((unsigned int)pValues[1] <= (unsigned int)(int)index3)
        {
            float dummy = 0.0f;
            FUN_00591c00(&dummy);
        }
        val3 = *(float*)(pValues[0] + index3 * 4);

        float range3 = val3 - twoPi;
        float localT3;
        if (val3 == twoPi)
            localT3 = t - floorf(t);
        else
        {
            if (range3 < t)
                localT3 = t - floorf(t / range3) * range3;
            else
                localT3 = t;
        }

        // Compute local parameters with blendDelta
        segLocal[0] = (modVal - t) + blendDelta;   // for segment 2
        segLocal[1] = (argLocal - t) + blendDelta; // for segment 1
        float segLocal2 = (localT3 - t) + blendDelta; // for segment 3

        float pt = t;
        if (pt < val1)  // clamp? Possibly push stack
            FUN_0058ac50();
        if (pt < val2)
            FUN_0058ac50();
        if (pt < val3)
            FUN_0058ac50();

        // Evaluate each segment using intermediate function
        result1 = FUN_00590360(this, pValues, argLocal, segLocal[1], output1, output2);
        result2 = FUN_00590360(this, pValues, modVal, segLocal[0], output1, output2);
        result3 = FUN_00590360(this, pValues, localT3, segLocal2, output1, output2);

        // Blend results of segments 2 and 3 first
        if (result2 == 0 || result3 == 0)
            result2 = 0;
        else
            result2 = FUN_00584240(result2, result3, output1);

        // Blend the final result
        if (result1 == 0 || result2 == 0)
        {
            argLocal = 0.0f;
            FUN_0056fb60();
            FUN_0056fb60();
        }
        else
        {
            argLocal = (float)FUN_00584240(result1, result2, output1);
            FUN_0056fb60();
            FUN_0056fb60();
        }
    }
    else // Two-point path
    {
        // Compute local parameters for each segment
        segLocal[0] = (modVal - t) + blendDelta;
        segLocal[1] = (argLocal - t) + blendDelta;

        float pt = t;
        if (pt < val1)
            FUN_0058ac50();
        if (pt < val2)
            FUN_0058ac50();

        // Evaluate both segments
        result1 = FUN_00590360(this, pValues, argLocal, segLocal[1], output1, output2);
        result2 = FUN_00590360(this, pValues, modVal, segLocal[0], output1, output2);

        // Blend
        if (result1 == 0 || result2 == 0)
            argLocal = 0.0f;
        else
            argLocal = (float)FUN_00584240(result1, result2, output1);
    }

    // Cleanup stack operations
    FUN_0056fb60();
    FUN_0056fb60();

    return argLocal;
}

// Note: The following functions are not defined here but are used:
//   FUN_00591c00 – likely an error/assert handler
//   FUN_0058ac50 – unknown math stack operation (push)
//   FUN_00590360 – evaluates a single segment value (Hermite or Catmull-Rom?)
//   FUN_00584240 – blends two segment results (weighted sum?)
//   FUN_0056fb60 – unknown math stack cleanup (pop)
//   DAT_00e2b1a4 – global constant (probably 2*PI)