// FUNC_NAME: FlagContainer::clearFlag
// Address: 0x0081dd80
// Role: Clears a flag bitmask and triggers cleanup if all flags are cleared.
// Offset +0x14: uint flags (bitmask of active states/events)

void __thiscall FlagContainer::clearFlag(uint flagMask) {
    this->flags &= ~flagMask;
    if (this->flags == 0) {
        FUN_004df6e0(); // unknown cleanup function
        FUN_004df6e0();
        FUN_004df6e0();
        FUN_004df6e0();
    }
}