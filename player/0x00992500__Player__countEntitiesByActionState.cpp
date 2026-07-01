// FUNC_NAME: Player::countEntitiesByActionState
void Player::countEntitiesByActionState(int* entityListArray, int* countCategory1, int* countCategory2, int* countCategory3, int* countCategory4) {
    // entityListArray: [0] is pointer to array of entity pointers, [1] is count
    int* entityArray = (int*)(entityListArray[0]);
    int numEntities = entityListArray[1];

    if (numEntities == 0) {
        // Early exit if no entities
        return;
    }

    // m_bSkipCheck at this+0xD4: if non-zero, additional checks are applied
    bool playerInSpecialState = (*(int*)(this + 0xD4) != 0);

    for (int i = 0; i < numEntities; i++) {
        int* entityPtr = (int*)(entityArray[i]);

        // Determine if counting should occur for this entity
        // Counting occurs if player is NOT in special state,
        // or if playerStateCheck fails, or entity does NOT have bit0 set at +0x5F
        // i.e., skip counting only when all three conditions are met.
        bool shouldCount = true;
        if (playerInSpecialState && isPlayerInMissionMode() && ((*(byte*)(entityPtr + 0x5F) & 1) != 0)) {
            shouldCount = false;
        }

        if (shouldCount) {
            // Get entity action/state category (returns 1-5, other values ignored)
            int category = getEntityActionCategory();

            switch (category) {
                case 1:
                case 2:
                    // Categories 1 and 2 increment the same counter (param_6)
                    (*countCategory4)++;
                    break;
                case 3:
                    // Category 3 increments param_5
                    (*countCategory3)++;
                    break;
                case 4:
                    // Category 4 increments param_4
                    (*countCategory2)++;
                    break;
                case 5:
                    // Category 5 increments param_3
                    (*countCategory1)++;
                    break;
                default:
                    // Unknown category, ignore
                    break;
            }
        }
    }
}