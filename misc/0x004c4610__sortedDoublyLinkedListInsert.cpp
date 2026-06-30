// FUNC_NAME: sortedDoublyLinkedListInsert
// Inserts a key into a sorted doubly linked list.
// Node structure: [0]=key (uint), [4]=next pointer, [8]=prev pointer (each 4 bytes)
// headPtr is a pointer to the list head pointer (double indirection).
uint* sortedDoublyLinkedListInsert(uint key, uint** headPtr)
{
    uint* node;
    uint* current;
    uint* previous;

    // Case: empty list
    if (*headPtr == nullptr)
    {
        node = (uint*)allocateNode();  // calls FUN_004c4560, allocates a 12-byte node
        node[0] = key;                 // set key at offset 0
        *headPtr = node;               // update head
        return node;
    }

    // Traverse the list to find insertion point
    previous = nullptr;
    current = *headPtr;

    while (current && current[0] < key)
    {
        previous = current;
        current = (uint*)current[1];   // follow next pointer at offset 4
    }

    // Key already exists?
    if (current && current[0] == key)
    {
        return current;
    }

    // Insert new node between previous and current
    node = (uint*)allocateNode();
    node[0] = key;
    node[1] = (uint)current;      // next pointer (offset 4)
    node[2] = (uint)previous;     // prev pointer (offset 8)

    // Update previous node's next pointer or head
    if (previous)
    {
        previous[1] = (uint)node;  // prev->next = node
    }
    else
    {
        *headPtr = node;           // new head
    }

    // Update current node's prev pointer (if not end)
    if (current)
    {
        current[2] = (uint)node;   // current->prev = node
    }

    return node;
}