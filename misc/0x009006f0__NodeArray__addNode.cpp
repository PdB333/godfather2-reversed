// FUNC_NAME: NodeArray::addNode
void __thiscall NodeArray::addNode(int* this, int* nodeData)
{
    int* piVar1;
    int iVar2;

    iVar2 = this[2]; // capacity
    if (this[1] == iVar2) { // count == capacity
        if (iVar2 == 0) {
            iVar2 = 1;
        } else {
            iVar2 = iVar2 * 2;
        }
        FUN_009004b0(iVar2); // reallocate array to new capacity
    }
    // pointer to new node slot at end of array
    piVar1 = (int*)(this[0] + this[1] * 0xc); // base + count * 12 (node size)
    this[1] = this[1] + 1; // increment count

    if (piVar1 != (int*)0x0) {
        iVar2 = *nodeData; // data pointer from input
        *piVar1 = iVar2;   // node->data = nodeData[0]
        piVar1[1] = 0;     // node->next = NULL initially
        if (iVar2 != 0) {
            // insert node into linked list: node->next = old next of data object
            piVar1[1] = *(int*)(iVar2 + 4); // node->next = data->next (offset +4)
            *(int**)(iVar2 + 4) = piVar1;   // data->next = node
        }
        piVar1[2] = nodeData[2]; // node->value = nodeData[2]
    }
    return;
}