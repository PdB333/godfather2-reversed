// FUNC_NAME: CubicSpline::evaluateAtTime
void __fastcall CubicSpline::evaluateAtTime(void* this, int splineData, float time, float* outResult)
{
    // splineData layout:
    // +0x10: int mNumKnots (count of knots)
    // +0x18: float* mKnotPositions (array of time values)
    // +0x14: float* mCoefficients (array of cubic coefficients, 4 floats per segment)
    // +0x1c: float* mEndValues (values at the last knot for each dimension)
    
    // Evaluate X component
    float* knotPositions = *(float**)(splineData + 0x18);
    float result = 0.0f;
    
    if (*knotPositions < time)
    {
        int numKnots = *(int*)(splineData + 0x10);
        if (time < knotPositions[numKnots - 1])
        {
            int segmentIndex = 0;
            float* currentKnot = knotPositions;
            if (0 < numKnots)
            {
                do {
                    if (time < currentKnot[1])
                    {
                        float t = time - knotPositions[segmentIndex];
                        float* coeffs = (float*)(segmentIndex * 0x10 + *(int*)(splineData + 0x14));
                        // Cubic Hermite interpolation
                        result = ((coeffs[0] * t + coeffs[1]) * t + coeffs[2]) * t + coeffs[3];
                        goto LAB_EVAL_Y;
                    }
                    segmentIndex = segmentIndex + 1;
                    currentKnot = currentKnot + 1;
                } while (segmentIndex < numKnots);
            }
            result = 0.0f; // Should not reach here
        }
        else
        {
            // Beyond last knot, use end value
            result = *(float*)(*(int*)(splineData + 0x1c) + -4 + numKnots * 4);
        }
    }
    else
    {
        // Before first knot, use first value
        result = **(float**)(splineData + 0x1c);
    }
    
LAB_EVAL_Y:
    // Evaluate Y component (same logic, different data offsets)
    knotPositions = *(float**)(splineData + 0x28);
    outResult[0] = result;
    
    if (*knotPositions < time)
    {
        int numKnots = *(int*)(splineData + 0x20);
        if (time < knotPositions[numKnots - 1])
        {
            int segmentIndex = 0;
            float* currentKnot = knotPositions;
            if (0 < numKnots)
            {
                do {
                    if (time < currentKnot[1])
                    {
                        float t = time - knotPositions[segmentIndex];
                        float* coeffs = (float*)(segmentIndex * 0x10 + *(int*)(splineData + 0x24));
                        result = ((coeffs[0] * t + coeffs[1]) * t + coeffs[2]) * t + coeffs[3];
                        goto LAB_EVAL_Z;
                    }
                    segmentIndex = segmentIndex + 1;
                    currentKnot = currentKnot + 1;
                } while (segmentIndex < numKnots);
            }
            result = 0.0f;
        }
        else
        {
            result = *(float*)(*(int*)(splineData + 0x2c) + -4 + numKnots * 4);
        }
    }
    else
    {
        result = **(float**)(splineData + 0x2c);
    }
    
LAB_EVAL_Z:
    // Evaluate Z component (same logic, different data offsets)
    knotPositions = *(float**)(splineData + 0x38);
    outResult[1] = result;
    
    if (time <= *knotPositions)
    {
        outResult[2] = **(float**)(splineData + 0x3c);
        return;
    }
    
    int numKnots = *(int*)(splineData + 0x30);
    if (time < knotPositions[numKnots - 1])
    {
        int segmentIndex = 0;
        float* currentKnot = knotPositions;
        if (0 < numKnots)
        {
            do {
                if (time < currentKnot[1])
                {
                    float t = time - knotPositions[segmentIndex];
                    float* coeffs = (float*)(segmentIndex * 0x10 + *(int*)(splineData + 0x34));
                    outResult[2] = ((coeffs[0] * t + coeffs[1]) * t + coeffs[2]) * t + coeffs[3];
                    return;
                }
                segmentIndex = segmentIndex + 1;
                currentKnot = currentKnot + 1;
            } while (segmentIndex < numKnots);
        }
        outResult[2] = 0.0f;
        return;
    }
    
    outResult[2] = *(float*)(*(int*)(splineData + 0x3c) + -4 + numKnots * 4);
}