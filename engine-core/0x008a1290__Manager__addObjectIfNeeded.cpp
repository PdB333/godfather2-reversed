// FUNC_NAME: Manager::addObjectIfNeeded
// Address: 0x008a1290
// Role: Adds a new object (size 0x180) to the manager's linked list if the virtual creation check passes.
// Uses a temporary stack node to transfer ownership.

void Manager::addObjectIfNeeded(Data* pData) {
    // Pre-process the input data
    PreprocessData(pData);  // FUN_008a0c90

    // Virtual function at vtable+0x2cc decides whether creation is allowed
    if (IsCreationAllowed()) {
        return;
    }

    // Allocate memory for the new object (0x180 bytes)
    void* newMemory = operator new(0x180);
    Node tempNode;               // stack-based node for insertion

    if (newMemory != nullptr) {
        // Construct the object using pData, returns pointer stored in node->data
        tempNode.data = ConstructObject(pData); // FUN_0089db90
        if (tempNode.data != nullptr) {
            // Set the node's next pointer to itself (sentinel for list insertion)
            tempNode.next = &tempNode; // *(int **)(iStack_8+4) = &iStack_8
        }
    } else {
        tempNode.data = nullptr;
        // next left uninitialized – not used when data is null
    }

    // Insert the temporary node into the manager's list at offset 0x28
    AddToList(&m_list, &tempNode); // FUN_0089fb80(this+0x28, &iStack_8)

    // Release the temporary node if it held a valid object
    if (tempNode.data != nullptr) {
        ReleaseNode(&tempNode); // FUN_004daf90(&iStack_8)
    }
}