// FUNC_NAME: NPCManager::areAllNPCsReady

int __fastcall NPCManager::areAllNPCsReady(NPCManager* this)
{
    float fTimer = *(float*)((char*)this + 0x164); // +0x164: m_fTimer or m_fCheckValue
    float fGlobal = _DAT_00d577a0; // global constant (e.g., -1.0f or 0.0f)

    if (fTimer != fGlobal) {
        // Return a bitmask encoding comparison result (less, equal, NaN flags)
        // This path is taken when the timer hasn't reached the global value
        return (uint)CONCAT21((short)((uint)in_EAX >> 0x10),
                              (fTimer == fGlobal) << 6 | (NAN(fTimer) || NAN(fGlobal)) << 2 |
                              2U | fTimer < fGlobal) << 8;
    }

    // Timer matches global value; check all NPCs in the list
    uint count = *(uint*)((char*)this + 0x98); // +0x98: m_nNPCListCount
    if (count != 0) {
        int** ppList = *(int***)((char*)this + 0x94); // +0x94: m_ppNPCList (array of pointers)
        for (uint i = 0; i < count; i++) {
            int* pNPC = ppList[i * 2]; // Each entry is 8 bytes? Actually ppList + 2*i
            // Check if NPC pointer is valid and not a special sentinel (0x48)
            if (pNPC != nullptr && pNPC != (int*)0x48) {
                // Check NPC state at offset 0xee4 (e.g., m_bIsReady or m_bActive)
                if (*(int*)((char*)pNPC + 0xee4) != 1) {
                    return 0; // Not all ready
                }
            }
        }
    }
    return 1; // All NPCs are ready
}