// FUNC_NAME: getGameStateFlag
uint8_t getGameStateFlag(void)
{
    // Returns a global byte flag at address 0x00f15a39
    // Likely indicates some game state (e.g., paused, mission active, etc.)
    return DAT_00f15a39;
}