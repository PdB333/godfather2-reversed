// FUNC_NAME: Sentient::cleanupPendingAction
void __fastcall Sentient::cleanupPendingAction(void *thisPtr)
{
    // Check bit 0 of flags at +0x39f
    if ((*(byte *)((int)thisPtr + 0x39f) & 1) != 0) {
        // Get pointer at +0x1b0, then check short at +0x1f4 (500) within that object
        if (*(short *)(*(int *)((int)thisPtr + 0x1b0) + 0x1f4) != 0 &&
            *(int *)((int)thisPtr + 0x2d0) != 0) {
            // Call function on the object pointed by +0x2d0
            handleActionableObject(*(int *)((int)thisPtr + 0x2d0));
        }
        // General cleanup
        resetState();
        // Clear bit 8 (0x100) in ushort flags at +0x39e
        *(ushort *)((int)thisPtr + 0x39e) &= 0xfeff; // 0xfeff = ~0x100
    }
}