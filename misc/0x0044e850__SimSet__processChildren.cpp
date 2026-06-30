// FUNC_NAME: SimSet::processChildren
void SimSet::processChildren(__thiscall void (*callback)(GameObject*, void*), void* callbackContext)
{
    // Initialization (e.g., reset iterators)
    prepareIteration(); // FUN_004506f0

    // Pointer to current node in linked list (initialized by prepareIteration)
    ChildNode* currentNode = m_pFirstNode; // local_4

    // Index into child array (used when linked list is exhausted)
    uint arrayIndex = 0; // local_8

    if (currentNode != nullptr) {
        do {
            // Iterate through linked list nodes
            while (true) {
                // If the node has a valid child object, invoke the callback
                if (currentNode->childObject != nullptr) { // +0x10
                    callback(currentNode->childObject, callbackContext);
                }

                // Move to the next node in the linked list
                currentNode = currentNode->next; // +0x14

                // If the parent object signals to stop iteration (e.g., during destruction), break
                if (m_nIterationState == -0x50) { // in_EAX compared as -0x50
                    break;
                }

                // If we reached the end of the linked list, try the array of children
                if (currentNode == nullptr) {
                    do {
                        // If we've already processed all array entries, exit the outer loop
                        if (m_nChildCount <= arrayIndex) { // +0x54
                            goto endIteration;
                        }
                        // Fetch the next non-null child from the array
                        currentNode = m_pChildArray[arrayIndex]; // +0x58
                        arrayIndex++;
                    } while (currentNode == nullptr); // Skip null entries
                }
            }
endIteration:
            // Continue outer loop if there are still nodes to process
        } while (currentNode != nullptr);
    }
    return;
}