// FUNC_NAME: PlayerSM::update
void __thiscall PlayerSM::update(int *this, int deltaTimeOrInput)
{
    char flagCheck;

    // Profiling or scoped timer start
    FUN_007ffa80();
    // Reset some state (maybe player input flag)
    FUN_004706f0(0);
    // Virtual call to state-specific update (offset +0x1c in vtable)
    (*(void (**)(int))(*(int *)this + 0x1c))(deltaTimeOrInput);
    // Check byte flag at this+0x1b97, bit 0
    if ((*(byte *)((int)this + 0x1b97) & 1) == 0) {
        // Possibly check if character model 250 (0xfa) exists or is active
        flagCheck = FUN_0054f220(0xfa);
        if (flagCheck != '\0') {
            goto skipFlagClear;
        }
    }
    // Clear bit 24 of flag at this+0x1b94
    this[0x6e5] &= 0xfeffffff; // +0x1b94
skipFlagClear:
    // Update audio system
    FUN_00625030();
    // Update animation system
    FUN_0072d8b0();
    // Update debug display with global DAT_00d62a14
    FUN_007f89d0(&DAT_00d62a14);
    // If pointer at this+0x1e70 is non-null, call UI update
    if (this[0x79c] != 0) { // +0x1e70
        FUN_004df600();
    }
}