// FUNC_NAME: moveNodeToTailOfGlobalList

// Function at 0x004d8e60: Removes a node from a global singly-linked list and appends it to the tail.
// List uses next pointer at offset +0xF0.
static void __fastcall moveNodeToTailOfGlobalList(void* /* unused this */, void* node)
{
    // Global list pointers
    static void* s_listHead = *(void**)0x012189f8;      // Head of list
    static void* s_listTail = *(void**)0x01218a00;      // Tail of list
    static void* s_lastMovedNode = *(void**)0x012189fc; // Previously moved node (or temporary)

    void* tempHead = s_lastMovedNode;
    void* tempTail = s_listTail;

    if (s_listHead != 0)
    {
        if (s_listHead == node)
        {
            // Node is the head; remove it
            tempHead = s_listHead; // preserve old head
            s_listHead = *(void**)((char*)s_listHead + 0xF0); // head = head->next
        }
        else
        {
            // Search for the node in the list
            tempTail = s_listHead; // start from head
            if (*(void**)((char*)s_listHead + 0xF0) == 0)
                return; // list has only head, node not found

            do
            {
                tempHead = *(void**)((char*)tempTail + 0xF0);
                if (tempHead == node)
                    break;
                tempTail = tempHead;
                if (*(void**)((char*)tempHead + 0xF0) == 0)
                    return; // reached end, node not found
            } while (true);

            // Unlink the node: previous node's next = node's next
            *(void**)((char*)tempTail + 0xF0) = *(void**)((char*)node + 0xF0);
        }

        // Clear the node's next pointer
        *(void**)((char*)node + 0xF0) = 0;

        // Append node to the tail
        tempTail = node;
        if (s_listTail != 0)
        {
            // List is non-empty: link the old tail to this node
            *(void**)((char*)s_listTail + 0xF0) = node;
            s_listTail = node;
            return;
        }
    }

    // If list was empty, set both head and tail to the node
    s_listTail = tempTail;
    s_lastMovedNode = tempHead;
}