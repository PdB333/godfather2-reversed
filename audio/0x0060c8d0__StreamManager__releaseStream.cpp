// FUNC_NAME: StreamManager::releaseStream
// Function address: 0x0060c8d0
// Manages release of a stream slot and removal of associated stream from active list.
// Global arrays:
// gStreamActiveFlags[slot] (int) - +0x0 from base DAT_011da7f0? Actually indexed by slot*4, so likely an int array.
// gStreamPlayingFlags[slot] (int) - similarly from DAT_011da7f4
// gActiveStreamList[] - pointers to stream objects (DAT_011da8f0)
// gActiveStreamCount (DAT_01205850)
// gStreamCriticalSection (DAT_012224c0)
// gStreamManager (DAT_01205750) - pointer to manager object with vtable

// Note: This function appears to be a static method or global function; param_1 is a slot index, param_2 is a stream object pointer.
void StreamManager::releaseStream(int slotIndex, Stream* streamPtr, void* userData1, void* userData2)
{
    // Check if stream object exists
    if (streamPtr != NULL) {
        // If stream is already active (flag at offset 0x1c), skip to finalization
        if (*(char*)(streamPtr + 0x1c) != '\0') {
            goto finalize;
        }

        // Check stream activation (this function may set the flag if possible)
        checkStreamActivation(); // FUN_0060b870

        // If stream became active after check, remove it from global active list under critical section
        if (*(char*)(streamPtr + 0x1c) != '\0') {
            EnterCriticalSection(&gStreamCriticalSection);
            int i = 0;
            if (0 < gActiveStreamCount) {
                do {
                    if (gActiveStreamList[i] == streamPtr) {
                        gActiveStreamCount--;
                        if (0 < gActiveStreamCount) {
                            // Swap with last element to maintain contiguous list
                            gActiveStreamList[i] = gActiveStreamList[gActiveStreamCount];
                        }
                        break;
                    }
                    i++;
                } while (i < gActiveStreamCount);
            }
            LeaveCriticalSection(&gStreamCriticalSection);

            // After removal, if stream still active, finalize
            if (*(char*)(streamPtr + 0x1c) != '\0') {
                goto finalize;
            }
        }
    }

    // Ensure slot state flags are set appropriately
    // gStreamActiveFlags is likely an int array; check if not already 1
    if (gStreamActiveFlags[slotIndex] != 1) {
        // Call manager method at vtable offset 0x198 (408): likely "setSlotActive" or "stopStream"
        (**(code**)(*(int*)gStreamManager + 0x198))(gStreamManager, slotIndex, 1);
        gStreamActiveFlags[slotIndex] = 1;
    }

    // gStreamPlayingFlags: check if not 0
    if (gStreamPlayingFlags[slotIndex] != 0) {
        // Call manager method at vtable offset 400 (0x190): likely "setSlotPlaying" or "pauseStream"
        (**(code**)(*(int*)gStreamManager + 400))(gStreamManager, slotIndex, 0, 0, 0);
        gStreamPlayingFlags[slotIndex] = 0;
    }

    return;

finalize:
    // Final processing: could be "postRelease" or "update"
    finalizeStreamRelease(slotIndex, streamPtr, userData1, userData2); // FUN_0060c820
    return;
}