// FUNC_NAME: Entity::flushPendingQueue
void __fastcall Entity::flushPendingQueue(int thisPtr)
{
    int oldCount;

    if ((*(int *)(thisPtr + 0x16c) == 0) && (*(int *)(thisPtr + 0xfc) == 0)) {
        // Guard: only execute if both flags are zero (e.g., not active and not destroyed)
        oldCount = *(int *)(thisPtr + 0x74);   // +0x74: count of pending items
        *(int *)(thisPtr + 0x74) = 0;          // reset counter before processing
        FUN_006b2f70();                         // begin processing (e.g., lock or reset state)
        for (; oldCount != 0; oldCount--) {
            FUN_006b4da0();                     // process each item (e.g., release or execute)
        }
    }
    return;
}