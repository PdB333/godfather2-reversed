// FUNC_NAME: PlayerStateMachine::update
void __fastcall PlayerStateMachine::update(int *this)
{
    char isPaused;
    int inputState;
    int *subObjectBase;

    isPaused = __fastcall isGamePaused(); // 0x009b0d80
    if (isPaused != '\0') {
        // If game is paused, only update the sub‑component (e.g., animation or camera)
        if (this[0x12] == 0) {
            subObjectBase = (int *)0x0;
        } else {
            // +0x48 is the offset of the sub‑object pointer within 'this'
            // Subtract 0x48 to get the base of the sub‑object (which has a vtable)
            subObjectBase = (int *)(this[0x12] + -0x48);
        }
        // Call virtual function at offset 0x164 on the sub‑object
        (**(code **)(*subObjectBase + 0x164))();
        return;
    }

    // Normal update path: reset frame state
    __fastcall resetFrameState(); // 0x009afea0

    // Get current input state (e.g., controller or keyboard)
    inputState = __fastcall getInputState(); // 0x007347e0

    // Call virtual function at offset 0x2c (probably processInput)
    // Parameters: inputState, 1, 0, 1, 1.0f, 1.0f
    (**(code **)(*this + 0x2c))(inputState, 1, 0, 1, 0x3f800000, 0x3f800000);

    // Similarly get sub‑object base and call its post‑update virtual (offset 0x168)
    if (this[0x12] == 0) {
        subObjectBase = (int *)0x0;
    } else {
        subObjectBase = (int *)(this[0x12] + -0x48);
    }
    (**(code **)(*subObjectBase + 0x168))();

    // Mark this frame as updated (offset 0x104 = 0x41 * 4)
    this[0x41] = 1;
}