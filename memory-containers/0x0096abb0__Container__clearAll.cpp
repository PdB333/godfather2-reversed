// FUNC_NAME: Container::clearAll
void __fastcall Container::clearAll(int* this) // 0x0096abb0
{
    // this[0] = pointer to internal data block
    // this[1] = item count (set to 0 at end)
    // this[2] = capacity of slot array
    // this[4] = number of nodes currently in list

    int* internalData = (int*)*this;
    // internalData + 8 (offset 8) holds pointer to slot array (array of node pointers)
    int** slotArray = (int**)(internalData[2]);

    int* currentNode = slotArray[0]; // head node

    while (currentNode != 0)
    {
        // node + 8 (offset 8) holds a pointer to the slot that contains the next node pointer
        int** nextSlot = (int**)(*((int**)(currentNode + 8)));  // iVar1 = next node
        int* nextNode = *nextSlot;

        // Clear the slot pointer (mark slot as free)
        FUN_009c8f10(nextSlot);
        // Release the node memory
        FUN_009c8eb0(currentNode);

        this[4] = this[4] - 1; // decrement node count
        currentNode = nextNode;
    }

    // Zero out all slots in the array (up to capacity inclusive)
    unsigned int i = 0;
    do {
        slotArray[i] = 0;
        i++;
    } while (i <= (unsigned int)this[2]);

    this[1] = 0; // reset item count to zero
}