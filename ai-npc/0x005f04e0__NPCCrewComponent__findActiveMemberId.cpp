// FUNC_NAME: NPCCrewComponent::findActiveMemberId
int NPCCrewComponent::findActiveMemberId(int* outMemberId) {
    // unaff_EDI: register EDI passed from caller, likely a manager instance (e.g., NPCCrewComponent)
    NPCCrewComponent* manager = (NPCCrewComponent*)unaff_EDI;
    Node* currentNode = nullptr;

    // If output pointer is valid, clear it
    if (outMemberId != nullptr) {
        *outMemberId = 0;
    }

    // Guards: manager must exist, list must have entries, and list head must be valid
    if (manager == nullptr) {
        return 0;
    }
    if (this->entryCount == 0) { // offset +0x12 (short)
        return 0;
    }
    currentNode = this->headNode; // offset +0x08 (Node*)
    if (currentNode == nullptr) {
        return 0;
    }

    // Iterate through the linked list of nodes
    while (true) {
        // Each node: +0x04 -> next, +0x08 -> status byte, +0x0C -> object pointer
        Object* obj = currentNode->object;
        if (obj != nullptr && obj->condition >= 1) { // condition at +0x38
            int memberId = obj->id; // id at +0x30
            int validationResult = manager->isMemberValid(memberId); // FUN_005f0be0
            if (validationResult != 0) {
                // Found a valid member
                if (currentNode->statusFlag == 0) { // +0x08 byte
                    *outMemberId = validationResult;
                }
                return (int)currentNode;
            }
        }

        currentNode = currentNode->next; // +0x04
        if (currentNode == nullptr) {
            return 0; // No valid member found
        }
    }
}