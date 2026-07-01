// FUNC_NAME: ContextManager::pushScopedContext
// Function address: 0x008fa460
// Pushes a temporary scoped context into a linked list rooted at this+0x160.
// The context is represented by a stack-allocated node (ScopeNode) that gets inserted
// into a singly linked list at offset 0x4c of the list head (pListHead).
// After performing some initialization (via FUN_008c6d20/FUN_0043c6f0), the node is removed
// and the linked list is restored.

void __fastcall ContextManager::pushScopedContext(void* thisPtr)
{
    // this+0x160 points to the list head (a structure with linked list fields)
    int* pListHead = *(int**)((int)thisPtr + 0x160); // iVar1

    // Scoped node structure allocated on the stack
    struct ScopeNode {
        void* vtable;          // +0x00 (points to PTR_FUN_00d5dbbc)
        int    magic;          // +0x04 (0x88886a27)
        int    field_08;       // +0x08 (saved next pointer)
        int    field_0C;       // +0x0C (0)
        int    field_10;       // +0x10 (0)
        int    field_14;       // +0x14 (0)
        int    field_18;       // +0x18 (0)
        int    field_1C;       // +0x1C (0)
        int    field_20;       // +0x20 (0)
        int    field_24;       // +0x24 (0)
        int    field_28;       // +0x28 (DAT_01205228)
    } scopeNode; // local_30 etc.

    // Saved previous linked list pointer (at pListHead+0x4c)
    int savedNext; // local_18

    // Initialize scope node fields
    scopeNode.vtable = &PTR_FUN_00d5dbbc;   // local_24 = &PTR_FUN_00d5dbbc
    scopeNode.magic  = 0x88886a27;          // local_20
    scopeNode.field_08 = 0;                 // local_1c
    scopeNode.field_0C = 0;                 // local_18 (actually assigned later)
    scopeNode.field_10 = 0;                 // local_14
    scopeNode.field_14 = 0;                 // local_10
    scopeNode.field_18 = 0;                 // local_c
    scopeNode.field_1C = 0;                 // local_8
    scopeNode.field_20 = 0;                 // local_4? Actually local_4 is set to DAT_01205228, but we map field_28 to that.
    scopeNode.field_24 = 0;                 // not explicitly set? Actually there's local_28 = 0 after setting local_30 etc.
    scopeNode.field_28 = DAT_01205228;      // local_4

    // If the list head exists and the node at listHead+0x48 exists (always true if pListHead non‑zero)
    if ((pListHead != (int*)0) && (pListHead + 0x48 != (int*)0)) {
        // Save the old next pointer (at pListHead+0x4c)
        savedNext = *(int*)((int)pListHead + 0x4c); // local_18

        // Point pListHead+0x4c to our stack‑based node (so the node is now the list head)
        *(int**)((int)pListHead + 0x4c) = &scopeNode.field_08; // Actually writing &local_1c (scopeNode.field_08)

        // Set our node's next pointer to the node at pListHead+0x48 (the original head)
        scopeNode.field_08 = (int)pListHead + 0x48; // local_1c = iVar1 + 0x48
    }

    int resourceHandle = FUN_008c6d20(2); // uVar2
    // Local variables used for the call to FUN_0043c6f0
    int initStructData = DAT_0112ad8c;     // local_30
    int initStructZero = 0;                // local_28
    void* initStructVtablePtr = &scopeNode.vtable; // local_2c = &local_24 (which is &scopeNode.vtable)
    // Call initialisation routine with the constructed data
    FUN_0043c6f0(resourceHandle, &initStructData, 0);

    // Cleanup: if the node was inserted, remove it from the list
    if (scopeNode.field_08 != 0) {
        FUN_004daf90(&scopeNode.field_08); // removes node and restores the list
    }
}