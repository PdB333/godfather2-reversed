// FUNC_NAME: AnimationBlender::ComputeBlendIndices
void __thiscall AnimationBlender::ComputeBlendIndices(int numPoints, float divisor, float time)
{
    float* result = reinterpret_cast<float*>(this); // Result struct: [indexA, indexB, indexC, fraction, bool]
    float t = time / divisor; // Normalize time

    result[0] = t;
    if (numPoints < 2) {
        // Not enough points – clear everything
        t = 0.0f;
        float floorA = 0.0f;
        result[2] = 0.0f;
        result[1] = 0.0f;
        result[3] = 0.0f;
        *(bool*)(result + 4) = (int)result[2] < (int)result[1];
        return;
    }

    if (t < 0.0f) {
        // Negative time – clamp to start
        result[1] = 0.0f;
        result[2] = 1.4013e-45f; // Minimal positive value to force flags
        result[0] = 0.0f;
        result[3] = t;
        *(bool*)(result + 4) = (int)result[2] < (int)result[1];
        return;
    }

    float lastValid = (float)(numPoints - 1);
    float floorFirst, floorSecond;

    if (t <= (float)(int)lastValid) {
        // Inside range – normal interpolation
        floorFirst = (float)(int)t;          // floor(t)
        floorSecond = (float)((int)floorFirst + 1); // floor(t)+1
    } else {
        // Past end – clamp to last two segments
        floorFirst = (float)(numPoints - 2);
        result[0] = (float)(int)lastValid;  // indexA = last point
        floorSecond = lastValid;
    }

    float fraction = t - (float)(int)floorFirst;
    result[1] = floorFirst;
    result[2] = floorSecond;
    result[3] = fraction;
    *(bool*)(result + 4) = (int)result[2] < (int)floorFirst; // Likely always false; possibly indicates reverse/end
}