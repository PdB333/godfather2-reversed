// FUNC_NAME: PlayerSM::handleAction
void __thiscall PlayerSM::handleAction(intptr_t self, const ActionInput* actionInput)
{
    // self is offset by 0x394 from the actual Player object base
    // vtable is at the base
    int* vtable = reinterpret_cast<int*>(self - 0x394);
    
    // Clear some animation state
    *reinterpret_cast<uint8_t*>(self + 0x1b31) = 0xFF; // animation state index
    *reinterpret_cast<int*>(self + 0x1b38) = 5;        // animation speed flag?

    // Clear the "playing animation" flag (bit 6 of +0x558)
    if ((*reinterpret_cast<uint32_t*>(self + 0x558) >> 6) & 1) {
        (reinterpret_cast<void(__thiscall*)(int)>(vtable[0x28]))(0x20); // stop animation?
    }
    *reinterpret_cast<uint32_t*>(self + 0x558) &= ~0x40;

    uint32_t globalParam = DAT_01205224; // some global context

    // If action type is 1 (interact), play a sound
    if (actionInput->actionType == 1) {
        FUN_007f94c0(actionInput->entity, globalParam);
    }

    float currentTime = FUN_007f9450(globalParam); // get game time
    // Check if it's time for an interaction timeout and something else
    if ( (currentTime >= *reinterpret_cast<float*>(self + 0x19dc)) &&
         (*reinterpret_cast<char*>(self + 0x17f8) == '\0') &&
         (actionInput->actionType == 1) ) {
        vtable[0x1e4](); // call virtual function (interact?)
        *reinterpret_cast<uint32_t*>(self + 0x1800) |= 2; // set bit 1
    }

    // Process action based on target entity
    if (actionInput->entity != nullptr && actionInput->entity != 0x48) {
        // entity is offset by -0x48 from its base? This implies an Entity structure.
        int* targetEntity = reinterpret_cast<int*>(actionInput->entity - 0x48);
        int targetActionType = 0;
        char canInteract = (reinterpret_cast<char(__thiscall*)(int, int*)>(targetEntity[4]))(0x55859efa, &targetActionType);
        if (canInteract && targetActionType != 0) {
            switch (actionInput->actionType) {
            case 1: // Interact / Pickup
                FUN_007fff40(targetActionType + 0x1cd8); // set animation?
                FUN_008d8100(targetActionType, vtable); // set interaction state
                int currentPlayer = FUN_007fd760(); // get current player
                if ((reinterpret_cast<int*>(self - 0x394) != reinterpret_cast<int*>(currentPlayer)) ||
                    (FUN_007f7b90() == '\0')) {
                    // not the local player or not a player
                    int canDoAction = FUN_006bc8d0(targetActionType, 0x369ac561);
                    if ((canDoAction == 0) || (FUN_0072d630() == '\0')) {
                        // normal pickup
                        beginDialogue(0, 0);
                        playDialogue(0x20eb8823, 0, beginDialogue(0, 0), 0);
                    } else {
                        // alternate pickup
                        beginDialogue(0, 0);
                        playDialogue(0xd732272a, 0, beginDialogue(0, 0), 0);
                    }
                    endDialogueContext();
                }
                // Copy animation state from target
                *reinterpret_cast<uint8_t*>(self + 0x1b31) = *reinterpret_cast<uint8_t*>(targetActionType + 0x1ec4);
                int animSpeed = FUN_007f98e0();
                *reinterpret_cast<int*>(self + 0x1b38) = animSpeed;
                int localPlayer = FUN_00716c30(); // get local player
                if (localPlayer == reinterpret_cast<intptr_t>(self - 0x394)) {
                    FUN_007f63e0(0x66); // play sound effect 0x66
                }
                break;

            case 2: // Cover related?
            case 4:
            case 5:
            case 6:
            case 7:
            case 0xB:
                // Check if we already have an interaction target
                if (*reinterpret_cast<int*>(self + 0x1b44) != 0) {
                    int currentInteraction = *reinterpret_cast<int*>(self + 0x1b44) - 0x48;
                    int hasComponent = FUN_006c9470(currentInteraction, 0x383225a1);
                    if (hasComponent != 0) {
                        // Already interacting with something
                        int canSwap = FUN_006c9470(vtable, 0x383225a1);
                        if (canSwap == 0) {
                            if (*reinterpret_cast<int*>(self + 0x1b40) == 0x637b907) break;
                            int something = FUN_00806440(1);
                            FUN_008d8010(*(int*)(targetActionType + 0x1ed4), something, 1);
                        } else {
                            int something = FUN_00806440(1);
                            FUN_008d7d90(*(int*)(targetActionType + 0x1ed4), something, 1);
                        }
                    } else {
                        int something = FUN_00806440(1);
                        FUN_008d7d90(*(int*)(targetActionType + 0x1ed4), something, 1);
                    }
                } else {
                    // No current interaction, so start one
                    int canInteract = FUN_006c9470(vtable, 0x383225a1);
                    if (canInteract == 0) {
                        if (*reinterpret_cast<int*>(self + 0x1b40) == 0x637b907) break;
                        int something = FUN_00806440(1);
                        FUN_008d8010(*(int*)(targetActionType + 0x1ed4), something, 1);
                    } else {
                        int something = FUN_00806440(1);
                        FUN_008d7d90(*(int*)(targetActionType + 0x1ed4), something, 1);
                    }
                }
                break;

            case 3: // Move to action?
                FUN_008d8100(targetActionType, vtable);
                break;
            }
        }
    }

    int actionType = actionInput->actionType;
    // Handle movement/cover for specific action types
    if ( (actionType == 6 || actionType == 7 || actionType == 5) &&
         ((*reinterpret_cast<uint32_t*>(self + 0x554) >> 0x13) & 1) == 0 ) {
        int context = beginDialogue(0, 0);
        if ( (*reinterpret_cast<int*>(self + 0x4ac) != 0) &&
             (FUN_007f7b90() == '\0') &&
             ((*reinterpret_cast<uint32_t*>(self + 0x550) >> 10) & 1) == 0 ) {
            playDialogue(0x95750bca, 0, context, 0);
        }
        endDialogueContext();
    }

    // Check cover-related thresholds
    float someValue = (reinterpret_cast<float(__thiscall*)(int)>(*(int*)(*reinterpret_cast<int*>(self + 0x260)) + 0x30))();
    float thresholdHigh = *reinterpret_cast<float*>(self + 0x19f0);
    float thresholdLow = *reinterpret_cast<float*>(self + 0x19ec);
    if (someValue < thresholdHigh) {
        if ( (someValue < thresholdLow) &&
             ((*reinterpret_cast<uint32_t*>(self + 0x550) >> 0x0D) & 1) == 0 &&
             ( ((*reinterpret_cast<uint32_t*>(self + 0x54C) >> 0x0B) & 1) == 0 ||
               ((*reinterpret_cast<uint32_t*>(self + 0x54C) >> 0x0F) & 1) != 0 ) ) {
            // Enter cover mode
            *reinterpret_cast<uint32_t*>(self + 0x1800) |= 0x18;
            *reinterpret_cast<uint32_t*>(self + 0x1800) &= ~2;
            FUN_007fff40(self + 0x193c); // set animation?
        }
    } else {
        if ( ((*reinterpret_cast<uint32_t*>(self + 0x550) >> 0x0D) & 1) == 0 &&
             ( ((*reinterpret_cast<uint32_t*>(self + 0x54C) >> 0x0B) & 1) == 0 ||
               ((*reinterpret_cast<uint32_t*>(self + 0x54C) >> 0x0F) & 1) != 0 ) ) {
            *reinterpret_cast<uint32_t*>(self + 0x1800) |= 4; // toggle cover exit flag?
        }
    }

    // More cover/action logic based on action type flags
    uint32_t flags = FUN_0084d420(actionInput->actionType);
    if ((flags & 8) == 0 || *reinterpret_cast<int*>(self + 0x1adc) != 0) {
        if ((flags & 0x40) == 0 ||
            (*reinterpret_cast<int*>(self + 0x1adc) != 0 || *reinterpret_cast<int*>(self + 0x1af0) != 0)) {
            // Check negative flag
            char negativeFlag = static_cast<char>(flags); // sign bit?
            if (negativeFlag < 0 &&
                ((*reinterpret_cast<uint32_t*>(self + 0x554) >> 0x16) & 1) == 0 &&
                _DAT_00d577a0 < actionInput->someFloat) {
                int canDo = FUN_006bc8d0(vtable, 0x369ac561);
                if (canDo != 0) {
                    beginDialogue(0, 0);
                    playDialogue(0x95750bca, 1, beginDialogue(0, 0), 0);
                    endDialogueContext();
                }
                FUN_007faa10(); // play rejection sound?
            }
        } else {
            // Cover interaction with distance check
            int localPlayer = FUN_00471610(); // get local player
            float dx = actionInput->x - *reinterpret_cast<float*>(localPlayer + 0x30);
            float dy = actionInput->y - *reinterpret_cast<float*>(localPlayer + 0x34);
            float dz = actionInput->z - *reinterpret_cast<float*>(localPlayer + 0x38);
            float dist = sqrt(dx*dx + dy*dy + dz*dz);
            if (dist < 0.0f) dist = 0.0f;
            float thresholdDist = *reinterpret_cast<float*>(self + 0x1998);
            if (dist <= thresholdDist && actionInput->someFloat > 0.0f) {
                if (FUN_00414d50() == '\0') { // not already in cover
                    if (*reinterpret_cast<int*>(self + 0x1af0) != 0) {
                        FUN_004df590(); // exit previous cover?
                    }
                    int result = (reinterpret_cast<int(__thiscall*)(int, int, int, int)>(vtable[0x58]))(0, vtable, 0, 0);
                    result = FUN_00471610(result);
                    int coverData;
                    FUN_004df330(&coverData, self + 0x1ae0, result);
                    FUN_00414db0(&coverData);
                    FUN_00414df0(); // enter cover
                }
            }
        }
    } else {
        // Alternative cover branch with different distance
        int localPlayer = FUN_00471610();
        float dx = actionInput->x - *reinterpret_cast<float*>(localPlayer + 0x30);
        float dy = actionInput->y - *reinterpret_cast<float*>(localPlayer + 0x34);
        float dz = actionInput->z - *reinterpret_cast<float*>(localPlayer + 0x38);
        float dist = sqrt(dx*dx + dy*dy + dz*dz);
        if (dist < 0.0f) dist = 0.0f;
        float thresholdDist2 = *reinterpret_cast<float*>(self + 0x1990);
        if (dist <= thresholdDist2 && actionInput->someFloat > 0.0f && FUN_00414d50() == '\0') {
            FUN_008064b0(); // initiate cover?
            int coverComponent = FUN_006bc8b0(vtable);
            if (coverComponent != 0 && FUN_006eb940() != '\0' &&
                (reinterpret_cast<char(__thiscall*)(int)>(*(int*)coverComponent + 0x1c))(0x100) != '\0') {
                int spawnBase = (self == 0x394) ? 0 : (self - 0x358);
                FUN_00440590(&DAT_0112c82c, spawnBase, DAT_00d5eee4, 0, 4); // spawn cover object?
            }
            if (FUN_00481660() != '\0' || FUN_00481640() != '\0') {
                int spawnBase2 = (self == 0x394) ? 0 : (self - 0x358);
                FUN_00440590(&DAT_0112c82c, spawnBase2, DAT_00d71b10, 0, 4);
            }
        }
    }

    // Handle cover state updates
    if (*reinterpret_cast<int*>(self + 0x1b5c) != 0 &&
        ( *reinterpret_cast<char*>(self + 0xc94) == '\0' ||
          *reinterpret_cast<char*>(self + 0xc84) != '\x02' ||
          ( ((*reinterpret_cast<uint32_t*>(self + 0x550) >> 2) & 1) == 0 &&
            (int state = *reinterpret_cast<int*>(self + 0xc7c);
             state != 0x2C && state != 0x2D && state != 0x2E) ) ) ) {
        int targetEntityBase = (actionInput->entity == 0) ? 0 : (actionInput->entity - 0x48);
        FUN_006ada80(targetEntityBase, *reinterpret_cast<int*>(self + 0x1b5c)); // set cover target?
        int localPlayer = FUN_00471610();
        struct TransformSave {
            uint32_t magic;
            void* data;
            uint8_t flag;
        } transform;
        transform.magic = DAT_0112ad8c;
        transform.data = reinterpret_cast<void*>(self + 0x1ae0);
        transform.flag = 1;
        // Prepare transform from player position
        memcpy(&transform.data, reinterpret_cast<void*>(localPlayer + 0x30), sizeof(float)*3); // copy position
        FUN_00408a00(&transform, 0);
        if (*(int*)&transform.magic != 0) {
            FUN_004daf90(*(int*)&transform.magic); // release transform?
        }
    }
}