// FUNC_NAME: PlayerCrewLeaderComponent::updateCrewMemberStates
int PlayerCrewLeaderComponent::updateCrewMemberStates(CrewMemberList* list, bool enable) {
    int focusMemberId = this->getFocusedMemberId();
    if (focusMemberId == 0) {
        return 0;
    }
    Node* headNodePtr = *list->m_pHeadNode;  // list +0x1c: pointer to head node pointer
    Node* currentNode = headNodePtr;
    Node* endSentinel = list->m_pHeadNode;   // sentinel is the same pointer value

    while (true) {
        // Sanity check: verify list pointer is still valid
        if ((currentNode == nullptr) || (currentNode != list->m_pHeadNode)) {
            EA_ASSERT(0);  // FUN_00b97aea
        }
        if (currentNode == endSentinel) {
            break;
        }
        if (currentNode == nullptr) {
            EA_ASSERT(0);
        }
        if (currentNode == list->m_pHeadNode) {
            EA_ASSERT(0);
        }
        int memberId = currentNode->m_memberId;  // +0x10
        if (memberId != focusMemberId) {
            if (!enable) {
                currentNode->m_flags.m_isActive = 0;  // +0x298
            } else if (currentNode->m_flags.m_forceActive == 0) {  // +0x299
                currentNode->m_flags.m_isActive = 1;
            }
        }
        currentNode = this->advanceIterator(currentNode);  // FUN_005e09e0
    }
    return 1;
}