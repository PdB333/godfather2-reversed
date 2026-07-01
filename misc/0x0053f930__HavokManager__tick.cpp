// FUNC_NAME: HavokManager::tick
void HavokManager::tick() {
    // Set bit 0 of flags to indicate tick started
    m_flags |= 1;

    if ((m_flags & 2) == 0) {
        // Non-direct mode: post message to trigger Havok tick via message system
        uint32_t msgId = HashString("iMsgHavokManagerTick");
        PostMessageToQueue(&g_pMsgQueue, msgId);
        if (g_pMsgQueue != 0) {
            ProcessQueuedMessages();
        }
    } else {
        // Direct mode: manually tick Havok worlds
        // First world
        if (g_pHavokWorld1 != 0) {
            g_havokWorld1Counter++;
            void* entity = AcquireHavokEntity();
            if (entity == 0) {
                ReleaseHavokEntity(&g_pHavokWorld1, 0xb000);
            } else {
                // Increment 15-bit reference counter in entity at offset +0x14
                uint16_t counter = *(uint16_t*)((uintptr_t)entity + 0x14);
                // Bit manipulation: ((short)(counter) + 1) xor counter, masked to 0x7fff, xor counter
                // Equivalent to increment lower 15 bits ignoring overflow? Simplified:
                uint16_t newCounter = ((((uint32_t)counter * 2) >> 1) + 1 ^ counter) & 0x7fff ^ counter;
                *(uint16_t*)((uintptr_t)entity + 0x14) = newCounter;
            }
        }

        // Second world (if present)
        if (g_pHavokWorld2 != 0) {
            g_havokWorld2Counter++;
            void* entity = AcquireHavokEntity();
            if (entity == 0) {
                ReleaseHavokEntity(&g_pHavokWorld2, 0xf000);
                return;
            } else {
                uint16_t counter = *(uint16_t*)((uintptr_t)entity + 0x14);
                uint16_t newCounter = ((((uint32_t)counter * 2) >> 1) + 1 ^ counter) & 0x7fff ^ counter;
                *(uint16_t*)((uintptr_t)entity + 0x14) = newCounter;
                return;
            }
        }
    }
}
// Offsets used:
// +0x5c (this): flags (uint32)
// +0x14 (entity): ushort counter (15-bit reference)