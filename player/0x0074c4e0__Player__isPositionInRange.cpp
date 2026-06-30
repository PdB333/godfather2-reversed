// FUNC_NAME: Player::isPositionInRange
bool __thiscall Player::isPositionInRange(float* position) {
    // Check if we have a valid target (or some flag at +0x88)
    if (*(int*)(this + 0x88) != 0) {
        // Get the player's current position (likely from a global)
        void* playerData = __global_getPlayerPosition(); // FUN_00471610
        float playerX = *(float*)(playerData + 0x30);
        float playerY = *(float*)(playerData + 0x34);
        float playerZ = *(float*)(playerData + 0x38);

        // Compute distance squared? Actually uses SQRT (square root) for Euclidean distance
        float dx = position[0] - playerX;
        float dy = position[1] - playerY;
        float dz = position[2] - playerZ;
        float distSq = dx*dx + dy*dy + dz*dz;
        float dist = SQRT(distSq); // Inline sqrt call

        // Compare against a global threshold (e.g., 15.0f set in data)
        if (dist < *(float*)0x00d64704) {
            return true;
        }
    }
    return false;
}