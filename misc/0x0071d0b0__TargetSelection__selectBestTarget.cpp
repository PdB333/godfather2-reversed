// FUNC_NAME: TargetSelection::selectBestTarget
int __thiscall TargetSelection::selectBestTarget(TargetList* thisList, Player* player) {
    int bestEntity = 0;
    char bestIsImportant = '\0';
    char bestIsThreatening = '\0';
    char bestIsCurrentAim = '\0';
    int bestPriority = 0;
    float bestDistance = DAT_00d5ccf8; // global: max float
    float thresholdDist = DAT_01205228; // global: some threshold

    // Get player position
    int* playerPosPtr = getPlayerPosition(); // FUN_00471610
    float* playerPos = (float*)(playerPosPtr + 0x30); // offset to position

    // Get player's current aim state
    char currentAimState = (*(code**)(*player + 0x28c))(); // vtable call

    // Get input / controller singleton
    int* inputManager = (int*)getSingleton(DAT_01131018); // FUN_0043b870
    int* controllerManager = (int*)getSingleton(DAT_01131040); // FUN_0043b870

    // Determine controller or camera target
    int cameraTarget = 0;
    if (!(controllerManager == 0 || *(int*)(controllerManager + 0x1c) == 0 || *(int*)(controllerManager + 0x1c) == 0x48)) {
        cameraTarget = *(int*)(controllerManager + 0x24);
    }

    // Iterate over linked list of target candidates
    int* currentNode = (int*)*thisList; // head of list
    int bestCandidate = thisList->best; // offset +0x14

    while (currentNode != 0) {
        int entity = *currentNode; // entity pointer (value in node)
        int* nextNode = (int*)currentNode[1]; // next pointer

        int aimState = 0; // iStack_2c
        int* aimManager = (int*)isAimingMode(); // FUN_0071c120
        if (aimManager != 0) {
            updateAimTarget(player, cameraTarget); // FUN_0071c170
        }

        char isValid = '\0';
        if (*(int*)(entity + 8) != 0 && *(int*)(entity + 8) != 0x48) {
            isValid = validateTarget(player, entity); // FUN_0071cee0
        }

        if (aimManager == 0) goto checkEntity;

        aimState = getCurrentAimState(); // FUN_0071c150
        // Check if in combat or cutscene
        if (((aimManager[0x6e5] >> 0x17 & 1) == 0) &&
            ((controllerManager == 0 || (isCutsceneActive() == '\0')) ||
             ((*(byte*)((int)aimManager + 0x8e6) & 1) == 0))) {
            // Continue evaluation
        } else {
            // Skip this entity, but maybe clear best if same?
            int* bestPtr = &thisList->best; // offset +0x14
            if (*bestPtr == entity) {
                removeFromList(bestPtr); // FUN_004daf90
                *bestPtr = 0;
            }
            currentNode = nextNode;
            bestCandidate = bestEntity;
            continue;
        }

        if (aimState != 0) {
            // If aim state is active, skip rest? Actually break condition
            break;
        }

        // Check if entity is valid
        if (*(int*)(entity + 8) == 0) {
            currentNode = 0;
        } else {
            currentNode = (int*)(*(int*)(entity + 8) - 0x48);
        }

        int something = 0;
        char isSomething = (*(code**)(*currentNode + 0x10))(0x369ac561, &something);
        if (isSomething && something != 0 && (*(uint*)(something + 0x1f58) >> 0x19 & 1) != 0) {
            // Continue loop with updated iterator
        } else {
            goto checkEntity;
        }

checkEntity:
        if (isValid) {
            float playerPosX = *(float*)(playerPosPtr + 0x38); // +0x38
            float playerPosY = *(float*)(playerPosPtr + 0x34); // +0x34
            float playerPosZ = *(float*)(playerPosPtr + 0x30); // +0x30 was already taken
            float dx = *(float*)(playerPosPtr + 0x38) - playerPos[2];
            float dz = *(float*)(playerPosPtr + 0x30) - *playerPos;
            float dy = *(float*)(playerPosPtr + 0x34) - playerPos[1];
            float distSq = dy*dy + dx*dx + dz*dz;

            // Check if entity is in range or always targetable
            if (((*(byte*)(entity + 0x3c) >> 3 & 1) != 0) || (distSq < (float)thisList->maxDistance)) {
                bool bInRange = true;
            } else {
                continue; // skip this entity
            }

            float weightedDist = distSq; // fStack_34 after reassign? Actually there is a reassign: fStack_34 = fy*fy + fStack_34 (typo?) but likely it's distSq

            char isCurrentAim = isEntityCurrentAim(player[0x92e]); // FUN_0071c320 (param_2[0x92e] is some index)
            bool bThreatening = false;
            bool bImportant = false;

            // Check flags: vulnerable, hostile, neutral, etc.
            if ((((*(byte*)(entity + 0x3c) >> 3 & 1) != 0) || (isEntityFriendly() != '\0')) ||
                ((isEntityHostile() != '\0' && (isEntityFriendly() != '\0'))) ||
                (isEntityNeutral() != '\0')) {
                bThreatening = true;
                bImportant = true;
            }

            // Apply distance multiplier based on distance from some global
            if ((DAT_00d577a0 < *(float*)(entity + 0x2c)) &&
                ((float)((uint)(thresholdDist - *(float*)(entity + 0x2c)) & DAT_00e44680) < DAT_00d5779c)) {
                weightedDist = weightedDist * DAT_00d5ef6c;
            }

            // Additional multipliers for threatening, aiming, etc.
            if ((((*(byte*)(entity + 0x3c) >> 3 & 1) != 0) || (aimState != 0)) || (bThreatening)) {
                weightedDist = weightedDist * DAT_00d5842c;
            }

            if ((thisList->best == entity) && (isSameTargetAsPrevious() != '\0')) {
                weightedDist = weightedDist * DAT_00d5ca64;
            }

            // Check if player aim state changed
            if ((aimManager != 0) && ((*(code**)(*aimManager + 0x28c))() != currentAimState)) {
                weightedDist = weightedDist * DAT_00d5ef70;
            }

            int* someManager = getSomeManager(); // FUN_00716420
            char aimType = '\0';
            if (aimState != 0) {
                aimType = (*(code**)(*someManager + 0x10))(aimState, 0, 0); // get aim type
            }

            char isImportant = isEntityImportant(); // FUN_0071beb0

            // Get player's targeted entity
            int playerTarget = (*(code**)(*inputManager + 0x34))(); // vtable call
            if (*(int*)(playerTarget + 0xc) == 0) {
                playerTarget = 0;
            } else {
                playerTarget = *(int*)(playerTarget + 0xc) - 0x48;
            }

            int entityTarget = (*(int*)(entity + 8) == 0) ? 0 : (*(int*)(entity + 8) - 0x48);

            // If this entity is the one player is already targeting, mark as current aim
            if ((playerTarget == entityTarget) ||
                ((entity == thisList->best) && ((player[0x877] != 0 || (player[0x879] != 0))))) {
                isCurrentAim = '\x01';
            }

            // Apply penalty if not important and not current aim
            if ((isImportant == '\0') && (isCurrentAim == '\0')) {
                weightedDist = weightedDist * DAT_00d5ef70;
            }

            int priority = 0;
            if ((bImportant) || (isEntityThreatening() != '\0')) {
                priority |= 2;
            }
            if (isCurrentAim != '\0') {
                priority |= 1;
            }

            // Compare with current best
            if ((aimManager == 0) ||
                ((aimManager[0x6e5] >> 5 & 1) == 0) &&
                ((bestEntity == 0 || (bestPriority < priority)) ||
                 ((priority == bestPriority) &&
                  ((priority != 0 && (weightedDist < bestDistance)) ||
                   ((priority == 0 && isCurrentAim == '\0' && bestIsCurrentAim == '\0') &&
                    (((aimState != 0 && (getWeaponType() == 2 && aimType != '\0') && bestIsImportant == '\0') ||
                      ((isImportant != '\0' && bestIsThreatening == '\0')))) ||
                    (weightedDist < bestDistance)))))) {
                // Update best
                bestDistance = weightedDist;
                bestIsImportant = aimType;
                bestIsThreatening = isImportant;
                bestIsCurrentAim = isCurrentAim;
                bestPriority = priority;
                bestCandidate = entity;
            }

            currentNode = nextNode;
            continue;
        }

        // If not valid, free node
        clearTargetNode(&currentNode); // FUN_0071cfc0
        currentNode = nextNode;
        bestCandidate = bestEntity;
    }

    // Update list best pointer
    int* bestPtr = &thisList->best; // offset +0x14
    if (*bestPtr != bestCandidate) {
        if (*bestPtr != 0) {
            removeFromList(bestPtr); // FUN_004daf90
        }
        *bestPtr = bestCandidate;
        if (bestCandidate != 0) {
            thisList->bestNext = *(int*)(bestCandidate + 4); // offset +0x18
            *(int**)(bestCandidate + 4) = bestPtr;
        }
    }

    // Return the entity object from the best candidate
    if (*bestPtr != 0) {
        int entityFromNode = *(int*)(*bestPtr + 8);
        if (entityFromNode != 0) {
            return entityFromNode - 0x48;
        }
    }
    return 0;
}