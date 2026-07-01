// FUNC_NAME: EARSComponent::shutdown
void __fastcall EARSComponent::shutdown(int this) {
    char isActive;
    int globalState;
    int uVar2;
    int timerData[3]; // local_c, local_8, local_4

    // Check if a global flag is set and if a specific condition is not active
    isActive = getGlobalFlag(); // FUN_00602e00
    if (isActive && *(int *)(this + 0x160) == 0) {
        releaseResource(*(int *)(this + 0x17c), this + 0x15c); // FUN_00603330
    }

    resetTimer(this + 0x15c); // FUN_004d3e20

    // Fetch global state pointer and then set it via another manager call
    if (DAT_01223484 == 0) {
        uVar2 = -1;
    } else {
        uVar2 = *(int *)(DAT_01223484 + 0x3b4);
    }
    setGlobalState(uVar2); // FUN_008a9390

    // Set state field to 3 (likely idle/stopped)
    *(int *)(this + 0xd8) = 3;

    // Clear/reset first timer with DAT_0112b2a4 as base
    timerData[0] = DAT_0112b2a4;
    timerData[1] = 0;
    timerData[2] = 0;
    setTimer(timerData, 0); // FUN_00408a00

    stopAudioStreams(); // FUN_0093c210
    stopAnimations();   // FUN_0094e170

    // Clear a pointer field
    *(int *)(this + 0x10c) = 0;

    // Release an object pointed by field at +0x60
    releaseObject(*(int *)(this + 0x60)); // FUN_004badd0

    // Free a handle if it is not -1
    if (*(int *)(this + 0x110) != -1) {
        freeHandle(*(int *)(this + 0x110)); // FUN_0090dff0
        *(int *)(this + 0x110) = -1;
    }

    // Reset second timer with object's own field +0xb0 as data
    timerData[0] = *(int *)(this + 0xb0);
    timerData[1] = 0;
    timerData[2] = 0;
    setTimer(timerData, 0); // FUN_00408a00

    // Reset third timer using global DAT_0112f4b4
    timerData[0] = DAT_0112f4b4;
    timerData[1] = 0;
    timerData[2] = 0;
    setTimer(timerData, 0); // FUN_00408a00
}