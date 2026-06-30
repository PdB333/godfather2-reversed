// FUNC_NAME: buildWaveTable
void buildWaveTable(int* config) {
    float freqVal = *(float*)(config + 1); // +0x04
    float offsetVal = *(float*)(config + 2); // +0x08
    float maxVal = *(float*)0x00e2b1a4; // table length limit
    float stepScale = *(float*)0x00e2cd54; // scaling factor
    float phaseStep = *(float*)0x00e44640; // angular step or phase increment
    float scaleFactor = *(float*)0x00e2e22c; // final multiplier for short output

    float base = (maxVal - freqVal) * stepScale;
    int i = 0;
    do {
        double dPhase = (double)((float)i * phaseStep);
        FUN_00b9af10(); // side effect (likely random/seed update)

        float value = (float)dPhase * freqVal + base + offsetVal;
        // clamp to [0, maxVal]
        float clamped;
        if (value < 0.0f) {
            clamped = 0.0f;
        } else if (value > maxVal) {
            clamped = maxVal;
        } else {
            clamped = value;
        }

        unsigned short result = (unsigned short)(long long)(clamped * scaleFactor);

        i++;
        // write to three separate tables (likely pitch/duration/volume)
        *(unsigned short*)(i * 2 + 0x11d91e6) = result; // table1
        *(unsigned short*)(i * 2 + 0x11d93e6) = result; // table2
        *(unsigned short*)(i * 2 + 0x11d95e6) = result; // table3
    } while (i < 0x100);

    // notify listener of table update
    (**(code**)(*(int*)0x01205750 + 0x54))(0x01205750, 0, 0, &DAT_011d91e8);
}