// FUNC_NAME: setActionState
// Function at 0x006eb720: Sets an action state and ID if the object is capable of actions.
// Offsets:
//   +0x24 : byte flag indicating if actions are allowed (m_bCanAct)
//   +0x25 : byte flag cleared (m_bActionDone)
//   +0x28 : int state set to 1 (m_actionState)
//   +0x2c : int action ID set from param (m_actionId)
//   +0x40 : int cleared (m_actionTimerOrCounter)
void __thiscall setActionState(int actionId)
{
    char *canAct = (char *)(this + 0x24);
    if (*canAct != '\0') {
        *(int *)(this + 0x40) = 0;       // Clear action timer/counter
        *(int *)(this + 0x2c) = actionId; // Set action ID
        *(int *)(this + 0x28) = 1;        // Mark action as active
        *(char *)(this + 0x25) = 0;       // Clear completion flag
    }
}