// FUNC_NAME: Entity::updateLifecycle
// Function at 0x004eba30 - Decrements lifetime timers and manages slot usage table
// Called from 0x00500c10 (likely per-frame tick)
// Uses __thiscall: this in EAX

void Entity::updateLifecycle(bool bDecrementSecondary) {
    if (this == nullptr) return;

    // Decrement primary life timer at +0x14
    this->m_lifeTimer -= 1;  // +0x14: int16

    if (bDecrementSecondary) {
        // Decrement secondary timer at +0x18 (maybe damage flash or similar)
        this->m_secondaryTimer -= 1;  // +0x18: int16
    }

    // +0x16 holds the slot index assigned to this entity in the global slot table
    int16 slotIndex = this->m_slotIndex;  // +0x16: int16

    // Check if life expired and this entity is the last active one (slotIndex == g_slotCount)
    if (m_lifeTimer < 1 && slotIndex == g_slotCount) {
        // Decrement global active slot counter (DAT_010c2328)
        g_slotCount--;  // DAT_010c2328: int32

        // Walk backwards through the slot usage table (DAT_011947f8) to find a still-active slot
        // Table entries are 0x20 bytes each, with a usage count short at offset +4
        short* pUsage = (short*)((int)&g_slotUsageTable + g_slotCount * 0x20 + 4);
        while (g_slotCount >= 0) {
            if (*pUsage > 0) {
                // Found an active slot, stop cleanup
                return;
            }
            g_slotCount--;
            pUsage -= 0x10;  // Move back 16 bytes (half an entry? Possibly due to struct packing)
        }
    }
}