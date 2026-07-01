// FUNC_NAME: SimManager::processScheduledTasks
void __fastcall SimManager::processScheduledTasks(int thisPtr)
{
    int globalStatePtr = DAT_01129c4c; // pointer to global state (likely singleton)
    int localPointer[2]; // used as a temporary pointer/size pair (e.g., for an event node)

    if (*(int *)(thisPtr + 0x1c) == 0) {
        // Transitioning to idle or cleanup state
        FUN_004086d0(&DAT_012069c4); // likely debug log or notification
        if (*(int *)(thisPtr + 0x24) != 0) {
            FUN_004daf90((undefined4 *)(thisPtr + 0x24)); // free allocated memory at +0x24
            *(int *)(thisPtr + 0x24) = 0;
        }
        if (*(char *)(globalStatePtr + 0x48) != '\0') {
            FUN_00939b50(); // handle global flag (maybe start new sequence)
            return;
        }
    }
    else if ((*(char *)(globalStatePtr + 0x48) != '\0') &&
             ((*(uint *)(globalStatePtr + 0x5c) >> 10 & 1) == 0)) {
        // Global condition allows processing of queued events
        localPointer[0] = 0;
        localPointer[1] = 0;
        FUN_0094ec90((int *)localPointer); // retrieve next pending event node
        if (localPointer[0] != 0) {
            if (localPointer[0] != 0x48) {
                // Invoke event handler with two parameters from the node at offsets 0x18 and 0x1c
                FUN_00939af0(*(uint *)(localPointer[0] + 0x18),
                             *(uint *)(localPointer[0] + 0x1c));
                // Adjust pointer to get index (offset -0x48) and store result in global
                int adjustedPtr = (localPointer[0] == 0) ? 0 : (localPointer[0] - 0x48);
                *(int *)(DAT_01129938 + 0x28) = *(int *)(adjustedPtr + 100); // +100 = +0x64
                FUN_0094eb30((int *)localPointer); // cleanup or mark as processed
                *(int *)(thisPtr + 0x20) = 0; // reset flag at +0x20
            }
            if (localPointer[0] != 0) {
                FUN_004daf90(localPointer); // free the node memory
            }
        }
    }
    return;
}