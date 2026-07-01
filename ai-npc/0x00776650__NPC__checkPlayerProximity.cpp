// FUNC_NAME: NPC::checkPlayerProximity
uint __thiscall NPC::checkPlayerProximity(int thisPtr, int distanceThreshold)
{
    uint playerEntity;
    uint result;
    int entityTransform1;
    int entityTransform2;
    float adjustedThreshold;
    float dx;
    float dy;
    float dz;

    // Check if the "sensing enabled" flag (bit 5) is set in the state flags at +0xAC
    if ((*(uint *)(thisPtr + 0xAC) >> 5 & 1) == 0) {
        // Sensing disabled: return a value derived from another flag field (bits 13+)
        return (*(uint *)(thisPtr + 0xAC) >> 0xD) << 8;
    }

    // Get the local player entity
    playerEntity = getPlayer();
    result = playerEntity;
    if (playerEntity != 0) {
        // Check if the player is valid (e.g., alive, in game)
        result = isPlayerValid();
        if ((char)result != '\0') {
            // Ensure the player has a valid target pointer at +0x328
            if (*(int *)(playerEntity + 0x328) != 0) {
                // Convert distance threshold to float, handling negative values
                adjustedThreshold = (float)distanceThreshold;
                if (distanceThreshold < 0) {
                    adjustedThreshold = adjustedThreshold + DAT_00e44578; // Large float constant for negative handling
                }
                // Compare the NPC's detection range (+0x94) with the adjusted threshold scaled by a global factor
                if (*(float *)(thisPtr + 0x94) < adjustedThreshold * DAT_00d5efb8) {
                    // Get the current target entity (e.g., the player's target)
                    result = getCurrentTarget();
                    if (result != 0) {
                        // Get transforms of two entities (likely the player and the target)
                        entityTransform1 = getEntityTransform();
                        entityTransform2 = getEntityTransform();
                        // Compute distance between the two entities (positions at +0x30, +0x34, +0x38)
                        dy = *(float *)(entityTransform2 + 0x34) - *(float *)(entityTransform1 + 0x34);
                        dx = *(float *)(entityTransform2 + 0x30) - *(float *)(entityTransform1 + 0x30);
                        dz = *(float *)(entityTransform2 + 0x38) - *(float *)(entityTransform1 + 0x38);
                        // Compare squared distance to the player's detection radius squared (+0x34C)
                        if (dy * dy + dx * dx + dz * dz <
                            *(float *)(playerEntity + 0x34C) * *(float *)(playerEntity + 0x34C)) {
                            // Within range: return 1 in the low byte, preserving the high bytes from result
                            return (result & 0xFFFFFF00) | 1;
                        }
                    }
                }
            }
        }
    }
    // Not within range: return result with low byte cleared
    return result & 0xFFFFFF00;
}