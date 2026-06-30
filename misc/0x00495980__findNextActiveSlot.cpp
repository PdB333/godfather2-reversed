// FUNC_NAME: findNextActiveSlot
// Function at 0x00495980: Iterator over a 16-slot table of integers (probably object IDs or connection handles).
// Uses a global pointer at 0x012233b4 which points to a manager, with an array at offset 0x4EC.
// Iterator structure: [0] = current value, [1] = index (stored as low byte of int for packing).
// Returns 1 if a non-zero slot is found, else 0.

int __fastcall findNextActiveSlot(int* iterator)
{
    int* managerBase = DAT_012233b4;  // Global manager singleton
    iterator[1] = iterator[1] + 1;    // Advance index

    while (iterator[1] <= 15)         // Max 16 slots (0-15)
    {
        // Read the low byte of the index field (packed inside an int)
        unsigned char slotIndex = *(unsigned char*)&iterator[1];

        // Read the value from the table at managerBase + 0x4EC + (slotIndex * 4)
        int slotValue = *(int*)((char*)(DAT_012233b4 + 0x4EC) + slotIndex * 4);
        // Equivalent: int slotValue = ((int*)((char*)managerBase + 0x4EC))[slotIndex];

        iterator[0] = slotValue;      // Store the found value

        if (slotValue != 0)
            return 1;                 // Found a valid entry

        iterator[1] = iterator[1] + 1; // Move to next slot
    }

    iterator[0] = 0;                  // No valid entry found (already set from last read)
    return 0;
}