// FUNC_NAME: LinkedList::moveToHead
void __fastcall LinkedList::moveToHead(LinkedList* this, int node)
{
    int *prevPtr;
    int current;
    int head;
    
    if ((node != 0) && (head = *(int*)this, current = head, head != 0)) {
        // Find the node in the list by following next pointers at +0x20
        while (current != node) {
            prevPtr = (int *)(current + 0x20);  // +0x20: next pointer
            current = *prevPtr;
            if (*prevPtr == 0) {
                return;  // Node not found
            }
        }
        
        // If node found and it's not already the head
        if ((current != 0) && (current != head)) {
            // Unlink node from its current position
            // +0x1c: previous pointer
            if (*(int *)(current + 0x1c) != 0) {
                *(int *)(*(int *)(current + 0x1c) + 0x20) = *(int *)(current + 0x20);
            }
            if (*(int *)(current + 0x20) != 0) {
                *(int *)(*(int *)(current + 0x20) + 0x1c) = *(int *)(current + 0x1c);
            }
            
            // Insert node at head of list
            *(int *)(current + 0x1c) = 0;  // previous = null
            *(int *)(current + 0x20) = *(int*)this;  // next = old head
            *(int *)(*(int*)this + 0x1c) = current;  // old head's previous = node
            *(int*)this = current;  // head = node
        }
    }
}