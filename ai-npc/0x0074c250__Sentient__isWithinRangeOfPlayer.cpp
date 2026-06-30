// FUNC_NAME: Sentient::isWithinRangeOfPlayer
bool Sentient::isWithinRangeOfPlayer(Vector3* targetPos) {
    // Check if this sentient is valid and the game is active
    if (this != nullptr && 
        FUN_00800ad0() != 0 && 
        (*(uint32_t*)((uint8_t*)this + 0x8e0) >> 10 & 1) != 0) {
        
        // Get the player's position (or some reference object)
        void* playerObj = FUN_00471610(); // returns pointer to player object
        if (playerObj != nullptr) {
            float distance = FUN_0084cb90(targetPos, (float*)((uint8_t*)playerObj + 0x30), 
                                          (float*)((uint8_t*)this + 0x8f0), 0, 1);
            if (distance < g_playerReachDistance) {  // _DAT_00e51940
                return true;
            }
        }
    }
    return false;
}