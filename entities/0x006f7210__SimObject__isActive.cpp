// FUNC_NAME: SimObject::isActive
// Function at 0x006f7210: Checks if the object's state is considered active. 
// Returns 1 if state is 1 (active) without forceInactive, or state 2 or 3.
// Returns 0 if state is 0, forceInactive is set on state 1, or any other state.
char __thiscall SimObject::isActive(int this, char forceInactive)
{
    switch (*(int*)(this + 0x2c)) // +0x2c m_state (e.g., kStateInactive=0, kStateActive=1, kStatePaused=2, kStateSuspended=3)
    {
    case 0:
        return 0;
    case 1:
        if (forceInactive != 0)
            return 0;
        // fall through to default
    case 2:
    case 3:
        return 1;
    default:
        return 0;
    }
}