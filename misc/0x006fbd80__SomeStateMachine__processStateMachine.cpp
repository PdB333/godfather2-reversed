// FUNC_NAME: SomeStateMachine::processStateMachine
void __thiscall SomeStateMachine::processStateMachine(int* this)
{
    if (this[2] != 0) { // +8: enabled flag or condition
        if (*this == 6) { // +0: current state (state 6 = special transition)
            FUN_006fbd30();           // handle state 6 transition
            return;
        }
        // Reset to default state
        *this = 0;       // state = 0 (e.g., Idle)
        this[1] = 0;     // +4: timer or substate
    }
}