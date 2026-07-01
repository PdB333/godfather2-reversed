// FUNC_NAME: CombatPerception::evaluateTarget
int __thiscall CombatPerception::evaluateTarget(int this, int target)
{
    int result = 0;

    if (target == 0) {
        // No target: check own status
        // this+0x58 likely points to a character or AI state structure
        // +0x8e8: bit 2 check – maybe "isInCombat" or "isAggressive"
        if ((*(uint *)(*(int *)(this + 0x58) + 0x8e8) >> 2 & 1) == 0) {
            int statePtr = *(int *)(*(int *)(this + 0x58) + 0x74c);
            // statePtr might be an animation state or behavior state pointer
            // 0x48 could be an enum value (e.g., kStateIdle, kStatePursuing, etc.)
            if (statePtr != 0 && statePtr != 0x48) {
                // +0x188: bit 2 check – maybe "canUseWeapon" or "hasTarget"
                // +0x165: byte compared to 0x19 (25) – possibly a subtype or animation ID
                if ((*(uint *)(statePtr + 0x188) >> 2 & 1) != 0 && *(char *)(statePtr + 0x165) != '\x19') {
                    // Check if a specific action (key 10, e.g., "attack") is pressed
                    char isPressed = FUN_007aefe0(10); // isActionKeyPressed(10)
                    if (isPressed != '\0') {
                        result = 1;
                    }
                }
            }
        }
    } else {
        // Target exists: evaluate target's state
        // +0x1a4: bit 2 check – probably "isVulnerable" or "canBeTargeted"
        if ((*(uint *)(target + 0x1a4) >> 2 & 1) == 0) {
            // +0x1a8: maybe a counter or flag (0 = new, non-zero = existing)
            // Return 2 if target is "new", 3 if "existing"
            return 3 - (uint)(*(int *)(target + 0x1a8) != 0);
        }
    }
    return result;
}