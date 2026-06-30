// FUNC_NAME: SomeManager::cleanupReleasedSlots
void __fastcall SomeManager::cleanupReleasedSlots(SomeManager* thisPtr)
{
    // thisPtr +0x34: Array of 20 slot entries, each 12 bytes (3 ints)
    // each slot entry: struct { uint32_t status; // flags at offset 0 within entry
    //                           int32_t field4;   // at +4
    //                           void* pData;      // at +8
    //                         }
    // thisPtr +0x2C: Probably a global flag or first entry's status? (accessed via piVar2[-2] on first iteration)
    // The loop checks if the previous entry's status has bit1 set, and if current entry's pData is null,
    // then calls a release function.
    // After processing, it resets the count to 20 and clears the 'dirty' flag at +0x3D4.

    if ((thisPtr->flagsAt_3D4 & 1) != 0) // bit0 indicates a pending cleanup
    {
        int* piEntry = (int*)((char*)thisPtr + 0x34); // start of slot array
        int numSlots = 20; // 0x14
        do
        {
            // piEntry points to the first int of current entry
            // piEntry[-2] is two ints before: this is the status field of the previous entry
            // (or at the very first iteration, it points to memory at offset 0x2C)
            uint32_t prevStatus = (uint32_t)piEntry[-2];
            void* currentData = (void*)piEntry[0]; // pData field of current entry

            // Check if previous entry's bit1 is set and current entry's data pointer is null
            if (((prevStatus >> 1) & 1) != 0 && currentData == nullptr)
            {
                // Release associated resource (likely frees the previous entry's data)
                FUN_006abee0(); // assumed cleanup routine
            }

            piEntry += 3; // move to next entry (3 ints = 12 bytes)
            numSlots--;
        } while (numSlots != 0);

        // Reset state: set count back to 20, clear the dirty flag, zero two counters
        thisPtr->slotCount = 20; // +0x3D0
        thisPtr->flagsAt_3D4 &= 0xFFFFFFFE; // clear bit0
        thisPtr->counterAt_3DC = 0; // +0x3DC
        thisPtr->counterAt_3E4 = 0; // +0x3E4
    }
}