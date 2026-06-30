// FUNC_NAME: StateMachine::update
void __fastcall StateMachine::update(uint32_t arg1)
{
    // Pre-update step, possibly resets per-frame state
    beginUpdate();

    // Switch on the current state stored at this pointer (dereferenced as uint32_t)
    switch (*reinterpret_cast<uint32_t*>(this))
    {
    case 1:  // State_1
    case 3:  // State_3
        processState(arg1);
        return;

    case 2:  // State_2
        handleStateTwoSpecific();
        processState(arg1);
        return;

    case 9:  // State_9 (likely terminal or idle)
        processState(arg1);
        return;

    default: // Unknown state – reset to state 1
        setStateNext(1);
        processState(arg1);
        return;
    }
}