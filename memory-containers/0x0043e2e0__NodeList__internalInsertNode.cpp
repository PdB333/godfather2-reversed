// FUNC_NAME: NodeList::internalInsertNode
// Inserts a new node into a linked list, allocating it from a virtual allocator.
// param_1 (this) points to an object holding:
//   +0x20: pointer to allocator vtable (used to call alloc(size, userData))
//   +0x24: fallback userData pointer (if non-null, else uses stack buffer)
//   +0x38: list head/data pointer (the node to be linked after)
// unaff_EBX and unaff_EBP are additional parameters passed in registers (object callbacks, list context)
void __fastcall NodeList::internalInsertNode(int this)
{
    int* allocatorResult;
    int listData;                    // this+0x38
    int* nodePrevPtr;
    undefined4* allocatorParam;     // this+0x24
    int* newNode;
    int ebxParam;                   // unaff_EBX – object with callbacks at +0x18, +0x1c
    int ebpParam;                   // unaff_EBP – previous node pointer (for linking)
    undefined4 stackBuffer[3];      // fallback userData if allocatorParam is null

    listData = *(int*)(this + 0x38);
    allocatorParam = *(undefined4**)(this + 0x24);
    if (allocatorParam == (undefined4*)0x0) {
        stackBuffer[0] = 0;
        stackBuffer[1] = 0;
        stackBuffer[2] = 0;
        allocatorParam = &stackBuffer[0];
    }

    // Allocate 12 bytes (3 ints) via virtual allocator (vtable at this+0x20)
    newNode = (int*)(**(code**)**(undefined4**)(this + 0x20))(0xc, allocatorParam);
    if (newNode != (int*)0x0) {
        *newNode = listData;                    // node->field0 = listData
    }

    nodePrevPtr = newNode + 1;                  // node->field1 (previous pointer)
    if (nodePrevPtr != (int*)0x0) {
        *nodePrevPtr = ebpParam;                // node->prev = ebpParam
    }

    if (newNode + 2 != (int*)0x0) {
        newNode[2] = (int)stackBuffer;          // node->field2 = stackBuffer pointer
    }

    FUN_0043f560();                             // memory barrier or synchronization

    // Link the new node into the doubly linked list
    *(int**)(listData + 4) = newNode;           // listData->next = newNode
    *(int**)*nodePrevPtr = newNode;             // ebpParam->prev = newNode (nodePrevPtr points to node->prev, which was set to ebpParam)

    // Invoke callbacks if present in ebxParam object
    if (*(int*)(ebxParam + 0x18) != 0) {
        (**(code**)(*stackBuffer + 4))(*(int*)(ebxParam + 0x18));
    }
    if (*(int*)(ebxParam + 0x1c) != 0) {
        (**(code**)(*stackBuffer + 4))(*(int*)(ebxParam + 0x1c));
    }
    return;
}