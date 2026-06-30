// FUN_005e2440: PlayerCrewComponent::areAllCrewMembersReady
// Checks if all active crew members are ready (not busy, available)
// this is passed as first argument (param_1) due to static-style calling convention
// Offsets:
//   +0x1744: m_bCrewActive (bool)
//   +0x490 : m_aCrewSlotData[5] – array of 5 slot structures, each 0x4A4 bytes
//            first word of each slot is m_pCrewMember (0 if empty)
// Called from: 0x005e1e50, 0x005e1ee0, 0x005e2be0

bool PlayerCrewComponent::areAllCrewMembersReady(PlayerCrewComponent* this)
{
    bool allReady = false;
    bool anyNotReady = false;

    // Only check if crew is enabled
    if (*(char*)((char*)this + 0x1744) != 0) // m_bCrewActive
    {
        int* slotBase = (int*)((char*)this + 0x490); // m_aCrewSlotData
        for (int i = 0; i < 5; ++i)
        {
            if (*slotBase != 0) // slot occupied (m_pCrewMember != null)
            {
                // Call static helper: checks global crew readiness conditions
                // (e.g., no combat, not in dialog, player alive)
                char result = FUN_005e2040(this); // returns 1 if ready, 0 if not
                if (result == 0)
                {
                    anyNotReady = true;
                }
            }
            slotBase += 0x129; // advance to next slot (0x4A4 bytes)
        }
        allReady = !anyNotReady;
    }
    return allReady;
}