// FUNC_NAME: StateMachine::setActiveState
// Address: 0x004c2060
// Sets the active state ID, handling state transitions with pre/post callbacks.
// Uses __thiscall (this in ECX), state ID expected in EDI.
// Class fields: vtable+0x00, currentState+0x80
// Virtual function at vtable[0x14c/4] is called after state change (likely onStateEnter).

void __thiscall StateMachine::setActiveState(int newState)
{
    // resetState (FUN_004c2130) – cleanup before any state change
    // exitState (FUN_009f01a0) – called if old state was non-zero (state exit callback)
    
    if (newState == 0)
    {
        this->resetState();
        if (this->m_stateID != 0)
        {
            this->exitState();
            return;
        }
    }
    else if (this->m_stateID != newState)
    {
        this->resetState();
        if (this->m_stateID != 0)
        {
            this->exitState();
        }
        
        // Get virtual function pointer for state entry callback (vtable index 0x53)
        void (*onStateEnter)() = this->vtable[0x14c / sizeof(void*)];
        this->m_stateID = newState;            // +0x80
        onStateEnter();                         // indirect call via vtable
        return;
    }
    // If newState == m_stateID, do nothing (already in requested state)
}