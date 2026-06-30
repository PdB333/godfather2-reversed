// FUNC_NAME: LinkedList::clearAll
// Function at 0x00421010 iterates a singly-linked list starting at offset +4, deletes each node via FUN_009c8eb0 (likely operator delete or node destructor), then zeros head and size.
void LinkedList::clearAll()
{
    // +0x04: pointer to head node
    // +0x08: count/size (int)
    int* head = *(int**)(this + 4);  // current node pointer
    int* next;

    while (head != nullptr)
    {
        // Save next before deleting current
        next = *(int**)(head + 4);  // next node is at +4 within node? Or maybe head->next is at offset 0? Decompiled suggests *(int*)(head + 4) for next.
        // Actually from decompile: iVar1 = *(int *)(*(int *)(unaff_ESI + 4) + 4); -> first deref gets head, second gets head->next at +4? That's ambiguous.
        // Let's keep literal: head->next is at offset +4.
        FUN_009c8eb0(head);  // deallocate node
        head = next;
    }

    // Reset list state
    *(int**)(this + 4) = nullptr;  // head = null
    *(int*)(this + 8) = 0;         // size = 0
}