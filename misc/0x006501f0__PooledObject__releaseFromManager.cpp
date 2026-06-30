// FUNC_NAME: PooledObject::releaseFromManager
void PooledObject::releaseFromManager(void)
{
    int *piVar1;
    int iVar2;
    int *piVar3;
    uint uVar4;
    // 'this' is unaff_ESI, manager pointer is unaff_EDI (likely global or passed via register)
    PooledObject *thisObj = this;
    ManagerType *manager = (ManagerType *)unaff_EDI;

    // Set flag at offset 0x20 (bit 4)
    thisObj->flags |= 0x10;

    // If reference count or state at offset 0x04 is zero, set to -1 and call cleanup
    if (thisObj->refCount == 0) {
        thisObj->refCount = -1;
        FUN_0064d4a0(); // likely destructor or cleanup
    }

    // If the object has a valid handle (offset 0x00)
    if (thisObj->handle != 0) {
        // Remove from doubly linked list
        if (thisObj->prev == 0) {
            // If no previous, update head's next pointer (offset 0x1c in head object)
            *(int *)(thisObj->handle + 0x1c) = thisObj->next;
        } else {
            // Otherwise, update previous's next pointer (offset 0x0c)
            *(int *)(thisObj->prev + 0x0c) = thisObj->next;
        }
        if (thisObj->next != 0) {
            // Update next's previous pointer (offset 0x10)
            *(int *)(thisObj->next + 0x10) = thisObj->prev;
        }

        // Remove from hash table (manager at offset 0x218, bucket size 1024)
        uVar4 = (thisObj->handle / 0x34) & 0x3ff; // hash index
        piVar1 = (int *)(manager->hashTable + uVar4 * 4);
        iVar2 = *(int *)(manager->hashTable + uVar4 * 4);
        while (iVar2 != 0) {
            piVar3 = (int *)*piVar1;
            if (piVar3 == thisObj) {
                *piVar1 = piVar3[6]; // remove from bucket list (next pointer at offset 0x18?)
                break;
            }
            piVar1 = piVar3 + 6;
            iVar2 = piVar3[6];
        }

        // Clear linked list pointers and handle
        thisObj->next = 0;
        thisObj->prev = 0;
        thisObj->handle = 0;
    }
    return;
}