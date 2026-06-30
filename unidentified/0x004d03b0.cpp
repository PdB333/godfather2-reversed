// FUN_004d03b0: ServiceManager::serviceTick
// This function is called each frame to perform maintenance:
//  1. Drain a temporary linked list (maybe a "free list" or "pending list") by iterating through all nodes.
//  2. Destroy all nodes in a "death list" (objects to be deleted), releasing their critical sections and resources.
//  3. Drain a ring buffer of pending work (just updates index, actual processing happens elsewhere in the subsequent vtable calls).
//  4. Call two virtual update functions (primary and secondary) on the manager.

// The global singleton is stored at 0x012234a8.
// Its layout (offsets from the base pointer):
// +0x00: pointer to vtable (Vtbl*)
// +0x08: context pointer (used as argument in secondary update)
// +0x10: head of a temporary singly linked list (first list)
// +0x14: tail of that list
// +0x1C: ring buffer capacity (number of slots)
// +0x20: ring buffer current read/write index
// +0x24: ring buffer number of pending items
// +0x28: CRITICAL_SECTION for ring buffer
// +0x5C: head of death list (doubly linked)
// +0x60: tail of death list

// Each node in the death list (at offset 0x5C) has the following layout:
// +0x00: next pointer
// +0x04: prev pointer
// +0x36: pointer to a resource to be freed (e.g., memory block)
// +0x3A: CRITICAL_SECTION (embedded inside node)

// Function definitions for unknown callees:
// sub_00abd5c0() – pre-destroy notification (no documented params)
// sub_009c8f10(void* ptr) – frees a resource
// sub_009c8f80() – returns a pointer to a vtable for secondary update

void ServiceManager::serviceTick()
{
    // -----------------------------------------------------------------------
    // Step 1: Drain the temporary list at offset 0x10 (head = this->field_0x10)
    // This loop walks through all nodes, updating head and tail pointers.
    // -----------------------------------------------------------------------
    int* pCurrent = reinterpret_cast<int*>(this->field_0x10); // iVar1 = head
    while (pCurrent != nullptr)
    {
        int* pNode = reinterpret_cast<int*>(this->field_0x10); // puVar2 = head
        if (pNode != nullptr)
        {
            if (reinterpret_cast<int*>(this->field_0x14) == pNode) // if head == tail
            {
                this->field_0x14 = 0; // clear tail
            }
            this->field_0x10 = *pNode; // head = next node
        }
        pCurrent = reinterpret_cast<int*>(this->field_0x10);
    }

    // -----------------------------------------------------------------------
    // Step 2: Destroy all nodes in the death list at offset 0x5C
    // -----------------------------------------------------------------------
    pCurrent = reinterpret_cast<int*>(this->field_0x5C); // head of death list
    while (pCurrent != nullptr)
    {
        int* pNode = reinterpret_cast<int*>(this->field_0x5C);
        int* pSavedNode = nullptr; // piVar7
        if (pNode != nullptr)
        {
            pCurrent = reinterpret_cast<int*>(*pNode); // next node
            this->field_0x5C = pCurrent; // update head to next
            pSavedNode = pNode;
            if (pCurrent == 0)
            {
                this->field_0x60 = 0; // clear tail since list empty
            }
            else
            {
                // Update new head's prev pointer to null
                *reinterpret_cast<int*>(pCurrent + 1) = 0; // pCurrent[1] = prev of new head
                *pNode = 0; // disconnect old head's next
            }
        }
        sub_00abd5c0(); // pre-destroy callback
        DeleteCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(pSavedNode + 0x3A)); // +0x3A = offset of CRITICAL_SECTION in node
        if (pSavedNode[0x36] != 0)
        {
            sub_009c8f10(reinterpret_cast<void*>(pSavedNode[0x36])); // free resource pointer at +0x36
        }
        pCurrent = reinterpret_cast<int*>(this->field_0x5C);
    }

    // -----------------------------------------------------------------------
    // Step 3: Drain the ring buffer (queue with count and index)
    // -----------------------------------------------------------------------
    bool bHasItem;
    do {
        bHasItem = false;
        EnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this + 0x28)); // +0x28 = ring buffer critical section
        if (this->field_0x24 != 0) // count > 0
        {
            this->field_0x20++; // increment read/write index
            if (this->field_0x20 >= this->field_0x1C) // modulo [maxSize]
            {
                this->field_0x20 = 0;
            }
            this->field_0x24--;
            bHasItem = true;
        }
        LeaveCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this + 0x28));
    } while (bHasItem);

    // -----------------------------------------------------------------------
    // Step 4: Call primary update (vtable[0])
    // -----------------------------------------------------------------------
    int64_t context = this->field_0x08; // uVar3
    (reinterpret_cast<Vtbl*>(this->vtbl)->primaryUpdate)(0); // vtable[0] called with 0

    // Step 4b: Call secondary update (vtable from another source)
    int* vtbl2 = reinterpret_cast<int*>(sub_009c8f80()); // get vtable pointer
    (reinterpret_cast<Vtbl2*>(*vtbl2)->secondaryUpdate)(context, 0); // vtable[1] called with context and 0

    return;
}