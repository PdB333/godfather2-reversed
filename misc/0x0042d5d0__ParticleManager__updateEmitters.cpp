// FUNC_NAME: ParticleManager::updateEmitters
void __thiscall ParticleManager::updateEmitters(DWORD param) {
    // this+0x34: count of emitters? (int)
    // this+0x50: pointer to array of emitter structs (0xB0 bytes each)
    int emitters = *(int *)(this + 0x34);
    char *arrayBase = *(char **)(this + 0x50);
    char *current = arrayBase;
    char *end = arrayBase + emitters * 0xB0;

    char localBuffer[28]; // used by FUN_004c4d80

    for (; current != end; current += 0xB0) {
        // +0x2a: short type/state (must be >= -1, i.e. not -2)
        short emitterState = *(short *)(current + 0x2A);
        // +0x04: byte flag (if != 1, emitter is active)
        char activeFlag = *(char *)(current + 4);

        if (emitterState > -2 && activeFlag != 1) {
            // +0x10: some data block (transform, offset, etc.)
            FUN_0042a1a0(current + 0x10, param); // likely updates emitter position/state

            // +0x29: byte counter/state (if < 6, fetch additional data)
            if (*(unsigned char *)(current + 0x29) < 6) {
                FUN_004c4d80(param, localBuffer); // likely gets world transform or bone data
            }
        }
    }
}