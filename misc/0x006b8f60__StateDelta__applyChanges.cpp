// FUNC_NAME: StateDelta::applyChanges
void __thiscall StateDelta::applyChanges(StateDelta* this, State* target) // this: +0x88 = setFlags, +0x8c = clearFlags; target: +0x34 = stateFlags
{
    uint setFlags = *(uint*)((int)this + 0x88);
    if ((setFlags & 1) != 0) {
        FUN_006b5b10(); // Enables feature A (e.g., enableRumble)
    }
    if ((setFlags & 4) != 0) {
        FUN_006b2600(1); // Sets mode (e.g., setEngineIgnition(true))
    }
    // Propagate remaining set flags to target
    if ((setFlags & 0x10) != 0) {
        *(uint*)((int)target + 0x34) |= 0x10;
    }
    if ((setFlags & 0x20) != 0) {
        *(uint*)((int)target + 0x34) |= 0x20;
    }
    if ((setFlags & 0x40) != 0) {
        *(uint*)((int)target + 0x34) |= 0x40;
    }
    if ((char)setFlags < 0) { // 0x80 (bit 7)
        *(uint*)((int)target + 0x34) |= 0x80;
    }
    if ((setFlags & 0x100) != 0) {
        *(uint*)((int)target + 0x34) |= 0x100;
    }
    if ((setFlags & 0x200) != 0) {
        *(uint*)((int)target + 0x34) |= 0x200;
    }
    if ((setFlags & 0x400) != 0) {
        *(uint*)((int)target + 0x34) |= 0x400;
    }
    if ((setFlags & 0x800) != 0) {
        *(uint*)((int)target + 0x34) |= 0x800;
    }
    if ((setFlags & 8) != 0) {
        *(uint*)((int)target + 0x34) |= 8;
    }

    uint clearFlags = *(uint*)((int)this + 0x8c);
    if ((clearFlags & 1) != 0) {
        FUN_006b5ac0(); // Disables feature A (e.g., disableRumble)
    }
    if ((clearFlags & 4) != 0) {
        FUN_006b2600(0); // Clears mode (e.g., setEngineIgnition(false))
    }
    // Propagate remaining clear flags to target
    if ((clearFlags & 0x10) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x10;
    }
    if ((clearFlags & 0x20) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x20;
    }
    if ((clearFlags & 0x40) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x40;
    }
    if ((char)clearFlags < 0) { // 0x80 (bit 7)
        *(uint*)((int)target + 0x34) &= ~0x80;
    }
    if ((clearFlags & 0x100) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x100;
    }
    if ((clearFlags & 0x200) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x200;
    }
    if ((clearFlags & 0x400) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x400;
    }
    if ((clearFlags & 0x800) != 0) {
        *(uint*)((int)target + 0x34) &= ~0x800;
    }
    if ((clearFlags & 8) != 0) {
        *(uint*)((int)target + 0x34) &= ~8;
    }
}