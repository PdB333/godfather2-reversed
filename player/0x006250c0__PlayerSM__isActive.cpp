// FUNC_NAME: PlayerSM::isActive
// Function at 0x006250c0: Checks the active flag (bit 0) of the state machine.
// If set, returns 1 (true). Otherwise, delegates to the sub-function via the manager pointer.
// Structure: +0x00: byte flags (bit0 = active), +0x04: void* manager (passed to sub-function)
bool __thiscall PlayerSM::isActive(byte *thisPtr) {
    if ((*thisPtr & 1) != 0) {
        return true;
    }
    // Sub-function likely initializes or queries the manager for state readiness
    return FUN_006250e0(*(undefined4 *)(thisPtr + 4));
}