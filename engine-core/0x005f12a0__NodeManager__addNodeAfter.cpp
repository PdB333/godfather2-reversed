// FUNC_NAME: NodeManager::addNodeAfter
void NodeManager::addNodeAfter(void) 
{
    // ESI = new node, EDI = existing node (passed via registers)
    Node* newNode = reinterpret_cast<Node*>(unaff_ESI);
    Node* existing = reinterpret_cast<Node*>(unaff_EDI);

    // Call initialization for the new node (likely sets up default fields)
    initNode(newNode); // FUN_005f57b0

    // If both nodes exist and the existing node has a valid next pointer (offset +0x04 != 0)
    if (existing != nullptr && newNode != nullptr && existing->next != nullptr) // unaff_EDI[1] != 0
    {
        // Insert newNode after existing in the linked list
        newNode->next = existing->next;   // *unaff_ESI = *unaff_EDI;
        existing->count++;                // unaff_EDI[3] = unaff_EDI[3] + 1;
        existing->next = newNode;         // *unaff_EDI = unaff_ESI;
    }

    // Mark newNode as end-of-list (sentinel = -1)
    newNode->sentinel = -1;               // unaff_ESI[6] = 0xffffffff;
    newNode->flags = 0;                   // *(undefined2 *)(unaff_ESI + 4) = 0;

    // Notify a system about this node insertion (using type and callback)
    registerNode(newNode->type, newNode->callback); // FUN_005dbc10(*(undefined2 *)(unaff_ESI + 2), unaff_ESI[9]);

    // If the new node has a callback, execute it and clear the callback info
    if (newNode->callback != nullptr) {
        newNode->callback();              // (*(code *)unaff_ESI[9])();
        newNode->callback = nullptr;      // unaff_ESI[9] = 0;
        newNode->callbackData1 = nullptr; // unaff_ESI[10] = 0;
        newNode->callbackData2 = nullptr; // unaff_ESI[0xb] = 0;
    }
}