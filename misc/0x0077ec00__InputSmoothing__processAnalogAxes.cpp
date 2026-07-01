// FUNC_NAME: InputSmoothing::processAnalogAxes

float InputSmoothing::processAnalogAxes(float* axes) {
    // Read smoothing scale values from object state
    uint64 raw0 = *(uint64*)(this + 0x70);
    uint64 raw1 = *(uint64*)(this + 0x78);

    // Decompose into two float pairs
    float scale0 = *(float*)&raw0;
    float scale1 = *(float*)((char*)&raw0 + 4);
    float scale2 = *(float*)&raw1;
    float scale3 = *(float*)((char*)&raw1 + 4);

    // If smoothing mode is 0x25 (37), override scales with a function result
    if (*(int*)(this + 0x54) == 0x25) {
        uint64* pScalePair = getSmoothingOverride(&raw0); // FUN_0071e3e0
        raw0 = *pScalePair;
        raw1 = pScalePair[1];
        scale0 = *(float*)&raw0;
        scale1 = *(float*)((char*)&raw0 + 4);
        scale2 = *(float*)&raw1;
        scale3 = *(float*)((char*)&raw1 + 4);
    }

    // Constants from global data
    const float MAX_VALUE = *(float*)0x00d691d8; // e.g., 1.0f or 32767.0f
    const float ADJUSTMENT_FACTOR = *(float*)0x00d5ef84; // sensitivity factor

    // Process axis 0
    float in0 = axes[0];
    float out0 = in0;
    if (scale0 != 0.0f) {
        out0 = (MAX_VALUE - in0) * ADJUSTMENT_FACTOR * scale0 + in0;
        if (out0 < 0.0f)
            out0 = 0.0f;
        else if (out0 > MAX_VALUE)
            out0 = MAX_VALUE;
    }

    // Process axis 1
    float in1 = axes[1];
    float out1 = in1;
    if (scale1 != 0.0f) {
        out1 = (MAX_VALUE - in1) * ADJUSTMENT_FACTOR * scale1 + in1;
        if (out1 < 0.0f)
            out1 = 0.0f;
        else if (out1 > MAX_VALUE)
            out1 = MAX_VALUE;
    }

    // Process axis 2
    float in2 = axes[2];
    float out2 = in2;
    if (scale2 != 0.0f) {
        out2 = (MAX_VALUE - in2) * ADJUSTMENT_FACTOR * scale2 + in2;
        if (out2 < 0.0f)
            out2 = 0.0f;
        else if (out2 > MAX_VALUE)
            out2 = MAX_VALUE;
    }

    // Compute partial sum for first three axes
    float sumDelta = (out0 - in0) + (out1 - in1) + (out2 - in2);

    // Process axis 3 (last)
    float in3 = axes[3];
    float out3 = in3;
    if (scale3 != 0.0f) {
        out3 = (MAX_VALUE - in3) * ADJUSTMENT_FACTOR * scale3 + in3;
        if (out3 < 0.0f)
            out3 = 0.0f;
        else if (out3 > MAX_VALUE)
            out3 = MAX_VALUE;
    }

    // Return total delta as extended double
    return (double)(out3 - in3) + (double)sumDelta;
}