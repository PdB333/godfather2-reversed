// FUNC_NAME: DebugOverlay::renderControllerInputOverlay
void __thiscall DebugOverlay::renderControllerInputOverlay(DebugOverlay *this) {
    int inputState1; // result of first virtual input check
    int inputState2;
    int inputState3;

    // Check if overlay is enabled (e.g., flag at offset +0x3FC)
    if (*(int *)((int)this + 0x3fc) != 0) {
        // Get three independent input states (e.g., key presses or button combos)
        inputState1 = isInputActive();  // FUN_005e9d10 – likely checks a specific key/button
        inputState2 = isInputActive();
        inputState3 = isInputActive();
        beginFrame(); // FUN_00c9eac0 – start of GUI rendering frame

        // Draw based on first input state: uses value at +0x90A0 (e.g., a texture handle or string)
        if (inputState1 != 0) {
            drawInputIcon(0, *(unsigned int *)((int)this + 0x90a0)); // FUN_00ca4e90 – index 0, icon pointer
        }
        // Draw based on second input state: uses three values at +0x9094, +0x9098, +0x909C (e.g., button icons)
        if (inputState2 != 0) {
            drawInputIcon(0, *(unsigned int *)((int)this + 0x9094));
            drawInputIcon(1, *(unsigned int *)((int)this + 0x9098));
            drawInputIcon(2, *(unsigned int *)((int)this + 0x909c));
        }
        // Draw based on third input state: uses value at +0x908C
        if (inputState3 != 0) {
            drawInputIcon(0, *(unsigned int *)((int)this + 0x908c));
        }
        endFrame(); // FUN_00c9eae0 – end of GUI rendering frame
    }
}