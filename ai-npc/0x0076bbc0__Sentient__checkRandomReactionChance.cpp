// FUNC_NAME: Sentient::checkRandomReactionChance
bool Sentient::checkRandomReactionChance() {
    // Offset +0x8E4: bitfield of AI flags (bit 14 = e.g., "reactionDisabled")
    uint32_t flags = *(uint32_t*)(this + 0x8E4);
    if ((flags >> 0xE) & 1) {
        return false; // Reaction suppressed by flag
    }

    // Offset +0x1B8C: current AI state (4 = e.g., "incapacitated" or "unresponsive")
    uint8_t state = *(uint8_t*)(this + 0x1B8C);
    if (state == 4) {
        return false;
    }

    // Random roll: (float)rand() * g_aiRandomMultiplier < g_aiRandomThreshold
    int randVal = rand();
    float scaled = (float)randVal * DAT_00e44590; // Global probability factor
    if (DAT_00e51c7c < scaled) { // Global threshold
        return false;
    }
    return true;
}