// FUNC_NAME: NodeList::relinkNode
void __thiscall NodeList::relinkNode(int* this, int listHead)
{
    int* currentNode = (int*)*this; // this->currentNode (offset 0x00)
    *this = *(int*)((int)currentNode + 8); // this->currentNode = currentNode->prev (offset 0x08)

    // If the previous node's flag at +0x15 is zero, update its next pointer
    if (*(char*)(*(int*)((int)currentNode + 8) + 0x15) == '\0') {
        *(int**)(*(int*)((int)currentNode + 8) + 4) = this; // prev->next = this (offset 0x04)
    }

    // Link currentNode's next to this->nextEntry
    *(int*)((int)currentNode + 4) = this[1]; // currentNode->next = this->nextEntry (offset 0x04)

    // If this is the head of the list (listHead->headNode->next), update head
    if (this == *(int**)(*(int*)(listHead + 0x1c) + 4)) {
        *(int*)(*(int*)(listHead + 0x1c) + 4) = (int)currentNode; // head->next = currentNode
        *(int**)((int)currentNode + 8) = this; // currentNode->prev = this
        this[1] = (int)currentNode; // this->nextEntry = currentNode
        return;
    }

    int* nextEntry = (int*)this[1];
    if (this == (int*)nextEntry[2]) { // nextEntry->prev? (offset 0x08)
        nextEntry[2] = (int)currentNode; // nextEntry->prev = currentNode
        *(int**)((int)currentNode + 8) = this; // currentNode->prev = this
        this[1] = (int)currentNode; // this->nextEntry = currentNode
        return;
    }

    *nextEntry = (int)currentNode; // nextEntry->data = currentNode? (offset 0x00)
    *(int**)((int)currentNode + 8) = this; // currentNode->prev = this
    this[1] = (int)currentNode; // this->nextEntry = currentNode
}