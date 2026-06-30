// FUNC_NAME: ObjectManager::updateAndCleanupObjects
void ObjectManager::updateAndCleanupObjects(void)
{
    int *pCurrent;
    int *pNext;
    int currentObj;
    int *pObjList;
    
    currentObj = DAT_01205514; // Global object list head pointer
    if (DAT_01205514 != 0) {
        do {
            // Update object state
            FUN_0051b120(); // Object::update
            FUN_0051b0b0(currentObj); // Object::postUpdate
            // Mark object as updated (bit 0x200000)
            *(uint *)(currentObj + 0xc) = *(uint *)(currentObj + 0xc) | 0x200000;
            FUN_0051d6b0(); // Some global update function
            // Clear object's child list if present
            if (*(undefined4 **)(currentObj + 8) != (undefined4 *)0x0) {
                **(undefined4 **)(currentObj + 8) = 0;
                *(undefined4 *)(currentObj + 8) = 0;
            }
            pNext = (int *)(currentObj + 0x14); // +0x14 next object pointer
            currentObj = *pNext;
        } while (*pNext != 0);
    }
    
    // Second pass: remove objects that are marked for deletion
    pObjList = &DAT_01205514;
    currentObj = DAT_01205514;
    while (currentObj != 0) {
        currentObj = *pObjList;
        if ((*(uint *)(currentObj + 0xc) & 0x200000) == 0) {
            // Object not updated, skip to next
            pObjList = (int *)(currentObj + 0x14);
        }
        else {
            // Object was updated, remove from list
            *pObjList = *(int *)(currentObj + 0x14);
            FUN_0051a5e0(unaff_EDI, unaff_ESI); // Object destructor
            // Add to free list (DAT_01206880 + 0x14 is free list head)
            pCurrent = (int *)(DAT_01206880 + 0x14);
            **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01125180; // Free list sentinel
            *pCurrent = *pCurrent + 4;
            pNext = (int *)(*pCurrent + 3U & 0xfffffffc);
            *pCurrent = (int)pNext;
            *pNext = currentObj;
            *pCurrent = *pCurrent + 4;
        }
        currentObj = *pObjList;
    }
    return;
}