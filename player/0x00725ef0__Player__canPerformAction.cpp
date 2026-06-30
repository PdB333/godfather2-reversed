// FUNC_NAME: Player::canPerformAction
// Address: 0x00725ef0 
// Role: Checks if player can perform an action (e.g., extortion/takedown) by iterating over active dialog/interaction nodes and verifying no blocking condition with the same owner ID.
// Uses a hash constant (0x8bd0e0eb) to identify the specific action type.

bool __thiscall Player::canPerformAction() {
    // +0x120: m_flags (bit mask)
    if (m_flags & 0x100) {
        // +0xcc: m_entityId (owner/player ID)
        FUN_00445410((int*)(this + 0xcc)); // Initialize iterator over dialog nodes (sets local_4, local_8)
        
        // local_4: current node pointer (DialogNode*)
        if (local_4 == nullptr) {
            return true; // No nodes, action allowed
        }
        
        do {
            DialogNode* node = (DialogNode*)local_4;
            // +0x14: node->flags (ushort)
            // +0xc: node->object (pointer to some entity or behavior object)
            if ((node->flags & 0x8000) == 0 &&
                (*(byte*)(*(int*)(node->object) + 4) & 0x10) != 0) { // Check object's type/state at offset +4
                
                Entity* relatedEntity = nullptr; // local_10[0]
                // Virtual call: (*(vtable_ptr+0x10))(object, 0x8bd0e0eb, &relatedEntity)
                // Returns bool indicating success
                bool found = ((bool (__thiscall*)(Entity*, uint, Entity**))(*(int*)(*(int*)(node->object) - 0x3c) + 0x10))(node->object, 0x8bd0e0eb, &relatedEntity);
                
                if (found && relatedEntity != nullptr &&
                    // +0xcc: relatedEntity->m_entityId
                    relatedEntity->m_entityId == this->m_entityId &&
                    // +0x12c (300): relatedEntity->m_actionState
                    relatedEntity->m_actionState != 0 &&
                    relatedEntity->m_actionState != 0x48 &&
                    // +0xe8: relatedEntity->m_stateFlags (byte)
                    (*(byte*)(relatedEntity + 0xe8) & 1) == 0) {
                    return false; // Blocking condition found
                }
            }
            
            // Move to next node in the list
            piVar1 = (int*)(local_4 + 4); // +4: node->next
            local_4 = *piVar1;
            
            // Continue if next pointer is non-null, else fall through to secondary list (local_8)
        } while ((*piVar1 != 0) ||
                 (((local_8 != nullptr) && 
                   (local_8 = (int*)*local_8, local_8 != nullptr) &&
                   (local_4 = local_8[2], local_8[2] != 0))));
    }
    return true; // Default allow
}