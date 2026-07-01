// FUNC_NAME: LinkedListNode::operator=
int __thiscall LinkedListNode::operator=(LinkedListNode *thisNode, LinkedListNode *sourceNode)
{
    int *thisNextPtr;
    int sourceNext;

    // Copy data at offset +4
    *(int *)((char *)thisNode + 4) = *(int *)((char *)sourceNode + 4);

    // Handle linked list next pointer at offset +8
    thisNextPtr = (int *)((char *)thisNode + 8);
    if (thisNextPtr != (int *)((char *)sourceNode + 8)) {
        sourceNext = *(int *)((char *)sourceNode + 8);
        if (*thisNextPtr != sourceNext) {
            if (*thisNextPtr != 0) {
                // Release old next node
                FUN_004daf90(*thisNextPtr);
            }
            *thisNextPtr = sourceNext;
            if (sourceNext != 0) {
                // Update prev pointer of the new next node to point back to this node
                *(int *)((char *)thisNode + 0xc) = *(int *)(sourceNext + 4);
                *(int **)(sourceNext + 4) = thisNextPtr;
            }
        }
    }

    // Copy remaining data members
    *(int *)((char *)thisNode + 0x10) = *(int *)((char *)sourceNode + 0x10);
    *(long long *)((char *)thisNode + 0x14) = *(long long *)((char *)sourceNode + 0x14);
    *(int *)((char *)thisNode + 0x1c) = *(int *)((char *)sourceNode + 0x1c);
    *(long long *)((char *)thisNode + 0x20) = *(long long *)((char *)sourceNode + 0x20);
    *(int *)((char *)thisNode + 0x28) = *(int *)((char *)sourceNode + 0x28);
    *(int *)((char *)thisNode + 0x2c) = *(int *)((char *)sourceNode + 0x2c);
    *(int *)((char *)thisNode + 0x30) = *(int *)((char *)sourceNode + 0x30);
    *(int *)((char *)thisNode + 0x34) = *(int *)((char *)sourceNode + 0x34);
    *(int *)((char *)thisNode + 0x38) = *(int *)((char *)sourceNode + 0x38);
    *(int *)((char *)thisNode + 0x3c) = *(int *)((char *)sourceNode + 0x3c);
    *(int *)((char *)thisNode + 0x40) = *(int *)((char *)sourceNode + 0x40);

    return (int)thisNode;
}