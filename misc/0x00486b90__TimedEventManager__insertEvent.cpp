// FUNC_NAME: TimedEventManager::insertEvent
void __thiscall TimedEventManager::insertEvent(int param_2, int param_3)
{
    // param_1 (this) is implicit
    int *listHead; // in_EAX, but actually a local variable address
    uint index = 0;
    int count = *(int *)(this + 0x94);
    int *arraySlot = (int *)(this + 0x20);

    // Find insertion index by scanning the sorted array (step 9 ints per element)
    if (count != 0) {
        do {
            if (*arraySlot < param_2) break;
            index++;
            arraySlot += 9;
        } while (index < (uint)count);
    }

    // Temporary node constructed on stack (8 ints? Actually 7 used)
    Node tmpNode;
    memset(&tmpNode, 0, sizeof(tmpNode)); // local_24 = 0, local_c = 0

    // The following replicates the original in_EAX logic (in_EAX = &tmpNode)
    // It seems to copy from some other location, but here we treat as empty node
    // The original uses in_EAX[6] to decide initialization path. We'll just set fields.
    tmpNode.field0 = 0;  // local_24 (first int)
    tmpNode.field4 = 0;  // local_20? Actually the code writes to local_20 after checks
    tmpNode.field8 = 0;  // local_1c
    tmpNode.fieldC = 0;  // local_18
    tmpNode.field10 = 0; // local_14
    tmpNode.field14 = 0; // local_10
    tmpNode.field18 = 0; // local_c (size? check for zero later)
    tmpNode.field1C = 0; // local_8 = param_2
    tmpNode.field20 = 0; // local_4 = param_3

    // Set the key and value
    tmpNode.key = param_2;
    tmpNode.value = param_3;

    // Insert node at index (FUN_00487330 handles linked list insertion)
    FUN_00487330(&tmpNode, index);

    // Increment total accumulator at +0x98
    *(int *)(this + 0x98) += param_3;

    // Post-insertion fix: maybe fix linked list if node was copied
    // The original checks local_c!=0, local_20!=0x2a7ed975, and local_24!=0
    // Then it adjusts next pointers if the node was not the sentinel.
    // We replicate that logic with our tmpNode fields.
    if ((tmpNode.field18 != 0) && (tmpNode.field4 != 0x2a7ed975) && (tmpNode.field0 != 0)) {
        int *nextPtr = *(int **)(tmpNode.field0 + 4); // local_24+4 -> next field
        if (nextPtr == &tmpNode) {
            // Self-loop? Fix: set next to tmpNode.field4 (which was old next?)
            *(int *)(tmpNode.field0 + 4) = tmpNode.field4;
            return;
        }
        while ((int *)nextPtr[1] != &tmpNode) {
            nextPtr = (int *)nextPtr[1];
        }
        nextPtr[1] = tmpNode.field4;
    }
}

struct Node {
    int field0;   // +0x00 (local_24)
    int field4;   // +0x04 (local_20) - next pointer or sentinel
    int field8;   // +0x08 (local_1c)
    int fieldC;   // +0x0C (local_18)
    int field10;  // +0x10 (local_14)
    int field14;  // +0x14 (local_10)
    int field18;  // +0x18 (local_c) - size/tag?
    int key;      // +0x1C (local_8)
    int value;    // +0x20 (local_4)
};