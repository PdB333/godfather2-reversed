// FUNC_NAME: CombatPerception::checkVisibilityThroughObstructions
bool CombatPerception::checkVisibilityThroughObstructions(void* targetNode) {
    // In EAX: this pointer (CombatPerception)
    // Structure offsets (this):
    // +0x00: vtable pointer
    // +0x04: unknown
    // +0x08: m_targetLabelId (used for name lookup)
    // +0x0C: m_obstructionList (array of pointers to obstruction objects)
    // +0x18: m_obstructionCount
    // +0x1C: m_visibilityEnabled (bool)

    bool visibilityEnabled = *(int*)(this + 0x1C) != 0;
    if (!visibilityEnabled) {
        return false;
    }

    // Traverse linked list from targetNode to find the tail
    void* currentNode = targetNode;
    void* tailNode = targetNode;
    void* nextNode = *(void**)((int)targetNode + 0x0C);
    while (nextNode != nullptr) {
        tailNode = nextNode;
        nextNode = *(void**)((int)nextNode + 0x0C);
    }

    // Call virtual function to get a diagnostic name or label for the target
    // This function likely returns a pointer to a character string.
    char* targetLabel = (char*)this->vtable->getTargetName(/* this pointer? */ &targetNode, *(int*)(this + 0x08), tailNode);
    // The actual call: (*(code **)(*(int *)(*(int *)(*in_EAX + 0x70) + 0x14) + 4))(&targetNode, *(int*)(this+0x08), tailNode)

    if (*targetLabel == '\0') {
        return false;
    }

    uint32_t obstructionCount = *(uint32_t*)(this + 0x18);
    if (obstructionCount > 1) {
        uint32_t tailFlags = FUN_005566a0(tailNode, *(uint32_t*)((int)targetNode + 0x04));
        if (tailFlags != 0) {
            uint32_t blockedMask = FUN_005413f0((tailFlags >> 2) | 0x80000000);
            uint8_t enemyLayer = FUN_00541470(*(uint32_t*)((int)tailNode + 0x1C));
            uint32_t obstructionIndex = 1;
            // Iterate over the obstruction list (starting at offset 0x0C, each entry is a pointer)
            uint32_t* obstructionPtrs = (uint32_t*)(this + 0x0C); // +3 words from start
            while (obstructionIndex < obstructionCount) {
                uint32_t obstruction = obstructionPtrs[obstructionIndex];
                uint32_t obstFlags = FUN_005414c0(*(uint32_t*)(obstruction + 0x24));
                if (((1 << (enemyLayer & 0x1F)) & obstFlags) != 0) {
                    uint32_t globalMask = FUN_00541430();
                    if ((blockedMask & globalMask) == 0) {
                        return false;
                    }
                }
                obstructionIndex++;
            }
        }
    }
    return true;
}