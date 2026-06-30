// FUNC_NAME: TNLGhostManager::getGhostNodeAtIndex
// Function address: 0x0045f3b0
// Role: Retrieves the ghost node at a 1-based index from a linked list stored in the manager.
// The manager has a pointer to a list container at offset 0x218.
// The container holds the head node pointer at offset 0x124, and each node has a next pointer at the same offset (0x124).
// Indexing is 1-based (head is a dummy sentinel); returns the real node at the given index or 0 if out of bounds.

int __thiscall TNLGhostManager::getGhostNodeAtIndex(int thisPtr, int index)
{
    int listContainer = *(int*)(thisPtr + 0x218);   // +0x218: pointer to list container struct
    if (listContainer == 0 || index < 0) {
        return 0;
    }

    int node = *(int*)(listContainer + 0x124);      // +0x124: head node pointer (dummy sentinel)
    int currentIndex = 0;
    while (true) {
        node = *(int*)(node + 0x124);               // +0x124: next pointer in each node
        if (node == 0) {
            break;
        }
        currentIndex++;
        if (index <= currentIndex) {
            return node;
        }
    }
    return node;  // returns 0 if list ended before finding the index
}