// FUNC_NAME: IntrusiveListArray::reserveCapacity
void __thiscall IntrusiveListArray::reserveCapacity(int *this, uint newCapacity)
{
    int *newData;
    int iVar2;
    int *oldNode;
    uint i;
    int *newNode;

    // If current capacity is insufficient, allocate new array
    if ((uint)this[2] < newCapacity) {
        newData = (int *)operator new[](newCapacity * 8); // FUN_009c8e80
        if (this[0] != 0) {
            i = 0;
            newNode = newData;
            if (this[1] != 0) {
                do {
                    oldNode = (int *)(this[0] + i * 8);
                    if (newNode != (int *)0x0) {
                        // Copy the list node data:
                        // newNode[0] = pointer to the object
                        // newNode[1] = previous next pointer (intrusive list)
                        iVar2 = *oldNode;
                        *newNode = iVar2;
                        newNode[1] = 0;
                        if (iVar2 != 0) {
                            // Update the object's list pointer (offset +0x04)
                            newNode[1] = *(int *)(iVar2 + 4);
                            *(int **)(iVar2 + 4) = newNode;
                        }
                    }
                    // Clean up the old node (detach? destructor)
                    if (*oldNode != 0) {
                        FUN_004daf90(oldNode); // likely destroyListElement
                    }
                    i = i + 1;
                    newNode = newNode + 2;
                } while (i < (uint)this[1]);
            }
            // Free old array
            operator delete[](this[0]); // FUN_009c8f10
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}