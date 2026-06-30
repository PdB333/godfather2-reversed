// FUNC_NAME: PlayerSM::updateState
// Address: 0x0055df10
// Role: Updates the state machine dispatch based on current state and flags.
// Offsets:
//  +0x10c: int m_state (0,1,2)
//  +0x110: uint m_flags (bit1 = paused? bit3 = finished?)
//  +0x0d4: void* m_target (some object pointer)

void __thiscall PlayerSM::updateState()
{
    int state = *(int*)((uint)this + 0x10c);    // m_state
    uint flags = *(uint*)((uint)this + 0x110);  // m_flags
    void* target = *(void**)((uint)this + 0xd4); // m_target

    switch (state) {
        case 0:
            // State 0: idle/inactive
            FUN_0055f8b0(); // processIdleState
            break;

        case 1:
            // State 1: active/running
            if ((flags & 0x2) == 0) { // bit1 clear => not paused
                FUN_0055de60(); // processActiveState
            } else {
                FUN_0055df90(); // processFinishedOrPausedState
            }
            break;

        case 2:
            // State 2: finishing/paused
            // Condition: (target exists and bit3 clear) OR bit1 clear
            if (((target != nullptr) && ((flags & 0x8) == 0)) || ((flags & 0x2) == 0)) {
                FUN_0055f950(); // processPausedOrResumeState
            } else {
                FUN_0055df90(); // processFinishedOrPausedState
            }
            break;

        default:
            break;
    }
}