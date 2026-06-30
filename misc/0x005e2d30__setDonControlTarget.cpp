// FUNC_NAME: setDonControlTarget
bool setDonControlTarget(uint param_1, void* targetEntity) {
    // Global pointer to DonControlManager or similar state (0x122350c)
    // Byte at +0x1744 indicates whether don control mode is active
    if (*(char*)(DAT_0122350c + 0x1744) != 0) {
        // Get the currently controlled object (e.g., player's crew leader)
        void* controlledObject = getControlledEntity(); // FUN_005e2150
        if (controlledObject != nullptr) {
            // Set target at offset +0x24c (likely a pointer to entity or action)
            *(uint*)((char*)controlledObject + 0x24c) = (uint)targetEntity;
            return true;
        }
    }
    return false;
}