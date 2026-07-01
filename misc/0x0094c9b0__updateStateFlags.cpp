// FUNC_NAME: updateStateFlags
void __thiscall updateStateFlags(int thisPtr)
{
    uint flags = *(uint *)(thisPtr + 0x11c);

    // Bit 7 set: a pending state change or update flag
    if ((flags & 0x80) != 0) {
        *(uint *)(thisPtr + 0x11c) = flags & 0xFFFFFF7F;  // clear bit 7

        bool canTransition = FUN_0094b9b0();  // (0x0094b9b0) – some condition check

        if (!canTransition) {
            *(uint *)(thisPtr + 0x11c) |= 0x40000;  // set bit 18 – failure/blocked flag
        }
        else if ((*(uint *)(thisPtr + 0x11c) & 0x80000) != 0) {  // bit 19 set
            int index = *(int *)(thisPtr + 4);  // +0x04: entity index / slot ID
            // Global array DAT_00e56a9c – stride 0x2c bytes, indexed by entity index
            int stateInfo = *(int *)(&DAT_00e56a9c + index * 0x2c);
            if (stateInfo == 1) {
                FUN_00948ee0();  // (0x00948ee0) – transition to state 1
                return;
            }
            if (stateInfo == 2) {
                FUN_00948f60();  // (0x00948f60) – transition to state 2
                return;
            }
        }
    }
}