// FUNC_NAME: PendingActionManager::ProcessPendingActions
void __thiscall PendingActionManager::ProcessPendingActions(void)
{
    int* pNode; // eax
    float clampMin; // fVar3

    clampMin = g_fGlobalMinTime; // DAT_00e2b04c - minimal timer value
    pNode = this->m_pPendingListHead; // +0x11C (offset 0x47 * 4)

    while (pNode != NULL) {
        PendingNode* currentNode = reinterpret_cast<PendingNode*>(this->m_pPendingListHead); // +0x11C

        // Save global (unnecessary, but decompiler shows)
        g_fGlobalMinTime = clampMin;

        // Advance list head to next node (stored at +0x10 in node)
        this->m_pPendingListHead = reinterpret_cast<int*>(currentNode->pNext); // node+0x10

        // If node's first byte != 0, set a "has active item" flag
        if (currentNode->firstByte != 0) {
            *reinterpret_cast<byte*>(reinterpret_cast<uint>(this) + 0x3d) = 1; // flag at +0x3D
        }

        // Check if timer update mode is active (bits 2 & 3 at +0x2E)
        if ((*reinterpret_cast<byte*>(reinterpret_cast<uint>(this) + 0x2e) & 0xC) != 0) {
            // Scale cooldown value at +0x6F (float conversion)
            float scaledCooldown = static_cast<float>(this->m_cooldown) * g_fCooldownScale; // DAT_00e2cd54
            if (scaledCooldown < clampMin) {
                scaledCooldown = clampMin;
            }
            this->m_cooldown = static_cast<int>(scaledCooldown);

            // Decrement timer at +0x6E
            float newTimer = static_cast<float>(this->m_timer) - g_fTimerDecrement; // DAT_00e2b1a4
            this->m_timer = static_cast<int>(newTimer);
            if (newTimer < clampMin) {
                this->m_timer = static_cast<int>(clampMin);
            }
        }

        // Call virtual handler on this with the node as argument (vtable slot 0x40)
        (this->vtable->processNode)(currentNode); // vtable+0x40

        // Deallocate the node (likely memory manager call)
        DeallocNode(currentNode); // FUN_009c8eb0

        // Reload globals for next iteration
        clampMin = g_fGlobalMinTime;
        pNode = this->m_pPendingListHead; // +0x11C
    }

    // Store back (debug / global tracking)
    g_fGlobalMinTime = clampMin;
}