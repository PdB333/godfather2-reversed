// FUNC_NAME: ObjectManager::findMatchingObject

undefined4 __fastcall ObjectManager::findMatchingObject(int thisPtr)
{
    char criteriaBuffer[12];
    int iVar1;
    uint index;
    undefined4 result;
    
    // Check if the object list is valid and the global gameplay state is active
    if ((*(int *)(thisPtr + 0x60) != 0) &&    // count of objects in the list
        (**(int **)(DAT_012233a0 + 4) != 0) &&  // global singleton's active flag pointer
        (**(int **)(DAT_012233a0 + 4) != 0x1f30)) // sentinel check (likely a vtable or state ID)
    {
        // Get the current gameplay context (e.g., InputManager, PlayerState, etc.)
        iVar1 = getGameplayContext();  // FUN_00471610
        // Clear the search criteria buffer (12 bytes of zeros)
        clearCriteriaBuffer(criteriaBuffer, 0);  // FUN_00424fb0
        
        index = 0;
        if (*(int *)(thisPtr + 0x60) != 0) {
            while (true) {
                result = *(undefined4 *)(*(int *)(thisPtr + 0x5c) + index * 4);
                // Check if this object matches the search criteria (uses gameplay context offset 0x30)
                if (matchesCriteria(result, iVar1 + 0x30, criteriaBuffer) != '\0') // FUN_006ba510
                    break;
                index++;
                if (*(uint *)(thisPtr + 0x60) <= index) {
                    return 0;
                }
            }
            // Notify that the object was found at this index (e.g., for removal or activation)
            objectFoundAt(index);  // FUN_006ba720
        }
        return result;
    }
    return 0;
}