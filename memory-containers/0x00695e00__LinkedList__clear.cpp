// FUNC_NAME: LinkedList::clear

void __fastcall LinkedList::clear(LinkedList *this)
{
    // Get the sentinel node from the list header (offset 0x04)
    LinkedListNode *sentinel = *(LinkedListNode **)((int)this + 4);

    // Delete or cleanup the data associated with the sentinel node
    // The data is stored at offset 0x04 of the node
    if (sentinel != nullptr)
    {
        void *data = *(void **)((int)sentinel + 4);
        if (data != nullptr)
        {
            FUN_00695700(data); // Assumed to be a deallocation/cleanup function
        }

        // Reset sentinel's next and prev to itself (circular list)
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

    // Reset the list size (offset 0x08 of this)
    this->size = 0;
}