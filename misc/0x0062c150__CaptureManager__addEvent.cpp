// FUNC_NAME: CaptureManager::addEvent
// Function at 0x0062c150 - Records an event into a capture ring buffer.
// Base structure (basePtr) likely represents a capture context with arrays and a buffer descriptor.
// Offsets: +0x00..? array of ints, +0x08 (basePtr[2]) = pointer to buffer descriptor,
// buffer descriptor +0x08 = current write pointer.
void __fastcall CaptureManager::addEvent(int *basePtr, int slotIndex)
{
    int val = basePtr[slotIndex * 2 + 5];          // +0x14 + slotIndex*8
    if (val == -1) {
        // Unfinished capture; log and possibly force a reset
        FUN_00627bd0("unfinished capture");
        val = -2;                                   // decompiler hint: extraout_ECX likely yields -2
    }
    if (val == -2) {
        // Write a new event entry: type 3 and a computed float
        int bufferDesc = basePtr[2];                // +0x08
        float *bufPtr = *(float **)(bufferDesc + 8); // +0x08 from buffer descriptor
        bufPtr[0] = 3.0f;                           // event type constant
        bufPtr[1] = (float)((basePtr[slotIndex * 2 + 4] - slotIndex) + 1); // +0x10 + slotIndex*8
        // Advance write pointer by 8 bytes
        *(int *)(bufferDesc + 8) += 8;
        return;
    }
    // Not a special marker; delegate to another handler
    FUN_00625c60(basePtr[slotIndex * 2 + 4], val);
}