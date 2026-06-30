// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Constructor for the main game manager. Sets up memory pools and initializes subsystems.
void __thiscall GodfatherGameManager::GodfatherGameManager(void)
{
    int iVar1;
    undefined4 *pNextNode;
    undefined4 *pPrevNode;
    undefined4 *pCurrentNode;
    undefined4 *pLastNode;
    int iCount;
    undefined4 *pNodePool;
    undefined4 *pThis; // ecx (this pointer)

    // Set base class vtable pointer
    *pThis = &PTR_LAB_00e38370;

    // Call virtual function on a subobject at offset 0x37C04 from this
    // The subobject's vtable is used to call at offset 0xc (likely a virtual init method)
    (**(code **)(*(int *)pThis[0xdf01] + 0xc))();

    // Initialize memory manager (maybe EA's HeapMgr)
    FUN_0066e1d0();

    // Initialize a pool of 143 objects (each 0x50 bytes) located at the end of this object
    pNodePool = pThis + 0x10c04; // Start pool at offset 0x10c04
    iCount = 0x8f;               // 143 entries
    pCurrentNode = pThis + 0x10c4d; // End of pool + some offset

    do {
        iVar1 = *(int *)(pCurrentNode - 0x50);  // Read first field of the previous node
        pLastNode = pCurrentNode - 0x50;        // Pointer to previous node
        pNodePool = pNodePool - 0x50;           // Move pool pointer back

        if (iVar1 != 0) {
            // If previous node's first field is non-null, it's part of a linked list.
            // Perform list removal/relinking for the node at pLastNode
            pNextNode = *(undefined4 **)(iVar1 + 4); // Get next pointer of the node
            if (pNextNode == pLastNode) {
                // If next points to the node we're about to free, update it directly
                *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(pCurrentNode - 0x4f);
            }
            else {
                // Otherwise traverse the list to find the node pointing to pLastNode
                pPrevNode = (undefined4 *)pNextNode[1];
                while (pPrevNode != pLastNode) {
                    pNextNode = (undefined4 *)pNextNode[1];
                    pPrevNode = (undefined4 *)pNextNode[1];
                }
                // Update the node that points to pLastNode
                pNextNode[1] = *(undefined4 *)(pCurrentNode - 0x4f);
            }
        }

        iCount = iCount - 1;
        // Set vtable pointer for each node in the pool (each node is an object)
        *pNodePool = &PTR_LAB_00e38340;
        pCurrentNode = pLastNode; // Move backward through the array
    } while (-1 < iCount);

    // Initialize 200 additional objects (perhaps NPC slots or other managers)
    iCount = 199;
    do {
        FUN_005231b0();
        iCount = iCount - 1;
    } while (-1 < iCount);

    // Set derived class vtable pointer (final vtable for this class)
    *pThis = &PTR_LAB_00e38374;

    // Clear a global flag (possibly initialization complete)
    DAT_012234d0 = 0;
}