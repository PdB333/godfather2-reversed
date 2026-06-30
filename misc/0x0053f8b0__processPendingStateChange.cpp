// FUNC_NAME: processPendingStateChange

void __fastcall processPendingStateChange(int thisPtr)
{
    uint flags = *(uint *)(thisPtr + 0x5c);

    if ((flags & 1) != 0) {
        // Clear the "pending" flag
        *(uint *)(thisPtr + 0x5c) = flags & 0xfffffffe;

        if ((flags & 2) == 0) {
            // State type A: call global object update/reset
            FUN_004086d0(&DAT_0121bf38);
            FUN_00408310(&DAT_0121bf38);
        } else {
            // State type B: call different global objects
            FUN_004086d0(&DAT_012069c4);
            FUN_004086d0(&DAT_012069d4);
        }

        // If there's a pending item to enqueue (byte flag true) and pointer is valid
        if ((*(char *)(thisPtr + 0x86c) != '\0') && (*(int *)(thisPtr + 0x868) != 0)) {
            // Add the pending item to the list at offset 0x68
            FUN_009ea940(thisPtr + 0x68, *(int *)(thisPtr + 0x868));
            // Clear the pointer and the pending flag
            *(undefined4 *)(thisPtr + 0x868) = 0;
        }
        // Clear the enqueue flag regardless
        *(undefined1 *)(thisPtr + 0x86c) = 0;
    }
}