// FUNC_NAME: EA::Core::ListNode::init
// Address: 0x005f9190
// Role: Initializes a list node with self-referencing pointers (sentinel node) and sets up internal list head

void* EA::Core::ListNode::init(void* this) {
    // Get vtable pointer from the object (already set by caller)
    int** vtable = *(int***)this;
    // Save the second field (offset +0x04) - could be a parent container or previous node
    int secondField = *(int*)((char*)this + 4);

    // Call virtual function at vtable[2] (offset 8) - probably some initialization or reference counting
    (**(code**)(*vtable + 8))(vtable);

    // If secondField is non-zero, perform some operation with it (maybe allocate or attach)
    int allocationResult;
    if (secondField == 0) {
        allocationResult = 0;
    } else {
        allocationResult = FUN_004265d0(secondField, vtable); // unknown allocation/copy
    }

    // Call another function (could be assign or register)
    FUN_005f9900(this, vtable, allocationResult);

    // Get the node pointer from offset +0x04 again (may have changed)
    int* nodePtr = *(int**)((char*)this + 4);
    if (nodePtr == nullptr) {
        // Use local stack as fallback (likely a placeholder for error handling)
        int stackBuffer[3];
        nodePtr = stackBuffer;
    }

    // Call virtual function at vtable[0] (first entry) with argument 0xc (size 12 bytes) and nodePtr
    // This likely allocates a new node of 12 bytes
    int newNode = (*(code**)*vtable)(0xc, nodePtr);
    if (newNode != 0) {
        // Set first field of new node to point to itself (circular list sentinel)
        *(int*)newNode = newNode;
    }
    // Set second field (offset +4) to point to itself
    if ((int*)(newNode + 4) != nullptr) {
        *(int*)(newNode + 4) = newNode;
    }

    // Store the new node at offset +0x18 (param_1[6]) and clear offset +0x1C (param_1[7])
    *(int*)((char*)this + 0x18) = newNode;
    *(int*)((char*)this + 0x1C) = 0;

    return this;
}