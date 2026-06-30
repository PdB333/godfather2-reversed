// FUNC_NAME: Animation::outputInterpolatedData
// Function address: 0x00581080
// Role: Fills an output buffer with interpolated animation data from this Animation state.
// The output buffer pointer is passed in EAX (hidden parameter), assumed to be an array of 27 ints.
// param_2 is an interpolation time or weight.

void __thiscall Animation::outputInterpolatedData(void *this, int param_2)
{
    short sVar1;
    int iVar2;
    int *outputBuffer; // in EAX (hidden)

    // Block 0 (indices 0-3) - e.g., translation channel
    if (*(short *)((int)this + 0x2e) < 1) {
        outputBuffer[0] = 0;
        outputBuffer[1] = 0;
        outputBuffer[2] = 0;
        outputBuffer[3] = -1;
    } else {
        sVar1 = *(short *)((int)this + 0x5a);          // +0x5a: rate0
        iVar2 = *(int *)((int)this + 0xac);            // +0xac: base0
        outputBuffer[0] = sVar1 * param_2 + iVar2;     // interpolated value
        outputBuffer[1] = *(int *)((int)this + 0xa8);  // +0xa8: value0_1
        outputBuffer[2] = *(int *)((int)this + 0xcc);  // +0xcc: value0_2
        outputBuffer[3] = 0;                           // sentinel
    }

    // Block 1 (indices 4-7) - e.g., rotation channel
    if (*(short *)((int)this + 10) < 1) {
        outputBuffer[4] = 0;
        outputBuffer[5] = 0;
        outputBuffer[6] = 0;
        outputBuffer[7] = -1;
    } else {
        outputBuffer[4] = *(int *)((int)this + 0xa0) + *(short *)((int)this + 0x58) * param_2 * 2;
        outputBuffer[5] = *(int *)((int)this + 0xa4);
        outputBuffer[6] = *(int *)((int)this + 0xd0);
        outputBuffer[7] = 0;
    }

    // Block 2 (indices 8-9) - e.g., scale channel (2 components)
    if (*(short *)((int)this + 0x2c) < 1) {
        outputBuffer[8] = 0;
        outputBuffer[9] = -1;
    } else {
        outputBuffer[8] = *(int *)((int)this + 0xb0);
        outputBuffer[9] = 0;
    }

    // Block 3 (indices 10-13) - e.g., second translation group
    if (*(short *)((int)this + 0x76) < 1) {
        outputBuffer[10] = 0;
        outputBuffer[11] = 0;
        outputBuffer[12] = 0;
        outputBuffer[13] = -1;
    } else {
        sVar1 = *(short *)((int)this + 0x7a);          // +0x7a: rate1
        iVar2 = *(int *)((int)this + 0xc0);            // +0xc0: base1
        outputBuffer[10] = sVar1 * param_2 + iVar2;
        outputBuffer[11] = *(int *)((int)this + 200);   // +0xc8
        outputBuffer[12] = *(int *)((int)this + 0xd4);
        outputBuffer[13] = 0;
    }

    // Block 4 (indices 14-17) - e.g., second rotation group
    if (*(short *)((int)this + 0x74) < 1) {
        outputBuffer[14] = 0;
        outputBuffer[15] = 0;
        outputBuffer[16] = 0;
        outputBuffer[17] = -1;
    } else {
        outputBuffer[14] = *(int *)((int)this + 0xbc) + *(short *)((int)this + 0x78) * param_2 * 2;
        outputBuffer[15] = *(int *)((int)this + 0xc4);
        outputBuffer[16] = *(int *)((int)this + 0xd8);
        outputBuffer[17] = 0;
    }

    // Block 5 (indices 18-19) - e.g., second scale channel
    if (*(short *)((int)this + 0x72) < 1) {
        outputBuffer[18] = 0;
        outputBuffer[19] = -1;
    } else {
        outputBuffer[18] = *(int *)((int)this + 0xb4) + *(short *)((int)this + 0x72) * param_2 * 12;
        outputBuffer[19] = 0;
    }

    // Block 6 (indices 20-25) - e.g., morph target data
    sVar1 = *(short *)((int)this + 0x8a);              // +0x8a: morphCount
    outputBuffer[20] = *(int *)((int)this + 0xb8);     // +0xb8: morphBase
    outputBuffer[21] = 0;                              // sentinel
    if (sVar1 < 1) {
        outputBuffer[22] = 0;
        outputBuffer[23] = 0;
        outputBuffer[24] = 0;
        outputBuffer[25] = -1;
    } else {
        outputBuffer[22] = *(int *)((int)this + 0xe0) + (uint)*(byte *)((int)this + 0x89) * param_2 * 2;
        outputBuffer[23] = *(int *)((int)this + 0xe4);
        outputBuffer[24] = *(int *)((int)this + 0xe8);
        outputBuffer[25] = 0;
    }

    // Final int (index 26) - e.g., some flag or blend weight
    if (*(int *)((int)this + 0x1c) > 0) {
        outputBuffer[26] = *(int *)((int)this + 0x9c);
    } else {
        outputBuffer[26] = 0;
    }
}