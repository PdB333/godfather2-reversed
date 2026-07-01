// FUNC_NAME: CombatAI::evaluateAction
undefined4 __thiscall CombatAI::evaluateAction(int this, int* entity, float param3) {
    bool isAttackPossible;
    bool isApproachPossible;
    char attackFlag;
    char approachFlag;
    int target;
    undefined4 result;
    undefined4 entityPosY;
    undefined4 entityPosX;
    undefined4 targetPos1Y;
    undefined4 targetPos1X;
    undefined4 targetPos2Y;
    undefined4 targetPos2X;

    // +0x58: pointer to current target entity
    target = *(int*)(this + 0x58);

    if (entity != (int*)0x0 && !Global::isSystemEnabled() && param3 < g_fMaxActionRange) {
        // Check first condition (attack possible)
        if (((*(byte*)(entity + 0x322) & 1) == 0) ||
            (attackFlag = checkEntityFlag(entity, target), attackFlag == '\0') ||
            ((*(uint*)(entity + 0x322) >> 0x11 & 1) != 0)) {
            isAttackPossible = false;
        } else {
            isAttackPossible = true;
        }

        // Check second condition (approach possible)
        if (((*(byte*)(entity + 0x322) & 1) == 0) ||
            (approachFlag = (**(code**)(*entity + 0x29c))(target), approachFlag == '\0') ||
            ((approachFlag = FUN_007d3830(entity, target), approachFlag == '\0' ||
            ((*(uint*)(entity + 0x322) >> 0x11 & 1) != 0)))) {
            isApproachPossible = false;
        } else {
            isApproachPossible = true;
        }

        // If either condition holds, attempt action
        if (isAttackPossible || isApproachPossible) {
            updateTarget(target, entity); // FUN_00883330
            entityPosX = *(undefined4*)(target + 0x864); // +0x860: X position? Actually +0x860 and 0x864
            entityPosY = *(undefined4*)(target + 0x860);
            // vtable+0x1f0: get position of something (maybe entity's world position)
            (**(code**)(*entity + 0x1f0))(&entityPosX, &entityPosY); // note: passes address of stack var twice

            if (!isAttackPossible ||
                (attackFlag = FUN_00542f80(target, &entityPosX), attackFlag == '\0')) {
                if (!isApproachPossible) {
                    return 0;
                }
                // Use approach-specific target positions
                targetPos2X = *(undefined4*)(target + 0x1f78); // +0x1f78: approach target X?
                targetPos2Y = *(undefined4*)(target + 0x1f7c); // +0x1f7c: approach target Y?
            } else {
                // Use attack-specific target positions
                targetPos2X = *(undefined4*)(target + 0x1f70); // +0x1f70: attack target X?
                targetPos2Y = *(undefined4*)(target + 0x1f74); // +0x1f74: attack target Y?
            }

            approachFlag = performAction(entity, &entityPosX, targetPos2X, targetPos2Y);
            if (approachFlag != '\0') {
                if (attackFlag != '\0') {
                    return 0x20; // Attack action
                }
                if (isApproachPossible) {
                    return 0x10000; // Approach action
                }
            }
        } else if (((*(byte*)(entity + 0x322) & 1) == 0) &&
                   (int currentAction = FUN_007788c0(entity), currentAction != 0) &&
                   ((*(byte*)(currentAction + 0x1c0) & 1) != 0)) {
            return 4; // Special action (e.g., idle)
        }
    }
    return 0; // No action
}