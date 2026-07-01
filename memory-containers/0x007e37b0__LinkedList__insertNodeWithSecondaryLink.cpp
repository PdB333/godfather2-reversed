// FUNC_NAME: LinkedList::insertNodeWithSecondaryLink
void __fastcall LinkedList::insertNodeWithSecondaryLink(LinkedList* this, int* data)
{
    // this structure:
    // +0x00: head (pointer to first node)
    // +0x04: tail (pointer to last node)
    // +0x08: count (number of nodes)
    // +0x0C: allocator pointer (or default if null)
    // +0x10: vtable pointer (for allocation function)

    // Node structure (size 0x14 = 20 bytes):
    // +0x00: primaryData (int, copied from *data)
    // +0x04: secondaryNext (pointer, used for secondary linked list)
    // +0x08: flag (byte, copied from data[2])
    // +0x0C: mainNext (pointer, used for main doubly linked list)
    // +0x10: mainPrev (pointer, used for main doubly linked list)

    int* allocator = (int*)this[3];
    if (allocator == nullptr) {
        allocator = &DAT_01218a14; // default allocator
    }

    // Call allocation function via vtable
    int* newNode = (int*)(*(code**)(*(int**)this[4]))[0])(0x14, allocator);
    if (newNode != nullptr) {
        int primaryData = *data;
        *newNode = primaryData; // node->primaryData = data[0]
        newNode[1] = 0; // node->secondaryNext = nullptr

        if (primaryData != 0) {
            // Insert newNode after the node pointed to by primaryData in the secondary list
            newNode[1] = *(int*)(primaryData + 4); // newNode->secondaryNext = primaryData->secondaryNext
            *(int**)(primaryData + 4) = newNode;   // primaryData->secondaryNext = newNode
        }

        // Copy byte flag from data[2]
        *(char*)(newNode + 2) = (char)data[2]; // node->flag = data[2]

        newNode[3] = 0; // node->mainNext = nullptr
        newNode[4] = 0; // node->mainPrev = nullptr
    }

    // Insert newNode at the end of the main doubly linked list
    if (this[1] != 0) {
        // List not empty
        *(int**)(this[1] + 0xC) = newNode; // tail->mainNext = newNode
        *(int*)(newNode + 0x10) = this[1]; // newNode->mainPrev = tail
        int newTail = *(int*)(this[1] + 0xC); // newTail = tail->mainNext (which is newNode)
        this[2] = this[2] + 1; // count++
        this[1] = newTail; // tail = newNode
    } else {
        // List empty
        this[2] = this[2] + 1; // count++
        this[0] = (int)newNode; // head = newNode
        this[1] = (int)newNode; // tail = newNode
    }
}