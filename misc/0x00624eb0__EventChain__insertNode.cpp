// FUNC_NAME: EventChain::insertNode
void __thiscall EventChain::insertNode(void* param2, bool param3, EventChainNode* newNode, EventChainNode* existingChain) {
    newNode->owner = this; // field at +0x18 (index 6)

    if (existingChain != nullptr) {
        // Chain already exists: call its handling method and optionally set flag
        existingChain->vtable->handleEvent(param2, param3, newNode);
        if ((char)param3 != 0) {
            existingChain->flags |= 4; // field at +0x14 (index 5)
        }
        return;
    }

    // No existing chain: either store next pointer or handle directly
    if (this->nextNode != nullptr) { // +0x04
        // New node's handler is called with the old next pointer
        newNode->vtable->handleEvent(param2, param3, this->nextNode);
        this->nextNode = newNode;
    } else {
        // No next pointer yet: store node and invoke base handler
        this->nextNode = newNode;
        baseEventHandler(param2, param3); // FUN_00624820
    }
}