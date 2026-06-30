// FUNC_NAME: PlayerStateMachine::updateState
void __fastcall PlayerStateMachine::updateState(int thisPtr)
{
    int currentState = *(int *)(thisPtr + 0x10c); // state enum (0=idle,1=move,2=action)
    bool flagBit1 = (*(uint *)(thisPtr + 0x110) >> 1) & 1; // +0x110 flags bit1 (maybe "active"?)
    bool flagBit3 = (*(uint *)(thisPtr + 0x110) >> 3) & 1; // +0x110 flags bit3 (maybe "pending"?)
    bool hasTarget = *(int *)(thisPtr + 0xd4) != 0;       // +0xd4 target/component pointer

    if (currentState == 2)
    {
        // State 2: action/combat? 
        if ((hasTarget && !flagBit3) || !flagBit1)
        {
            FUN_0055f950(); // handle state 2 transition
            return;
        }
    }
    else
    {
        if (currentState == 0)
        {
            // State 0: idle
            FUN_0055f8b0(); // idle update
            return;
        }
        if (currentState != 1)
        {
            return; // unknown state, do nothing
        }
        // State 1: movement
        if (!flagBit1)
        {
            FUN_0055de60(); // movement transition
            return;
        }
    }
    // If conditions not met, fall through to default update
    FUN_0055df90(); // generic update (e.g., apply physics or blend)
}