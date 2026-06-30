// FUNC_NAME: EARSObject::destructorBase
void __fastcall EARSObject::destructorBase(void* this_)
{
    // Set vtable to base class (likely for destructor chain)
    *(uint32_t*)this_ = &vtable_BaseClass;  // +0x00 vtable

    // Set pointer to secondary vtable or function table
    *(uint32_t*)((uint8_t*)this_ + 0x3C) = &subVtable_A;  // +0x3C
    *(uint32_t*)((uint8_t*)this_ + 0x48) = &subVtable_B;  // +0x48

    // Reinitialize sub-objects (calls constructors to reset)
    // subObjA at offset 0x50 (20 dwords)
    subObjA_constructor((uint8_t*)this_ + 0x50);
    // subObjB at offset 0x58 (22 dwords)
    subObjB_constructor((uint8_t*)this_ + 0x58);

    // Remove this object from a global intrusive linked list
    // The list uses a sentinel stored at offset 0x80 (this->listHead)
    // The node itself has a next pointer at offset 0x84 (this->nodeNext)
    uint32_t* listHead = (uint32_t*)((uint8_t*)this_ + 0x80);   // +0x80 pointer to first node (or sentinel?)
    uint32_t* firstNode = *listHead;  // this is the first node pointer

    if (firstNode != nullptr)
    {
        uint32_t* secondNode = (uint32_t*)(firstNode[1]);  // firstNode->next
        if (secondNode == listHead) // if only one node (its next points back to head sentinel)
        {
            // Update sentinel's next to skip this node
            firstNode[1] = *(uint32_t*)((uint8_t*)this_ + 0x84); // this->nodeNext
            goto cleanup;
        }

        // Find predecessor in list (node whose next is this node)
        // Actually traverses to find node whose next points to head sentinel? (different algorithm)
        // This code appears to be a variant: it finds the last node in a circular list
        uint32_t* prevNode = secondNode;
        uint32_t* curNode = (uint32_t*)prevNode[1];
        while (curNode != listHead)
        {
            prevNode = curNode;
            curNode = (uint32_t*)curNode[1];
        }
        // prevNode is the last node (its next points to head sentinel)
        // Update its next to this->next (removes this node from list)
        prevNode[1] = *(uint32_t*)((uint8_t*)this_ + 0x84);
    }

cleanup:
    // Final cleanup (likely deallocation or unregister)
    deleteThis();
}