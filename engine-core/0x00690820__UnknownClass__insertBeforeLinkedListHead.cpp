// FUNC_NAME: UnknownClass::insertBeforeLinkedListHead
void __thiscall UnknownClass::insertBeforeLinkedListHead(int thisPtr, int container)
{
    // thisPtr: object with embedded linked list node at offsets +0x24B4 and +0x24B8
    // container: parent object containing list head at offset +0x48
    int* nextField = (int*)(thisPtr + 0x24B4); // pointer to the "next" field of this node
    int headNode;

    // If container is not null, compute the head node (list dummy) as container + 0x48
    if (container == 0) {
        headNode = 0;
    } else {
        headNode = container + 0x48;
    }

    // Only change if the desired insertion point differs from current next
    if (*nextField != headNode) {
        // Remove this node from its current list if it is already linked
        if (*nextField != 0) {
            listNodeUnlink(nextField); // e.g., FUN_004DAF90 - unlinks node given its next field address
        }
        *nextField = headNode; // set this->next to the head node
        if (headNode != 0) {
            // Insert before head: this->prev = head->prev
            *(int*)(thisPtr + 0x24B8) = *(int*)(headNode + 4);
            // head->prev points to this->next field
            *(int**)(headNode + 4) = nextField;
        }
    }
    return;
}