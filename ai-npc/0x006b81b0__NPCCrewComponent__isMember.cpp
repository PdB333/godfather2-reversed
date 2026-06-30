// FUNC_NAME: NPCCrewComponent::isMember
// Address: 0x006b81b0
// This function checks if a given player ID (param_2) is one of the two crew members tracked by this component.
// param_1 points to a structure with flags and two member IDs.
// If flag bit 0 is set, the first member ID is overridden from the global player manager's current player ID.
// If flag bit 1 is set, the second member ID is overridden similarly.
// Returns true (1) if param_2 matches either member, or if both member slots are empty (0). Otherwise false (0).

#include <cstdint>

// Forward declaration of the global getter; likely returns a pointer to a player manager/singleton.
// Offset 0x188 is assumed to be the current player's ID.
uint32_t* getPlayerManager(); // FUN_0078e110 - returns pointer to player manager object

bool __thiscall NPCCrewComponent::isMember(uint32_t* thisPtr, uint32_t playerId) {
    uint32_t member1 = thisPtr[3]; // +0x0C - first crew member ID
    uint32_t member2 = thisPtr[4]; // +0x10 - second crew member ID

    // If flag bit0 (0x1) is set, override member1 from the global player manager
    if ((thisPtr[0] & 0x1) != 0) {
        uint32_t* playerMgr = getPlayerManager();
        if (playerMgr != nullptr) {
            member1 = *(uint32_t*)((uint8_t*)playerMgr + 0x188); // current player ID
        }
    }

    // If flag bit1 (0x2) is set, override member2 from the global player manager
    if ((thisPtr[0] >> 1 & 0x1) != 0) {
        uint32_t* playerMgr = getPlayerManager();
        if (playerMgr != nullptr) {
            member2 = *(uint32_t*)((uint8_t*)playerMgr + 0x188);
        }
    }

    // Check if playerId matches one of the members.
    // Returns false only if there is at least one non-zero member AND playerId is not in the set.
    // (If both are zero, any player is accepted.)
    bool hasAnyMember = (member1 != 0) || (member2 != 0);
    bool matchesMember1 = (playerId == member1);
    bool matchesMember2 = (member2 == 0) || (playerId == member2); // if member2 is 0, treat as match

    if (hasAnyMember && !matchesMember1 && !matchesMember2) {
        return false;
    }
    return true;
}