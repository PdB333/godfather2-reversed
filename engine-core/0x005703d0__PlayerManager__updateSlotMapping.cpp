// FUNC_NAME: PlayerManager::updateSlotMapping
// Address: 0x005703d0
// This function iterates over the slots in `this` (count at +0x38),
// looks up the corresponding global game object (via a manager at unaff_EDI),
// and writes the local slot index into a field of that object.
// Offsets:
//   this+0x38: number of slots (uint)
//   this+0x60: array of 8-byte entries (each containing a player/game ID at offset 0)
//   globalManager+0x70: pointer to a table structure
//     table+0x1c: pointer to an array of objects
//   globalManager+0x74: short index into that array (stride 0x18)
//   objData+0x10: array of structures (stride 0x14) holding mapping targets
//   globalManager+0xb4: offset within the target structure where the slot index is written

void __thiscall PlayerManager::updateSlotMapping(void* self) {
    // Global manager pointer (from EDI register, set before call).
    // This is likely a singleton or frame-local pointer.
    int* globalManager = (int*)0;  // Replace with actual global/register variable

    int numSlots = *(int*)((char*)self + 0x38);
    if (numSlots != 0) {
        unsigned int i = 0;
        do {
            // Navigate global manager's table hierarchy
            int* tableBase = *(int**)((char*)globalManager + 0x70);
            int* objArray  = *(int**)((char*)tableBase + 0x1c);
            short objIndex = *(short*)((char*)globalManager + 0x74);
            int objData = *(int*)((char*)objArray + 0x14 + objIndex * 0x18);

            // Get the ID for the current slot
            int entryId = *(int*)((char*)self + 0x60 + i * 8);

            int foundIndex = findIndexInTable(entryId, objData);  // 0x005828a0
            if (foundIndex != -1) {
                int targetPtr = *(int*)((char*)objData + 0x10 + foundIndex * 0x14);
                if (targetPtr >= 0) {
                    int writeOffset = *(int*)((char*)globalManager + 0xb4);
                    *(char*)((char*)targetPtr + writeOffset) = (char)i;
                }
            }
            i++;
        } while (i < (unsigned int)numSlots);
    }
}