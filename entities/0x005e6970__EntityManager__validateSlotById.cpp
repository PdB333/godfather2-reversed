// FUNC_NAME: EntityManager::validateSlotById
void __fastcall EntityManager::validateSlotById(uint32_t fullId)
{
    // Extract 16-bit slot index from the full ID
    uint16_t slotIndex = (uint16_t)(fullId & 0xFFFF);
    
    // Validate slot index range (max 512 slots)
    if (slotIndex < 0x200)
    {
        // Compute pointer to the entity in the manager's array
        // g_pEntityArrayBase is a global pointer to the manager (DAT_012234bc)
        // Array of entities starts at offset +0x10 from the base
        // Each entity struct is 0x30 bytes
        Entity* pEntity = reinterpret_cast<Entity*>(
            reinterpret_cast<uint8_t*>(g_pEntityArrayBase) + 0x10 + slotIndex * 0x30);
        
        // Check that the slot exists, its stored ID matches the given full ID,
        // and the entity handle (at offset +0x10) is non-null
        if (pEntity != nullptr &&
            (*(uint32_t*)(reinterpret_cast<uint8_t*>(pEntity) + 0x2C) == fullId) &&
            (*(void**)(reinterpret_cast<uint8_t*>(pEntity) + 0x10) != nullptr))
        {
            // Valid entity - no action needed
            return;
        }
    }
    return;
}