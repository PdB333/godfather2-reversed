// FUNC_NAME: ObjectManager::~ObjectManager
void __fastcall ObjectManager::~ObjectManager(int *thisPtr)
{
    int *pActiveNode;
    int *pFreeNode;
    int *pPrevFreeNode;

    // Destroy all active objects in the singly-linked list (head at thisPtr[0])
    pActiveNode = (int *)*thisPtr;
    while (pActiveNode != 0) {
        pActiveNode = (int *)*thisPtr; // Re-fetch head (may be updated by virtual call)
        // Destroy the object's sub-object at offset 0x18 if present
        if (*(int *)(pActiveNode + 6) != 0) { // +0x18
            FUN_004daf90(pActiveNode + 6); // releaseSubObject
        }
        // Call virtual function at vtable+4 (likely release/destroy) with argument 0
        // This function may remove the node from the list and update *thisPtr
        (**(code **)(*(int *)(DAT_0112aa1c + 0x2c40) + 4))(pActiveNode, 0);
        pActiveNode = (int *)*thisPtr;
    }

    // Free all allocated memory blocks in the doubly-linked free list
    // Head at thisPtr[2], tail at thisPtr[3], sentinel is thisPtr+2
    pFreeNode = (int *)thisPtr[3]; // tail
    while (pFreeNode != thisPtr + 2) {
        int *pCurrent = (int *)thisPtr[2]; // head
        if (pCurrent == 0) {
            pPrevFreeNode = 0;
        } else {
            pPrevFreeNode = (int *)((int)pCurrent - 4); // offset to previous node? Actually this is weird
        }
        // Decrement allocation count
        thisPtr[10]--;
        // Remove node from doubly-linked list
        pFreeNode = (int *)pPrevFreeNode[2]; // next pointer
        int *pNext = (int *)pPrevFreeNode[1]; // previous pointer
        *pFreeNode = (int)pNext;
        *(int **)(pNext + 4) = pFreeNode;
        // Call virtual destructor via first vtable entry
        (**(code **)*pPrevFreeNode)(0);
        pFreeNode = (int *)thisPtr[3]; // re-fetch tail
    }

    // Shutdown subsystem if global flag is set
    if (*(int *)(DAT_0112aa1c + 0x2c88) != 0) {
        FUN_007857b0(thisPtr); // shutdownSubsystem
    }

    // Release resource ID if valid
    if (thisPtr[0xc] != -1) {
        if (DAT_0112af90 != 0) {
            FUN_009450b0(thisPtr[0xc]); // releaseResource
        }
        thisPtr[0xc] = -1;
    }

    // Global cleanup
    FUN_007832f0(); // globalCleanup

    // Clear callback pointer if set
    if (thisPtr[0x15] != 0) {
        *(int *)(thisPtr[0x15] + 8) = 0; // clear callback's field at +8
        thisPtr[0x15] = 0;
    }
}