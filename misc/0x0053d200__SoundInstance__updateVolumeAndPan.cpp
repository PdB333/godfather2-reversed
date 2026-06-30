// FUNC_NAME: SoundInstance::updateVolumeAndPan

void SoundInstance::updateVolumeAndPan() {
    // +0x2a8: soundType (int)
    // +0xe8: array of handles indexed by soundType * 0x20
    int soundHandle = *(int*)((char*)this + *(int*)((char*)this + 0x2a8) * 0x20 + 0xe8);
    if (soundHandle == 0) {
        return;
    }

    // +0xe0: sampleIndex (uint) into a global sample definition table at 0x011a0f28 (struct size 0x38)
    uint sampleIndex = *(uint*)((char*)this + 0xe0);
    void* sampleDef = nullptr;
    if (sampleIndex < 0x1000) {
        sampleDef = (void*)((char*)0x011a0f28 + sampleIndex * 0x38);
    }

    // Choose base volume based on sound type (4 = special type)
    float baseVol;
    if (*(int*)((char*)this + 0x2a8) == 4) {
        baseVol = DAT_00e4475c;  // Type 4 global volume
    } else {
        baseVol = DAT_00e2cd14;  // Default global volume
    }

    // +0x2ac / +0x2b0: ratio (e.g., distance/dampening)
    float ratio = *(float*)((char*)this + 0x2ac) / *(float*)((char*)this + 0x2b0);

    // +0xa4: channel (0 = left, 1 = right)
    int channel = *(int*)((char*)this + 0xa4);

    float leftVol = 0.0f, rightVol = 0.0f, leftPan = 0.0f, rightPan = 0.0f;

    if (channel == 0) {
        // sampleDef+0x02: short left channel divisor
        leftVol = baseVol / (float)*(ushort*)((char*)sampleDef + 2);
        leftPan = ratio / (float)*(ushort*)((char*)sampleDef + 2);
    }
    if (channel == 1) {
        // sampleDef+0x04: short right channel divisor
        rightVol = baseVol / (float)*(ushort*)((char*)sampleDef + 4);
        rightPan = ratio / (float)*(ushort*)((char*)sampleDef + 4);
    }

    float params[4] = { leftVol, rightVol, leftPan, rightPan };
    // +0x14: some audio mixer handle; function applies volume/pan to the sound
    FUN_0060add0(*(uint*)((char*)this + 0x14), soundHandle, &params);
}