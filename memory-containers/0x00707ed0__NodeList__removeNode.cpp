// FUNC_NAME: NodeList::removeNode
void __thiscall NodeList::removeNode(void* this, void* node)
{
    // Pointer to the list's head node stored at this+0x298
    Node* head = *(Node**)((char*)this + 0x298);
    if (head != nullptr) {
        // Temporary sentinel node using a static vtable
        Node sentinel;
        sentinel.vtable = &PTR_FUN_00e31e2c; // static vtable for list nodes

        // Calculate the embedded list node pointer inside the external object (offset +0x48)
        Node* entry = (node != nullptr) ? (Node*)((char*)node + 0x48) : nullptr;

        // Remember the original next pointer of the entry
        Node* savedNext = (entry != nullptr) ? entry->next : nullptr;

        // Mark the entry as removed by setting its next to point to the local sentinel
        // (decompiled: *(int **)(local_14 + 4) = &local_14, which means entry->next = &entry)
        if (entry != nullptr) {
            entry->next = (Node*)&entry; // actually points to the local pointer variable; used for detection
        }

        // Detach the old head from the list structure
        Node* oldHead = head; // head is the list head, but we pass &local_c which might be head->someField
        FUN_00408a00(&oldHead, 0); // likely detaches the list

        // Free/release the list head structure
        FUN_00408310(head);
        // Clear the head pointer
        *(Node**)((char*)this + 0x298) = nullptr;

        // Destroy the entry if it existed
        if (entry != nullptr) {
            FUN_004daf90(&entry); // destructor or deallocation
        }
    }
}