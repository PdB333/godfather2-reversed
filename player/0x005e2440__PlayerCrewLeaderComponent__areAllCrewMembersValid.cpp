// FUNC_NAME: PlayerCrewLeaderComponent::areAllCrewMembersValid
bool PlayerCrewLeaderComponent::areAllCrewMembersValid(int contextId) {
    bool anyFailed = false;
    // +0x1744: flag indicating crew is active (e.g., out on a mission)
    if (*(char*)(this + 0x1744) != 0) {
        // +0x490: base of an array of 5 crew member slots, each 0x129 bytes
        char* slot = (char*)(this + 0x490);
        for (int i = 0; i < 5; i++) {
            // First 4 bytes of each slot: non-zero if slot is occupied
            if (*(int*)slot != 0) {
                char result = isCrewMemberSatisfied(contextId); // FUN_005e2040
                if (result == 0) {
                    anyFailed = true;
                }
            }
            slot += 0x129; // advance to next slot (0x129 bytes)
        }
    }
    // Return true only if all occupied slots passed the check
    return !anyFailed;
}