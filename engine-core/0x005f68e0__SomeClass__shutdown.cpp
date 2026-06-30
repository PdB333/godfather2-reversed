// FUNC_NAME: SomeClass::shutdown
// Address: 0x005f68e0
// Identified role: Destructor/cleanup method that resets vtable and clears internal linked list.
// Structure offsets:
//   +0x00: vtable pointer
//   +0x04: head of singly linked list (ListNode)
//   +0x08: pointer to a resource that requires release via global function

struct ListNode {
    void* field0; // +0x00 (first dword)
    ListNode* pNext; // +0x04 (second dword)
};

void __thiscall SomeClass::shutdown() {
    // Set vtable to first destructor-specific vtable (derived class)
    this->vtable = &g_pVtableDerived; // +0x00

    // Release optional resource if present
    if (this->pResource != 0) { // +0x08
        g_pReleaseFunction(g_SomeGlobal, this->pResource);
    }

    // Switch to base vtable after cleanup
    this->vtable = &g_pVtableBase; // +0x00

    // Clear the linked list: zero out first two fields of each node
    ListNode* pCurr = this->pListHead; // +0x04
    while (pCurr != 0) {
        ListNode* pNext = pCurr->pNext; // +0x04
        pCurr->pNext = 0;
        pCurr->field0 = 0;
        pCurr = pNext;
    }
}