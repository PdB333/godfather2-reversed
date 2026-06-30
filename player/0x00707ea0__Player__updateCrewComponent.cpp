// FUNC_NAME: Player::updateCrewComponent
// Function at 0x00707ea0: Check a flag (bit 6 of dword at +0x1D0) and conditionally update a sub-component at offset +0x188.
// Role: Conditional update of a sub-object (e.g., crew component or state machine).
void __thiscall Player::updateCrewComponent() {
    // Offset 0x1D0: flags field; bit 6 indicates sub-component should be updated
    if ((*(uint32_t*)((uint8_t*)this + 0x1D0) >> 6) & 1) {
        // Offset 0x188: sub-component instance (e.g., CrewComponent, PlayerGroundSM)
        // Call its update routine at address 0x00707520
        ((void (__thiscall*)(void*))(0x00707520))((uint8_t*)this + 0x188);
    }
}