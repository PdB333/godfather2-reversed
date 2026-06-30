// FUNC_NAME: SomeContainer::initializeNode
undefined4* SomeContainer::initializeNode(undefined4* param_1)
{
    // in_EAX is the 'this' pointer (ECX in __thiscall)
    int* vtablePtr = *(int**)this;          // +0x00: vtable pointer
    int someField = this[1];                // +0x04: some integer field

    // Call virtual function at vtable+8 (likely a cleanup/destructor)
    (*(code**)(*vtablePtr + 8))(vtablePtr);

    // If someField is zero, no copy; otherwise call FUN_004265d0 (maybe a copy constructor)
    undefined4 copyResult;
    if (someField == 0) {
        copyResult = 0;
    } else {
        copyResult = FUN_004265d0(someField, vtablePtr);
    }

    // Call another initialization function with param_1 (the object to initialize)
    FUN_005f9680(param_1, vtablePtr, copyResult);

    // Check if param_1[1] (a pointer field) is null; if so, use a local buffer
    undefined4* bufferPtr = (undefined4*)param_1[1];
    undefined4 localBuffer[3]; // uStack_c, uStack_8, uStack_4
    if (bufferPtr == (undefined4*)0x0) {
        localBuffer[0] = 0;
        localBuffer[1] = 0;
        localBuffer[2] = 0;
        bufferPtr = localBuffer;
    }

    // Call virtual function on param_1's vtable with arguments 0xc and bufferPtr
    // This likely allocates or initializes internal storage
    int nodePtr = (*(code**)(**(undefined4**)param_1))(0xc, bufferPtr);
    if (nodePtr != 0) {
        *(int*)nodePtr = nodePtr;       // self-referential pointer (linked list node)
    }
    if ((int*)(nodePtr + 4) != (int*)0x0) {
        *(int*)(nodePtr + 4) = nodePtr; // another self-link
    }

    // Store the node pointer and zero in param_1's fields
    param_1[7] = 0;                     // +0x1C: some count or flag
    param_1[6] = nodePtr;              // +0x18: pointer to the node

    return param_1;
}