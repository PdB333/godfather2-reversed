// FUNC_NAME: PlayerDebugOptions::toggleDebugFlag
void __thiscall PlayerDebugOptions::toggleDebugFlag(void) {
    int currentFlag = *(int *)(this + 0x118); // +0x118: current debug flag state (0 or 1)
    if ((currentFlag == 1) || (currentFlag == 0)) {
        int newFlag = 1 - currentFlag;
        *(int *)(this + 0x118) = newFlag;           // +0x118: toggle flag
        *(int *)(this + 0x164) = newFlag;           // +0x164: secondary flag (mirror)
        *(int *)(this + 0x11c) = 0;                 // +0x11c: reset counter/timer
    }
    return;
}