// FUNC_NAME: SimManager::removeObjectsOfType
// Address: 0x005e51a0
// Removes all sim objects of a specific type from the object manager.
// Called during cleanup (e.g., when a player leaves or a type is unloaded).

extern void removeObjectFromSlot(int slotIndex, void* objectPtr); // FUN_005dbc10
extern void clearSlot(int slotIndex); // FUN_005e63e0

int __thiscall SimManager::removeObjectsOfType(int thisPtr, int typeId)
{
    int* slotArray = *(int**)(thisPtr + 0x603c); // Array of slot entries, each 0x74 bytes (0x1d ints)
    int* current;
    int index = 0;
    int result = 0;

    if (slotArray != nullptr) {
        int* endSlot = slotArray + 0x3a00; // 512 slots total (0x3a00/0x1d)
        for (current = slotArray; current < endSlot; current += 0x1d) {
            // Each slot entry layout:
            // [0] = pointer to object
            // [1] = pointer to type descriptor (with type ID at offset 4)
            if (current[0] != 0) {                // Object present
                if (current[1] != 0) {            // Type info valid
                    // Compare the type ID (at +4 from type descriptor) with the target
                    if (*(int*)(current[1] + 1) == typeId) {
                        removeObjectFromSlot(index, (void*)current[0]);
                    }
                }
                clearSlot(index);
            }
            ++index;
        }
        result = 1;
    }
    return result;
}