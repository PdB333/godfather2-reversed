// FUNC_NAME: initializeResourceSlots
void __cdecl initializeResourceSlots(void)
{
    const char* namePtr;
    int slotPointer;
    char slotIndex;
    int currentSlot;

    currentSlot = 0;
    do {
        // Get the string pointer from a global array of 21 resource names
        namePtr = gResourceNameTable[currentSlot];
        // Traverse the string to its null terminator (side effect: force string access)
        do {
            char c = *namePtr;
            namePtr = namePtr + 1;
        } while (c != '\0');

        // Call function that returns a pointer to a slot structure (0x38920)
        slotPointer = FUN_00638920();

        // Set flag byte at offset +5: enable bit 4 (0x10)
        *(unsigned char*)(slotPointer + 5) |= 0x10;

        // Store the slot index+1 at offset +6 (1-based index)
        slotIndex = (char)currentSlot;
        *(char*)(slotPointer + 6) = slotIndex + 1;

        currentSlot = currentSlot + 1;
    } while (currentSlot < 0x15); // 21 slots
}