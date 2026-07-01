// FUNC_NAME: Entity::cleanupComponentList
void __fastcall Entity::cleanupComponentList(Entity *this) {
    ComponentListNode *node;
    ComponentListNode *nextNode;

    // Set vtable pointer at offset +0x3c to the component list vtable
    if (this == nullptr) {
        node = nullptr;
    } else {
        node = (ComponentListNode *)((uint8_t *)this + 0x3c);
    }
    *node = (ComponentListNode *)&PTR_FUN_00e32808; // set vtable

    // Traverse the linked list starting from the second field of the node (next pointer)
    // Each node has format: [data pointer, next pointer] (both 4 bytes)
    nextNode = (ComponentListNode *)node->next;
    while (nextNode != nullptr) {
        node = (ComponentListNode *)nextNode->next;
        // Clear both pointers in the current node
        nextNode->next = nullptr;
        nextNode->data = nullptr;
        nextNode = node;
    }

    // Call the memory deallocation function (likely operator delete or pool free)
    FUN_0043b400();
}