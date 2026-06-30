// FUNC_NAME: NPCManager::timeSlicedUpdate
// Address: 0x0068ddd0
// This function processes a batch of 3 NPC entries in a time-sliced manner.
// It uses a global frame counter modulo the array size to select the starting index,
// then processes the next 3 consecutive slots.

void NPCManager::timeSlicedUpdate(int thisPtr, uint* arraySize)
{
    // Global frame counter used for time-slicing
    uint startIndex = g_frameCounter % *arraySize;

    // Each iteration processes one entry; the batch size is always 3
    uint processed = startIndex * 3 + 3;   // uVar1 = startIndex * 3 + 3
    uint remaining = processed + startIndex * -3; // = 3 (constant)

    // Pointer to the start of the current entry array (offset 0x14 from this)
    // Each entry is 0x6C bytes
    uint* entryBase = (uint*)(thisPtr + 0x14 + startIndex * 0x6C);

    // Process exactly 3 entries
    do {
        // Check if the entry is active (byte at offset +3)
        if (*(char*)(entryBase + 3) != '\0') {
            // If the function pointer at offset 0 is null, call the default method
            if (*(code**)*entryBase == (code*)0x0) {
                // Call the inherited default via vtable at offset -5 (20 bytes before entry)
                (*(code*)entryBase[-5])();
            } else {
                // Call the custom method, passing a pointer to the base object (-5)
                (*(code*)*entryBase)(entryBase - 5);
            }
        }
        // Advance to next entry (9*4 = 36 bytes; but actual stride is 0x6C = 108 bytes,
        // decompiler may have miscomputed; keeping original logic)
        entryBase += 9;
        remaining--;
    } while (remaining != 0);
}