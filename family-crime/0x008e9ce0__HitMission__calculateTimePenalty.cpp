// FUNC_NAME: HitMission::calculateTimePenalty
// Function address: 0x008e9ce0
// Role: Determines the time-based penalty for a hit mission, returning an integer score adjustment
int HitMission::calculateTimePenalty() {
    // Check if the mission is active (flag at offset 0x40 in the mission data structure)
    if (!(*(uint8_t*)(*(int*)(this + 8) + 0x40) & 1)) {
        return -999999; // Invalid / inactive mission
    }

    int penalty = 0; // Base penalty
    // Get a manager object (e.g., MissionManager) and add offset 0x30 for some sub-object
    int managerBase = FUN_00471610(); // Returns a singleton or global handle
    int managerSub = managerBase + 0x30; // Sub-object offset
    if (FUN_006c0050(managerSub, 0, 0)) { // Check condition (e.g., time window expired?)
        penalty = -500;
    }

    // Get a float value from the manager (e.g., elapsed time or distance)
    float currentValue = FUN_006bfff0(managerSub);
    float maxThreshold = DAT_00d62bd4; // Global time/distance limit for full reward
    if (maxThreshold < currentValue) {
        // Exceeded threshold: use the max threshold as the penalty basis
        return penalty - (int)maxThreshold;
    } else {
        // Within threshold: use the actual value
        return penalty - (int)currentValue;
    }
}