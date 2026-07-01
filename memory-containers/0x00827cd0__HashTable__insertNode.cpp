//FUNC_NAME: HashTable::insertNode
int* __thiscall HashTable::insertNode(int thisPtr, int* outNode, int* newNode)
{
    uint index;
    int capacity;
    int* bucketSlot;
    int oldNode;
    int oldNext;

    capacity = newNode; // Actually param_3, but we'll use newNode
    index = 0;
    if (*(uint*)(thisPtr + 8) != 0) {
        bucketSlot = *(int**)(thisPtr + 4);
        do {
            // Compare key at offset +0xC of the node
            if (*(int*)(*bucketSlot + 0xC) == *(int*)(newNode + 0xC)) {
                oldNode = *(int*)(index * 8 + *(int*)(thisPtr + 4));
                oldNext = 0;
                if (oldNode != 0) {
                    oldNext = *(int*)(oldNode + 4);
                    *(int**)(oldNode + 4) = &oldNode; // Temporarily point to stack
                }
                bucketSlot = (int*)(*(int*)(thisPtr + 4) + index * 8);
                if ((bucketSlot != &newNode) && (*bucketSlot != newNode)) {
                    if (*bucketSlot != 0) {
                        FUN_004daf90(bucketSlot); // Release old bucket head
                    }
                    *bucketSlot = newNode;
                    if (newNode != 0) {
                        bucketSlot[1] = *(int*)(newNode + 4);
                        *(int**)(newNode + 4) = bucketSlot;
                    }
                }
                // Setup outNode to point to oldNode
                outNode[0] = oldNode;
                outNode[1] = 0;
                if (oldNode != 0) {
                    outNode[1] = *(int*)(oldNode + 4);
                    *(int**)(oldNode + 4) = outNode;
                    FUN_004daf90(&oldNode); // Release old node
                }
                if (newNode == 0) {
                    return outNode;
                }
                FUN_004daf90(&newNode);
                return outNode;
            }
            index++;
            bucketSlot += 2;
        } while (index < *(uint*)(thisPtr + 8));
    }
    // No matching key found, need to add new bucket
    capacity = *(int*)(thisPtr + 0xC);
    if (*(int*)(thisPtr + 8) == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        FUN_00827340(capacity); // Resize bucket array
    }
    bucketSlot = (int*)(*(int*)(thisPtr + 4) + *(int*)(thisPtr + 8) * 8);
    *(int*)(thisPtr + 8) = *(int*)(thisPtr + 8) + 1;
    if (bucketSlot != (int*)0x0) {
        *bucketSlot = newNode;
        bucketSlot[1] = 0;
        if (newNode != 0) {
            bucketSlot[1] = *(int*)(newNode + 4);
            *(int**)(newNode + 4) = bucketSlot;
        }
    }
    // Setup outNode to point to newNode
    outNode[0] = newNode;
    outNode[1] = 0;
    if (newNode != 0) {
        outNode[1] = *(int*)(newNode + 4);
        *(int**)(newNode + 4) = outNode;
        FUN_004daf90(&newNode);
    }
    return outNode;
}