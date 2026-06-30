// FUNC_NAME: EntryPool::clear

void __fastcall EntryPool::clear(EntryPool* this)
{
    int count;
    int idx;
    Node* nodePtr;
    Node* entryAddr;
    Node* prevNode;

    count = this->count; // param_1[1], number of entries
    // Loop backward from count-1 down to 0
    for (idx = count - 1; idx >= 0; idx--) {
        nodePtr = this->entries[idx].data; // first field: pointer to a node (maybe list head)
        entryAddr = &this->entries[idx];   // address of this entry node (address of the 8-byte node)
        if (nodePtr != 0) {
            prevNode = nodePtr->next; // nodePtr->next (offset +0x4)
            if (prevNode == entryAddr) {
                // nodePtr is directly before entryAddr in the list
                nodePtr->next = entryAddr->next; // remove entryAddr from list
            } else {
                // Walk list starting from nodePtr->next to find entryAddr
                nodePtr = prevNode->next;
                while (nodePtr != entryAddr) {
                    prevNode = prevNode->next;
                    nodePtr = prevNode->next;
                }
                // prevNode now points to the node before entryAddr
                prevNode->next = entryAddr->next; // unlink entryAddr
            }
        }
    }
    // Free the entire entries array
    if (this->entries != 0) {
        operator delete(this->entries); // FUN_009c8f10 is likely operator delete (or custom free)
    }
}