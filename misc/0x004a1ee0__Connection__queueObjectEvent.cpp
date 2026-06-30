// FUNC_NAME: Connection::queueObjectEvent
// Address: 0x004a1ee0
// Role: Searches a watch list (array of 4 object IDs at +0x12c) for a given object ID.
//       If the ID is found, either processes it immediately (if the queue flag is clear)
//       or queues a pending event (up to 3) for later processing.
//       Returns 1 if the ID is found, 0 otherwise.
// Note: Custom calling convention – ECX is unused, EDX holds the connection object pointer,
//       and EDI holds the object ID to search for. The decompiled prototype shown uses
//       __fastcall with two parameters; the third (EDI) is not captured.

int __fastcall Connection::queueObjectEvent(void* unusedECX, void* connectionObj)
{
    const int watchListBase = 0x12c;        // array of 4 × 8‑byte entries
    const int queueFlagOffset = 0x1c0;      // byte: 0 = process immediately, !=0 = use queue
    const int queueCountOffset = 0x1bc;     // int: number of queued events (max 3)
    const int queueArrayBase = 0x14c;       // array of pending events, each 0x1c bytes

    // objectID is passed in EDI – we emulate it here for clarity.
    // In the actual binary, the caller sets EDI before calling this function.
    int objectID; // = edi

    // Check if the search ID is non‑null (meaningful).
    if (objectID == 0) {
        return 0;
    }

    // Search the 4‑element watch list at +0x12c.
    // Each element is 8 bytes (2 ints), so we step by 2 ints.
    int index = 0;
    int* watchEntry = (int*)((char*)connectionObj + watchListBase);
    while (*watchEntry != objectID) {
        ++index;
        watchEntry += 2;    // advance to next entry (8 bytes)
        if (index > 3) {
            return 0;       // not found
        }
    }

    // Found at index `index` (0‑3).
    char queueFlag = *(char*)((char*)connectionObj + queueFlagOffset);
    if (queueFlag == 0) {
        // Direct processing path.
        FUN_004a1f50(connectionObj, index);
    } else {
        // Queue path – check if we have room.
        int* queueCount = (int*)((char*)connectionObj + queueCountOffset);
        if (*queueCount < 3) {
            int newCount = *queueCount + 1;
            *queueCount = newCount;
            int* newEvent = (int*)((char*)connectionObj + queueArrayBase + newCount * 0x1c);
            newEvent[0] = 3;        // type code for this event
            newEvent[4] = index;    // store the watch‑list index
            return 1;
        }
        // Queue full – still return 1 because the object was found.
    }
    return 1;
}