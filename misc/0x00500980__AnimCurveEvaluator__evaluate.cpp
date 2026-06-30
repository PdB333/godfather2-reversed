// FUNC_NAME: AnimCurveEvaluator::evaluate

class AnimCurveEvaluator {
public:
    // +0x24: pointer to keyframe data
    // +0x30: temporary float 1 (used in case 2)
    // +0x34: temporary float 2
    // +0x38: temporary float 3
    // +0x3c: output value (interpolated)
    // +0x40: output slope or intercept

    struct KeyframeData {
        // +0x28: interpolation type (1..5)
        // +0x2c: time step / duration (used in case 2 if >0)
        // +0x34: value1
        // +0x38: value2
        // +0x3c: time1 (for case 4)
        // +0x40: time2 (for case 4)
        // +0x44: time offset?
    };
};

// Global constants (hypothetical names)
extern float g_defaultSlope;          // DAT_00e2b1a4
extern float g_scaleFactor;           // DAT_00e2cd54
extern float g_offset2;               // DAT_00e2b04c
extern float g_offset3;               // DAT_00e445ac
extern float g_initialMax;            // DAT_00e44850
extern float g_initialMin;            // DAT_00e4458c
extern float g_timeStepScale;         // DAT_00e2b334

void __thiscall AnimCurveEvaluator::evaluate() {
    KeyframeData* keyframeData = *(KeyframeData**)((char*)this + 0x24);
    int type = *(int*)((char*)keyframeData + 0x28);
    float slope;  // temporary for computation

    switch (type) {
    case 1:
    case 3:
        // Linear/Cubic - compute slope and value from two endpoints
        slope = (*(float*)((char*)keyframeData + 0x34) - *(float*)((char*)keyframeData + 0x38)) * g_scaleFactor;
        *(float*)((char*)this + 0x3c) = slope;
        *(float*)((char*)this + 0x40) = slope + *(float*)((char*)keyframeData + 0x38);
        break;

    case 2:
        // Hermite-like interpolation with iterative evaluation
        {
            float timeStep = *(float*)((char*)keyframeData + 0x2c); // duration
            // Set initial outputs
            *(float*)((char*)this + 0x3c) = g_defaultSlope;
            *(int*)((char*)this + 0x40) = 0;
            // Precompute three offsets from keyframe data
            float baseValue = *(float*)((char*)keyframeData + 0x3c);
            *(float*)((char*)this + 0x30) = baseValue + g_defaultSlope;
            *(float*)((char*)this + 0x34) = baseValue + g_offset2;
            *(float*)((char*)this + 0x38) = baseValue + g_offset3;

            if (timeStep > 0.0f) {
                float step = timeStep * g_timeStepScale;
                float maxVal = g_initialMax;
                float minVal = g_initialMin;
                float current = g_initialMin; // initial fVar5
                int iterationCount = 0x15; // 21 steps

                do {
                    calculateHermiteStep(); // internal function (address 0x005006d0)
                    // Track min/max
                    if (maxVal < current) {
                        maxVal = current;
                    }
                    if (current < minVal) {
                        minVal = current;
                    }
                    iterationCount--;
                    current = current + step;
                } while (iterationCount != 0);

                // Compute final slope and intercept from min/max
                float value1 = *(float*)((char*)keyframeData + 0x34);
                float value2 = *(float*)((char*)keyframeData + 0x38);
                float range = value1 - value2;
                float timeRange = maxVal - minVal;
                if (timeRange != 0.0f) {
                    slope = range / timeRange;
                } else {
                    slope = 0.0f; // prevent division by zero
                }
                *(float*)((char*)this + 0x3c) = slope;
                *(float*)((char*)this + 0x40) = value2 - slope * minVal;
            }
        }
        break;

    case 4:
        // Explicit linear interpolation with two time points
        {
            float value1 = *(float*)((char*)keyframeData + 0x34);
            float value2 = *(float*)((char*)keyframeData + 0x38);
            float time1 = *(float*)((char*)keyframeData + 0x40);
            float time2 = *(float*)((char*)keyframeData + 0x44);
            float timeDelta = time1 - time2;
            if (timeDelta != 0.0f) {
                slope = (value1 - value2) / timeDelta;
            } else {
                slope = 0.0f;
            }
            *(float*)((char*)this + 0x3c) = slope;
            *(float*)((char*)this + 0x40) = value2 - slope * time2;
        }
        break;

    case 5:
        // Step: direct value
        *(float*)((char*)this + 0x3c) = *(float*)((char*)keyframeData + 0x34) - *(float*)((char*)keyframeData + 0x38);
        *(int*)((char*)this + 0x40) = *(int*)((char*)keyframeData + 0x38);
        break;
    }
}