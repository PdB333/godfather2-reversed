// FUNC_NAME: SomeManager::RemoveObjectFromActiveList
void __thiscall SomeManager::RemoveObjectFromActiveList(int thisPtr, int* arrayDesc, int objectPtr)
{
    uint index = 0;
    if (arrayDesc[1] != 0) {
        int* arr = (int*)*arrayDesc;
        while (*arr != objectPtr) {
            index++;
            arr++;
            if (arrayDesc[1] <= index) {
                return;
            }
        }
        if (0 <= (int)index) {
            // Clear a flag in the object (bit 27 at offset +0x5C)
            *(uint*)(objectPtr + 0x5C) &= 0xF7FFFFFF;
            
            // If not the last element, swap with the last
            if (index != arrayDesc[1] - 1U) {
                *(int*)(*arrayDesc + index * 4) = *(int*)(*arrayDesc + (arrayDesc[1] - 1) * 4);
            }
            arrayDesc[1]--;
            
            // Scoped logging/debug output
            // Build a log record structure on the stack
            // local_c: likely a log type ID (DAT_0112a5a4)
            // local_14: points to a string table or message (PTR_LAB_00d5dbb0)
            // local_10: registers this object
            // local_4: 0 (maybe severity)
            // local_8: pointer to local_14 (for the struct chain)
            int* local_14_ptr = &PTR_LAB_00d5dbb0; // Actually a variable, but for clarity
            int logStruct;
            // The struct seems to be: { pointer to next? , message pointer, thisPtr, 0 }
            // We'll approximate as a call to a logging helper
            LOG_SCOPE(&logStruct, 0, thisPtr, DAT_0112a5a4, PTR_LAB_00d5dbb0);
            
            // Check if this manager still has active references
            if (*(int*)(thisPtr + 0x88) == 0 && 
                *(int*)(thisPtr + 0xA0) == 0 && 
                *(int*)(thisPtr + 0xAC) == 0 && 
                *(int*)(thisPtr + 0xB8) == 0) {
                // All counts zero: disable global debug flag
                FUN_004086d0(&DAT_0112a640);
                return;
            }
            // Otherwise enable it
            FUN_00408680(&DAT_0112a640);
        }
    }
    return;
}