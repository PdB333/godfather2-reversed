// FUNC_NAME: setGlobalState16FromPointer
struct GlobalState16 {
    uint32_t data[16]; // +0x00, 16 dwords = 64 bytes
};

// Global instance at 0x011f69f0
extern GlobalState16 gGlobalState;
extern uint32_t gGlobalFlag; // at 0x011f7430

void setGlobalState16FromPointer(uint32_t* src) {
    // Copy 16 dwords into global state
    gGlobalState.data[0] = src[0];
    gGlobalState.data[1] = src[1];
    gGlobalState.data[2] = src[2];
    gGlobalState.data[3] = src[3];
    gGlobalState.data[4] = src[4];
    gGlobalState.data[5] = src[5];
    gGlobalState.data[6] = src[6];
    gGlobalState.data[7] = src[7];
    gGlobalState.data[8] = src[8];
    gGlobalState.data[9] = src[9];
    gGlobalState.data[10] = src[10];
    gGlobalState.data[11] = src[11];
    gGlobalState.data[12] = src[12];
    gGlobalState.data[13] = src[13];
    gGlobalState.data[14] = src[14];
    gGlobalState.data[15] = src[15];

    // Call post-update routine
    FUN_00424470();

    // If low bit of global flag set, call additional init
    if ((gGlobalFlag & 1) != 0) {
        FUN_00614ab0();
    }
}