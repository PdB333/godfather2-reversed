// FUNC_NAME: PlayerSM::changeState
// Address: 0x006b7240
// Role: Handles state transitions for the player state machine.
// When transitioning into state 4 (e.g., idle/special state) from a different state,
// optionally plays a random sound and sets a flag. For other transitions, delegates
// to a sub-state machine component via a virtual call and clears the flag.
void __thiscall PlayerSM::changeState(uint previousState, uint newState)
{
    // m_pStateComponent pointer at +0x130
    void* stateComponent = *(void**)(this + 0x130);
    if (stateComponent == nullptr) {
        return;
    }

    // m_stateFlags at +0x290
    uint32 stateFlags = *(uint32*)(this + 0x290);

    if (newState == 4 && previousState != 4) {
        // Entering state 4 from a different state
        if ((stateFlags >> 29) & 1) {
            // Bit 29 already set – do nothing (may indicate a pending sound)
            return;
        }
        // Set bit 29 to prevent re-entry
        stateFlags |= 0x20000000;
        *(uint32*)(this + 0x290) = stateFlags;

        // Play random sound at object position
        int r = rand();
        float randomTime = (float)r * g_randomScale1 * g_randomScale2;
        EARS::AudioManager::playSoundAtPosition(&g_soundBank, this + 0x3c, randomTime, 0, 0);
    } else {
        // Other state transitions
        // Call virtual function at vtable index 0x11 (offset 0x44) on the state component
        // Pass a constant message ID and the new state
        (**(void (__thiscall**)(void*, uint, uint))((*(uint32*)stateComponent) + 0x44))
            (stateComponent, 0xf86f4484, newState);

        // Clear bit 29 of stateFlags
        stateFlags &= 0xdfffffff;
        *(uint32*)(this + 0x290) = stateFlags;
    }
}