// FUNC_NAME: AnimationPlayer::ComputeLayerResults
void __thiscall AnimationPlayer::ComputeLayerResults(int animationTime, int* outputBuffer)
{
    // Read blend counts from various fields. Each layer has a count (short) and data.
    // If count <= 0, the corresponding output is zeroed with flags = -1 (disabled).
    // Otherwise, compute start/position as (multiplier * animationTime + base) and fill other fields.

    // Layer 0 (blend layer 0) - 4 ints per output
    if (*(short*)(this + 0x2e) < 1) {
        outputBuffer[0] = 0;
        outputBuffer[1] = 0;
        outputBuffer[2] = 0;
        outputBuffer[3] = -1; // disabled
    } else {
        short multiplier = *(short*)(this + 0x5a);
        int base = *(int*)(this + 0xac);
        outputBuffer[0] = multiplier * animationTime + base;   // start/weight
        outputBuffer[1] = *(int*)(this + 0xa8);                // velocity?
        outputBuffer[2] = *(int*)(this + 0xcc);                // acceleration?
        outputBuffer[3] = 0;                                   // flags: enabled
    }

    // Layer 1 - also 4 ints
    if (*(short*)(this + 0xa) < 1) {
        outputBuffer[4] = 0;
        outputBuffer[5] = 0;
        outputBuffer[6] = 0;
        outputBuffer[7] = -1;
    } else {
        outputBuffer[4] = *(int*)(this + 0xa0) + *(short*)(this + 0x58) * animationTime * 2;
        outputBuffer[5] = *(int*)(this + 0xa4);
        outputBuffer[6] = *(int*)(this + 0xd0);
        outputBuffer[7] = 0;
    }

    // Layer 2 - 2 ints
    if (*(short*)(this + 0x2c) < 1) {
        outputBuffer[8] = 0;
        outputBuffer[9] = -1;
    } else {
        outputBuffer[8] = *(int*)(this + 0xb0);
        outputBuffer[9] = 0;
    }

    // Layer 3 - 4 ints
    if (*(short*)(this + 0x76) < 1) {
        outputBuffer[10] = 0;
        outputBuffer[11] = 0;
        outputBuffer[12] = 0;
        outputBuffer[13] = -1;
    } else {
        short multiplier = *(short*)(this + 0x7a);
        int base = *(int*)(this + 0xc0);
        outputBuffer[10] = multiplier * animationTime + base;
        outputBuffer[11] = *(int*)(this + 0xc8);  // +200
        outputBuffer[12] = *(int*)(this + 0xd4);
        outputBuffer[13] = 0;
    }

    // Layer 4 - 4 ints
    if (*(short*)(this + 0x74) < 1) {
        outputBuffer[14] = 0;
        outputBuffer[15] = 0;
        outputBuffer[16] = 0;
        outputBuffer[17] = -1;
    } else {
        outputBuffer[14] = *(int*)(this + 0xbc) + *(short*)(this + 0x78) * animationTime * 2;
        outputBuffer[15] = *(int*)(this + 0xc4);
        outputBuffer[16] = *(int*)(this + 0xd8);
        outputBuffer[17] = 0;
    }

    // Layer 5 - 2 ints
    if (*(short*)(this + 0x72) < 1) {
        outputBuffer[18] = 0;
        outputBuffer[19] = -1;
    } else {
        outputBuffer[18] = *(int*)(this + 0xb4) + *(short*)(this + 0x72) * animationTime * 12; // 0xc
        outputBuffer[19] = 0;
    }

    // Layer 6 (partial?) - first two ints unconditional, then 4 ints conditional
    outputBuffer[20] = *(int*)(this + 0xb8);
    outputBuffer[21] = 0;
    if (*(short*)(this + 0x8a) < 1) {
        outputBuffer[22] = 0;
        outputBuffer[23] = 0;
        outputBuffer[24] = 0;
        outputBuffer[25] = -1;
    } else {
        outputBuffer[22] = *(int*)(this + 0xe0) + (uint)*(byte*)(this + 0x89) * animationTime * 2;
        outputBuffer[23] = *(int*)(this + 0xe4);
        outputBuffer[24] = *(int*)(this + 0xe8);
        outputBuffer[25] = 0;
    }

    // Final single int (offset 0x1a = 26)
    if (*(int*)(this + 0x1c) > 0) {
        outputBuffer[26] = *(int*)(this + 0x9c);
    } else {
        outputBuffer[26] = 0;
    }
    return;
}