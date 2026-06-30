// FUNC_NAME: EARSObject::~EARSObject
int* __thiscall EARSObject::destructor(int* thisObj, int destroyFlags)
{
    int* currentNode;
    int* nextNode;

    // Set vtable pointers (assuming multiple inheritance or base class vtables)
    // +0x18 (index 6) = 0x00e355fc
    thisObj[6] = &PTR_LAB_00e355fc;   // Another vtable
    // +0x00 = 0x00e42de4 (primary vtable)
    *thisObj = &PTR_LAB_00e42de4;

    // Traverse linked list starting at offset +0x04
    // Each node has three int fields at offsets 0, 4, 8
    currentNode = (int*)thisObj[1];   // +0x04: head of list
    while (currentNode != (int*)0x0) {
        nextNode = (int*)currentNode[2];   // +0x08: next pointer in node
        // Clear node data (three fields)
        // +0x00: data1
        currentNode[0] = 0;
        // +0x04: data2
        currentNode[1] = 0;
        // +0x08: nextPtr
        currentNode[2] = 0;
        currentNode = nextNode;
    }

    // If destroyFlags has bit 0 set, call delete operator
    if ((destroyFlags & 1) != 0) {
        FUN_009c8eb0(thisObj);   // free/dealloc
    }
    return thisObj;
}