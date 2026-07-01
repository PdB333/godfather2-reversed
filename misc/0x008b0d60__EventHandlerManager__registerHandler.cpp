// FUNC_NAME: EventHandlerManager::registerHandler
// Function address: 0x008b0d60
// This method registers a new handler (param_2) into the manager's handler list.
// For each existing subscription whose key matches the handler's key, the
// subscription is appended to the handler's own subscription list.

void __thiscall EventHandlerManager::registerHandler(int thisPtr, int handlerPtr)
{
    // Get the current handler count (+0x08)
    int handlerCount = *(int *)(thisPtr + 0x08);
    bool alreadyPresent = false;

    // Check if handler is already in the list
    if (handlerCount != 0) {
        // Get the pointer to the array of handler nodes (+0x04)
        int** handlerArray = (int**)*(int *)(thisPtr + 0x04);
        for (int i = 0; i < handlerCount; i++) {
            // Each entry is a pointer to a HandlerNode; first field of node is the actual handler pointer
            if (*handlerArray[i] == handlerPtr) {
                alreadyPresent = true;
                break;
            }
        }
        if (alreadyPresent) {
            return;
        }
    }

    // Allocate a new HandlerNode (size 0x10 = 16 bytes)
    int* newNode = (int*)FUN_009c8e50(0x10); // custom allocator or operator new
    if (newNode == nullptr) {
        newNode = nullptr; // redundant, kept for clarity
    } else {
        // Initialize node: fields at offsets +0x00, +0x04, +0x08, +0x0C
        // +0x00: the handler pointer
        // +0x04: pointer to dynamic array of subscription pointers (initially empty)
        // +0x08: count of subscriptions
        // +0x0C: capacity of the subscription array
        newNode[1] = 0;   // m_subscriptions = nullptr
        newNode[2] = 0;   // m_subCount = 0
        newNode[3] = 0;   // m_subCapacity = 0
        newNode[0] = handlerPtr; // m_handler
    }

    // Grow the handler list if full (dynamic array pattern)
    int handlerCapacity = *(int *)(thisPtr + 0x0C);
    if (handlerCount == handlerCapacity) {
        int newCapacity = (handlerCapacity == 0) ? 1 : handlerCapacity * 2;
        FUN_008affc0(newCapacity);  // reallocates the handler array per new capacity
    }

    // Append new node to the handler array
    int** handlerArray = (int**)*(int *)(thisPtr + 0x04);
    handlerArray[handlerCount] = (int*)newNode;
    *(int *)(thisPtr + 0x08) = handlerCount + 1;

    // Now iterate over all subscriptions in the manager (+0x1C array, +0x20 count)
    int subCount = *(int *)(thisPtr + 0x20);
    if (subCount != 0) {
        int** subArray = (int**)*(int *)(thisPtr + 0x1C);
        // For each subscription, check if its key matches the handler's key
        for (int i = 0; i < subCount; i++) {
            int* subscription = subArray[i];
            // Compare four ints at offsets 0x134,0x138,0x13C,0x140
            // with handler fields at offsets 0x20,0x24,0x28,0x2C
            if (*(int *)(subscription + 0x134) == *(int *)(handlerPtr + 0x20) &&
                *(int *)(subscription + 0x138) == *(int *)(handlerPtr + 0x24) &&
                *(int *)(subscription + 0x13C) == *(int *)(handlerPtr + 0x28) &&
                *(int *)(subscription + 0x140) == *(int *)(handlerPtr + 0x2C)) {
                // Get the just-inserted handler node
                int* currentNode = (int*)*(int *)(thisPtr + 0x04) + (handlerCount); // handlerCount is old count, new index
                // currentNode points to the node (which is a pointer itself, but we want the node's fields)
                int* nodePtr = (int*)*(int *)(thisPtr + 0x04);
                int* node = (int*)nodePtr[handlerCount]; // the actual node
                // Grow node's subscription array if needed
                int nodeSubCount = *(int *)(node + 0x08);
                int nodeSubCapacity = *(int *)(node + 0x0C);
                if (nodeSubCount == nodeSubCapacity) {
                    int newCapacity = (nodeSubCapacity == 0) ? 1 : nodeSubCapacity * 2;
                    FUN_008aff60(newCapacity); // reallocates node's subscription array
                }
                // Append this subscription pointer to node's subscription array
                int** nodeSubArray = (int**)*(int *)(node + 0x04);
                nodeSubArray[nodeSubCount] = (int*)subscription;
                *(int *)(node + 0x08) = nodeSubCount + 1;
            }
        }
    }
    return;
}