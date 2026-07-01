// FUNC_NAME: LinkedList::removeNode
void __thiscall LinkedList::removeNode(int *list, int *nodeToRemove)
{
    // list[0] = head pointer (+0x00)
    // list[1] = tail pointer (+0x04)
    // Each node has next pointer at offset 0x00
    
    int *current = (int *)*list; // head
    
    if (nodeToRemove == current) {
        // Removing head
        if (nodeToRemove == (int *)list[1]) {
            // Single element: head == tail
            int next = *current;
            *list = next;
            list[1] = next;
            return;
        }
        // Head but not tail
        *list = *current;
        return;
    }
    
    // Traverse to find nodeToRemove
    int *previous = nullptr;
    do {
        previous = current;
        if (previous == nullptr) {
            // Node not found? (original code had a check against null)
            if (*nullptr != nodeToRemove) { // This is suspicious, likely a bug in decompilation
                return;
            }
            break;
        }
        current = (int *)*current; // advance to next
    } while (current != nodeToRemove);
    
    // Unlink nodeToRemove
    *previous = *nodeToRemove;
    
    // If nodeToRemove is tail, update tail to previous
    if ((int *)list[1] == nodeToRemove) {
        list[1] = (int)previous;
    }
}