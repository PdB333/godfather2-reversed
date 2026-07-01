// FUNC_NAME: intrusiveListInsertEnd
void intrusiveListInsertEnd(int head, int *dataPtr)
{
    // Allocate a new node of size 0x10 from EASTL allocator
    int *node = (int *)FUN_0068ab90(0x10, "EASTL", 0, 0,
                                    "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
                                    0xe9);

    // Node layout: [next(0x00), prev(0x04), dataValue(0x08), someData(0x0C)]
    int *dataField = node + 2; // points to node+0x08

    if (dataField != (int *)0x0) {
        int data = *dataPtr; // value to store in node
        *dataField = data;   // node->dataValue = data
        node[3] = 0;         // node->someData = 0
        if (data != 0) {
            // If data is a valid pointer, update its back-pointer
            // The object at 'data' has a field at +0x04 that points back to the node's data field
            // Also copy the object's previous back-pointer into node->someData
            node[3] = *(int *)(data + 4);        // store old back-pointer
            *(int **)(data + 4) = dataField;     // set new back-pointer to node's data field
        }
    }

    // Insert at end of doubly-linked circular list
    // The list head is at 'head', with fields: +0x00 = next, +0x04 = prev
    // Initial sentinel: head->next = head, head->prev = head (empty list)
    node[0] = head;               // node->next = head (sentinel)
    node[1] = *(int *)(head + 4); // node->prev = head->prev (previous last node)
    // Update the previous last node's next pointer to point to new node
    **(int **)(head + 4) = (int)node;
    // Update head's prev to new node (new last node)
    *(int **)(head + 4) = node;
}