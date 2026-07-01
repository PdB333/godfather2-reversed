// FUNC_NAME: Entity::getInteractionType
// Address: 0x007dfa80
// This function determines the interaction type for an entity based on its state and flags.
// Probably returns an enum ID (0 = none, 0x96 = threat/dialog?, other from sub function).

__thiscall int Entity::getInteractionType(Entity* this, bool isAIRequested) {
    if (this == nullptr) {
        return 0;
    }

    // External helper: checks if the entity is currently in a conversation/dialog state?
    if (IsEntityInConversation() != 0) {
        // Check bit 10 at offset 0x8e0 (likely a flags field)
        // e.g., bit 0x400 = "HasDialogOption" or "IsInteractable"
        if ((*(uint32_t*)((uint8_t*)this + 0x8e0) >> 10) & 1) {
            if (isAIRequested) {
                // For AI-controlled interactions, return a fixed threat/dialog code (0x96 = 150)
                return 0x96;
            }
            // For player or direct interaction, query a more specific type
            return GetPrimaryInteraction();
        }
    }
    return 0;
}