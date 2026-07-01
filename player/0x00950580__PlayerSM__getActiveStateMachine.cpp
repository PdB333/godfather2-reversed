// FUNC_NAME: PlayerSM::getActiveStateMachine
int __fastcall PlayerSM::getActiveStateMachine(int thisPtr)
{
    // Check if the flag at offset 0x1c4 is zero (inactive)
    // If zero, return pointer at offset 0x104 (first state machine)
    // Otherwise return pointer at offset 0x1c4 (second state machine)
    int result = thisPtr + 0x1c4;
    if (*(char *)(thisPtr + 0x1c4) == '\0') {
        result = thisPtr + 0x104;
    }
    return result;
}