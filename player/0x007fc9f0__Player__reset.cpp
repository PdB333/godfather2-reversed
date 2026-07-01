// FUNC_NAME: Player::reset
void __fastcall Player::reset(int this) // this pointer in ECX
{
    // +0xffc: pointer to a sub-object (likely another component)
    if (*(void**)(this + 0xffc) != (void*)0x0) {
        // Free/release the sub-object
        FUN_004daf90((undefined4*)(this + 0xffc));
        *(void**)(this + 0xffc) = (void*)0x0;
    }

    // +0x1010: player ID (set to invalid -1)
    *(int*)(this + 0x1010) = -1;
    // +0x1014: team ID (invalid)
    *(int*)(this + 0x1014) = -1;
    // +0x1018: slot index (0xFF = none)
    *(char*)(this + 0x1018) = (char)0xff;
    // +0x101c: some counter or flag
    *(int*)(this + 0x101c) = 0;
    // +0x1024: store a global constant (DAT_00d5f520)
    *(int*)(this + 0x1024) = DAT_00d5f520;
    // +0x1020: another field
    *(int*)(this + 0x1020) = 0;
    // +0x1028..0x102a: byte fields (flags/indices)
    *(char*)(this + 0x1028) = (char)0x0;
    *(char*)(this + 0x1029) = (char)0x0;
    *(char*)(this + 0x102a) = (char)0xff;
    // +0x102c, +0x1030, +0x1034: more state fields
    *(int*)(this + 0x102c) = 0;
    *(int*)(this + 0x1030) = 0;
    *(int*)(this + 0x1034) = 0;
}