// FUNC_NAME: EntityManager::registerEntity
void __thiscall EntityManager::registerEntity(int thisPtr, int objectPtr, char isNewAllocation)
{
    uint index = 0;
    int *listPtr;
    
    if (*(uint *)(thisPtr + 0x18) != 0) {
        listPtr = *(int **)(thisPtr + 0x14);
        do {
            if (*listPtr == objectPtr) {
                if ((int)index >= 0) {
                    return; // already registered
                }
                break;
            }
            index++;
            listPtr++;
        } while (index < *(uint *)(thisPtr + 0x18));
    }
    
    if (isNewAllocation == 0) {
        // Add to existing array
        FUN_006b44a0(&objectPtr);
    } else {
        // Allocate new slot and store pointer
        int *newSlot = (int *)FUN_006bee40(0);
        *newSlot = objectPtr;
    }
    
    // Set registration flag on the object
    uint *flagsPtr = (uint *)(objectPtr + 0x5c);
    *flagsPtr |= 0x400000;
    
    FUN_0083e370(1);
}