// FUNC_NAME: LinkedList::getNextNode

int __fastcall LinkedList::getNextNode(int this)
{
    int current;
    int head;
    int listHead;

    // Retrieve list head and check consistency
    getListHead(&head, &listHead);
    current = *(int *)(this + 0x24); // +0x24: m_currentNode

    if (head == 0 || head != this + 0x20) {
        assertFailed();
    }

    if (listHead != current) {
        if (head == 0) {
            assertFailed();
        }
        if (listHead == *(int *)(head + 4)) { // +0x4: m_pNext
            assertFailed();
        }
        // Return offset to the node data (after the next/prev pointers)
        return listHead + 0x10;
    }

    return 0; // No more nodes
}