// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

// Destructor at 0x005facc0: Cleans up all member sub-objects and linked lists.
// The class holds multiple dynamic arrays of objects with virtual destructors,
// stored as void* member pointers with corresponding factory/interfaces.

void __fastcall GodfatherGameManager::~GodfatherGameManager(void* thisPtr)
{
    int* pNode;
    int* pNextNode;
    void* pSub;
    void* pElement;

    // Set the initial vtable pointer (base class destructor stage)
    *(void**)thisPtr = &PTR_FUN_00e40808;          // +0x00 vtable
    *(void**)((int)thisPtr + 8) = &PTR_LAB_00e40814; // +0x08 secondary vtable

    // Release global resources (mutexes/queues?)
    FUN_00408310(&DAT_01222228);
    FUN_00408310(&DAT_01222220);

    // Clean up member at +0x50 (some pointer to a sub-object)
    if (*(void**)((int)thisPtr + 0x50) != 0) // +0x50 member pointer
    {
        pSub = *(void**)((int)thisPtr + 0x50);
        if (pSub != 0)
        {
            FUN_009c8f10(pSub); // Decrement reference count or similar
        }
        // Call delete via virtual destructor (offset +0x04 in vtable)
        (**(void (__fastcall**)(void*, int))(*(int*)thisPtr + 8))(*(void**)((int)thisPtr + 0x50), 0);
        *(void**)((int)thisPtr + 0x50) = 0;
    }

    // Iterate over a linked list starting at +0x28 (list head)
    // The list contains elements with a pointer at offset +8 to a sub-object
    pNode = *(int**)((int)thisPtr + 0x28); // +0x28 list head (sentinel node)
    // The list is circular: next pointer at offset 0, prev at +4
    pNextNode = (int*)*pNode;
    while (pNextNode != (int*)((int)thisPtr + 0x28))
    {
        pElement = (void*)pNextNode[2]; // +0x08 within node: pointer to sub-object
        // Call destructor on the sub-object via its own vtable (offset 0)
        (**(void (__fastcall**)(void*))pElement)(0);
        // Delete the sub-object via the factory vtable (offset +0x04)
        (**(void (__fastcall**)(void*, int))(*(int*)thisPtr + 0x0C))(pElement, 0);
        pNextNode = (int*)*pNextNode;
    }

    // Remove all remaining nodes from the list by resetting it to empty
    pNode = (int*)*(int*)((int)thisPtr + 0x28);
    *pNode = (int)pNode;
    *(int*)(*(int*)((int)thisPtr + 0x28) + 4) = (int)((int)thisPtr + 0x28);
    *(int*)((int)thisPtr + 0x2C) = 0; // +0x2C count?

    // Delete the nodes themselves (they were allocated with virtual destructor)
    if (pNextNode != (int*)((int)thisPtr + 0x28))
    {
        do
        {
            pNode = (int*)*pNextNode;
            // Call delete on node via interface at +0x04 (using offset +0x04)
            (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x10) + 4))(pNextNode, 0x0C);
            pNextNode = pNode;
        } while (pNode != (int*)((int)thisPtr + 0x28));
    }

    // Call some cleanup function via vtable (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)thisPtr + 0x0C))();

    // Another list at +0x48 (offset 0x48?)
    pNode = (int*)*(int*)((int)thisPtr + 0x48);
    pNextNode = (int*)*pNode;
    *pNode = (int)pNode;
    *(int*)(*(int*)((int)thisPtr + 0x48) + 4) = (int)((int)thisPtr + 0x48);
    *(int*)((int)thisPtr + 0x4C) = 0;
    if (pNextNode != (int*)((int)thisPtr + 0x48))
    {
        do
        {
            pNode = (int*)*pNextNode;
            (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x30) + 4))(pNextNode, 0x0C);
            pNextNode = pNode;
        } while (pNode != (int*)((int)thisPtr + 0x48));
    }

    // Delete the container at +0x48 itself
    (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x30) + 4))(*(void**)((int)thisPtr + 0x48), 0x0C);
    *(void**)((int)thisPtr + 0x48) = 0;

    // Clean up pointer at +0x44
    if (*(void**)((int)thisPtr + 0x44) != 0)
    {
        (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x40) + 4))(*(void**)((int)thisPtr + 0x44), 0);
        *(void**)((int)thisPtr + 0x44) = 0;
    }
    // Call cleanup function via vtable at +0x40 (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)((int)thisPtr + 0x40) + 0x0C))();

    // Clean up pointer at +0x3C
    if (*(void**)((int)thisPtr + 0x3C) != 0)
    {
        (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x38) + 4))(*(void**)((int)thisPtr + 0x3C), 0);
        *(void**)((int)thisPtr + 0x3C) = 0;
    }
    // Call cleanup function via vtable at +0x38 (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)((int)thisPtr + 0x38) + 0x0C))();

    // Clean up pointer at +0x34
    if (*(void**)((int)thisPtr + 0x34) != 0)
    {
        (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x30) + 4))(*(void**)((int)thisPtr + 0x34), 0);
        *(void**)((int)thisPtr + 0x34) = 0;
    }
    // Call cleanup function via vtable at +0x30 (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)((int)thisPtr + 0x30) + 0x0C))();

    // Re-clean the first list at +0x28 (reset again?)
    pNode = (int*)*(int*)((int)thisPtr + 0x28);
    *pNode = (int)pNode;
    *(int*)(*(int*)((int)thisPtr + 0x28) + 4) = (int)((int)thisPtr + 0x28);
    *(int*)((int)thisPtr + 0x2C) = 0;
    if (pNextNode != (int*)((int)thisPtr + 0x28))
    {
        do
        {
            pNode = (int*)*pNextNode;
            (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x10) + 4))(pNextNode, 0x0C);
            pNextNode = pNode;
        } while (pNode != (int*)((int)thisPtr + 0x28));
    }

    // Delete the list container at +0x28 itself
    (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x10) + 4))(*(void**)((int)thisPtr + 0x28), 0x0C);
    *(void**)((int)thisPtr + 0x28) = 0;

    // Clean up pointer at +0x24
    if (*(void**)((int)thisPtr + 0x24) != 0)
    {
        (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x20) + 4))(*(void**)((int)thisPtr + 0x24), 0);
        *(void**)((int)thisPtr + 0x24) = 0;
    }
    // Call cleanup function via vtable at +0x20 (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)((int)thisPtr + 0x20) + 0x0C))();

    // Clean up pointer at +0x1C
    if (*(void**)((int)thisPtr + 0x1C) != 0)
    {
        (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x18) + 4))(*(void**)((int)thisPtr + 0x1C), 0);
        *(void**)((int)thisPtr + 0x1C) = 0;
    }
    // Call cleanup function via vtable at +0x18 (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)((int)thisPtr + 0x18) + 0x0C))();

    // Clean up pointer at +0x14
    if (*(void**)((int)thisPtr + 0x14) != 0)
    {
        (**(void (__fastcall**)(void*, int))(*(int*)((int)thisPtr + 0x10) + 4))(*(void**)((int)thisPtr + 0x14), 0);
        *(void**)((int)thisPtr + 0x14) = 0;
    }
    // Call cleanup function via vtable at +0x10 (offset 0x0C)
    (**(void (__fastcall**)())(*(int*)((int)thisPtr + 0x10) + 0x0C))();

    // Set secondary vtable to a "dying" stage
    *(void**)((int)thisPtr + 8) = &PTR_LAB_00e40818;

    // Clear global singleton flag
    DAT_01223524 = 0;

    // Perform final cleanup (likely deallocate global memory)
    FUN_0049c640();

    return;
}