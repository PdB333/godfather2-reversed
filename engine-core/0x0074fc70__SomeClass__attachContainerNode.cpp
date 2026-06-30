// FUNC_NAME: SomeClass::attachContainerNode
void __thiscall SomeClass::attachContainerNode(int this, int newNodeBase)
{
    int** headPtrPtr = (int**)(this + 0x60); // pointer to container node pointer at +0x60
    int newNode;

    if (newNodeBase == 0) {
        newNode = 0;
    } else {
        newNode = newNodeBase + 0x48; // offset to the embedded list node
    }

    if (*headPtrPtr != newNode) {
        if (*headPtrPtr != 0) {
            // remove old node from its container (FUN_004daf90 likely unlinks the node)
            FUN_004daf90(headPtrPtr);
        }
        *headPtrPtr = newNode;
        if (newNode != 0) {
            // Save the node's previous pointer (which points to the head pointer) into this+0x64
            *(int*)(this + 100) = *(int*)(newNode + 4); // newNode->prev stored in field at +0x64
            // Set node's prev to point to the container's head pointer location
            *(int**)(newNode + 4) = headPtrPtr;
        }
    }
}