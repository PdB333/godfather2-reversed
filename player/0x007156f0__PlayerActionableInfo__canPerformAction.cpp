// FUNC_NAME: PlayerActionableInfo::canPerformAction
int __thiscall PlayerActionableInfo::canPerformAction(PlayerActionableInfo* this, uint32 actionId) {
    // Check if the entity has a flag at bit 1 of m_flags (offset +0x0C)
    if ((this->m_flags >> 1) & 1) {
        // Extract a cooldown/timer value from bits 9-15 of m_flags, shifted to bits 8-14
        return ((this->m_flags >> 9) << 8);
    }

    // Get the game manager singleton (FUN_00471610)
    GodfatherGameManager* gameManager = GodfatherGameManager::GetInstance();
    // Get a component from the manager's component list at offset 0x30 (index 0)
    ActionComponent* component = static_cast<ActionComponent*>(gameManager->getComponentFromList(gameManager + 0x30, 0));

    if (component != nullptr) {
        char actionNameBuffer[12]; // local_18
        // Convert actionId to a string representation (hash? name?)
        convertActionIdToString(actionId, actionNameBuffer);

        // Call a virtual method on this (vtable offset 0x3c) that likely fills buffers
        char outputBuffer1[4];  // local_24
        char outputBuffer2[12]; // local_c
        (this->*vtable[0x3c])(outputBuffer1, outputBuffer2);

        // Check if the action is allowed by the game systems
        char dataBuffer[8]; // auStack_20
        if (isActionAllowedBySystem(dataBuffer, &outputBuffer2, 0x40122, 0, actionId, 0)) {
            // Finally, ask the component if this action is allowed for this entity
            if (component->allowsAction(actionId)) {
                return 1; // Action allowed
            }
        }
    }
    return 0; // Action not allowed
}