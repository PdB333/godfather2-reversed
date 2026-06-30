// FUNC_NAME: StatsFilter::addSample

void __fastcall StatsFilter::addSample(float* sample)
{
    // sample[0..3] - primary 4-component vector (e.g., quaternion/position)
    // sample[4..5] - secondary 2-component vector
    // sample[6] - filter type (encoded as float: 0.0f = accumulation0, 1.4013e-45f = EMA, 2.8026e-45f = accumulation1)
    int type = *(int*)&sample[6]; // reinterpret bit pattern: 0, 1, or 2

    static float g_sampleWeight = DAT_00e2b1a4; // weight per sample (e.g., time delta)

    // State for accumulation filter type 0
    static float g_accumSum0[4];   // +0x0
    static float g_accumExtra0[2]; // +0x10
    static float g_accumCount0;    // +0x20

    // State for EMA filter type 1
    static float g_emaPrev0[4];    // +0x60
    static float g_emaExtra0[2];   // +0x70
    static float g_emaCount0;      // +0x80

    // State for accumulation filter type 2
    static float g_accumSum1[4];   // +0x30
    static float g_accumExtra1[2]; // +0x40
    static float g_accumCount1;    // +0x50

    switch (type)
    {
    case 0: // Accumulation filter 0
        g_accumSum0[0] += g_sampleWeight * sample[0];
        g_accumSum0[1] += g_sampleWeight * sample[1];
        g_accumSum0[2] += g_sampleWeight * sample[2];
        g_accumSum0[3] += g_sampleWeight * sample[3];
        g_accumExtra0[0] += sample[4];
        g_accumExtra0[1] += sample[5];
        g_accumCount0 += g_sampleWeight;
        break;

    case 1: // Exponential moving average filter
    {
        float w = g_sampleWeight / (g_emaCount0 + g_sampleWeight);
        g_emaPrev0[0] = (sample[0] - g_emaPrev0[0]) * w + g_emaPrev0[0];
        g_emaPrev0[1] = (sample[1] - g_emaPrev0[1]) * w + g_emaPrev0[1];
        g_emaPrev0[2] = (sample[2] - g_emaPrev0[2]) * w + g_emaPrev0[2];
        g_emaPrev0[3] = (sample[3] - g_emaPrev0[3]) * w + g_emaPrev0[3];
        g_emaExtra0[0] = sample[4] * w + (g_sampleWeight - w) * g_emaExtra0[0];
        g_emaExtra0[1] = sample[5] * w + (g_sampleWeight - w) * g_emaExtra0[1];
        g_emaCount0 += g_sampleWeight;
        break;
    }

    case 2: // Accumulation filter 1
        g_accumSum1[0] += g_sampleWeight * sample[0];
        g_accumSum1[1] += g_sampleWeight * sample[1];
        g_accumSum1[2] += g_sampleWeight * sample[2];
        g_accumSum1[3] += g_sampleWeight * sample[3];
        g_accumExtra1[0] += sample[4];
        g_accumExtra1[1] += sample[5];
        g_accumCount1 += g_sampleWeight;
        break;
    }
}