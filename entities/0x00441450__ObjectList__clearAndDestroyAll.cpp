// FUNC_NAME: ObjectList::clearAndDestroyAll
void ObjectList::clearAndDestroyAll()
{
    // this[6] (offset 0x18) = pointer to list root (sentinel node)
    ListNode* root = *(ListNode**)(this + 0x18 / sizeof(int)); // unaff_EDI[6]
    ListNode* current = *root; // piVar1 = *root
    ListNode* next = current->next; // piVar2 = *current

    // Make the list empty by setting root's next/prev to self
    root->next = root;
    root->prev = root;

    // Reset count at this[7] (offset 0x1C)
    *(int*)(this + 0x1C) = 0;

    // If the list was not empty, iterate and destroy each node
    if (next != root) {
        do {
            current = next;
            next = current->next; // piVar1 = *next

            // If the node has a sub-item count (short at offset 0x12)
            short subCount = *(short*)((int)current + 0x12);
            if (subCount != 0) {
                do {
                    // Clean up sub-item array (pointer at offset 0x0C)
                    FUN_00408310(*(void**)((int)current + 0x0C));
                    subCount = *(short*)((int)current + 0x12);
                } while (subCount != 0);
            }

            // Call virtual destructor/release via vtable[1] with flag 0x20
            (**(code**)(*(int*)*this + 4))(current, 0x20);

        } while (next != root);
    }
}