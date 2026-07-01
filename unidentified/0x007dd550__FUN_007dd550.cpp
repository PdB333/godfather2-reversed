// FUNC_NAME: SomeClass::syncState
void __fastcall SomeClass::syncState(int thisPtr)
{
    char cVar1;

    // Check if bit 2 (0x4) is set in the flags at +0x18
    if ((*(uint *)(thisPtr + 0x18) >> 2 & 1) != 0) {
        cVar1 = FUN_008a4380(); // Possibly a global condition check (e.g., isGamePaused?)
        if (cVar1 != '\0') {
            // Clear bit 2 (0x4) from flags
            *(uint *)(thisPtr + 0x18) = *(uint *)(thisPtr + 0x18) & 0xfffffffb;
        }
    }

    // If any of the target values differ from the current values, trigger an update
    if (((*(int *)(thisPtr + 0x10) != *(int *)(thisPtr + 0x18)) ||
        (*(int *)(thisPtr + 0x14) != *(int *)(thisPtr + 0x1c))) ||
       (*(int *)(thisPtr + 0x24) != *(int *)(thisPtr + 0x20))) {
        FUN_007dd3c0(); // Likely a function that applies the pending changes
    }

    // If the "dirty" flag at +0xd is set, clear both flags at +0xc and +0xd
    if (*(char *)(thisPtr + 0xd) != '\0') {
        *(undefined1 *)(thisPtr + 0xc) = 0;
        *(undefined1 *)(thisPtr + 0xd) = 0;
    }

    // Copy target values to current values (sync)
    *(undefined4 *)(thisPtr + 0x10) = *(undefined4 *)(thisPtr + 0x18);
    *(undefined4 *)(thisPtr + 0x14) = *(undefined4 *)(thisPtr + 0x1c);
    *(undefined4 *)(thisPtr + 0x24) = *(undefined4 *)(thisPtr + 0x20);
}