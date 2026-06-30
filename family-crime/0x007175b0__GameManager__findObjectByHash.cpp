// FUNC_NAME: GameManager::findObjectByHash
// 0x007175b0: Looks up an object by a specific hash constant (0x332D5A20) from a list stored in the game state.
// Returns a pointer to the matched object if found, otherwise 0.

int __thiscall GameManager::findObjectByHash(int thisPtr)
{
    int manager = *(int *)(thisPtr + 0x18);                // thisPtr->manager (e.g., GodfatherGameManager)
    if (manager == 0) {
        return 0;
    }
    // Bit test at manager+0x1F58, bit 0xB (flags indicating busy/shutdown?)
    if ((*(uint *)(manager + 0x1F58) >> 0xB) & 1) {
        return 0;
    }

    uint count = *(uint *)(manager + 0x744);               // Number of objects in the list
    int result = thisPtr;                                  // Use thisPtr as default (will be overwritten on match)
    if (count != 0) {
        for (uint index = 0; index < count; index++) {
            int* object = (int*)getObjectByIndex(index);  // FUN_00704110: returns pointer to object at given index
            if (object != nullptr) {
                result = 0;
                // Virtual function at vtable offset 0x10: takes a hash constant and pointer to result,
                // returns true if the object matches the hash.
                char found = (*(char(__thiscall**)(int, int*))(*object + 0x10))(0x332D5A20, &result);
                if (found && result != 0) {
                    return result;
                }
            }
        }
    }
    return 0;
}