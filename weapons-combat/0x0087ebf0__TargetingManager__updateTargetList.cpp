//FUNC_NAME: TargetingManager::updateTargetList
void TargetingManager::updateTargetList() {
    // Stack variables
    float playerPos[3]; // local_230, fStack_22c, fStack_228
    float gameTime; // local_23c
    float viewDir[3]; // local_24c, local_248, local_244 (scaled)
    float dotProduct; // local_250
    float distance; // fStack_240
    float candidateDistance; // fStack_234
    int candidateEntity; // iStack_238
    int candidateCount = 0; // local_18
    // Array of 64 pairs (entity pointer, float distance) stored as int[128]
    int candidateArray[128]; // local_218

    // Get player position (likely from player object)
    getPlayerPosition(&playerPos[0], 0); // FUN_00424fb0
    gameTime = (float)getGameTime(0); // FUN_00425130
    // Get camera forward vector and scale by global constant
    getCameraTransform(&viewDir[0], 0); // FUN_00425060
    transformVector(&viewDir[0], viewDir[0], viewDir[1], viewDir[2]); // FUN_004a2540
    viewDir[0] *= DAT_00d5ccf8; // scale factor
    viewDir[1] *= DAT_00d5ccf8;
    viewDir[2] *= DAT_00d5ccf8;

    // Clear candidate array
    for (int i = 0; i < 64; i++) {
        candidateArray[i * 2] = 0;
        candidateArray[i * 2 + 1] = 0;
    }
    candidateCount = 0;

    // Get entity list (linked list of entity pointers)
    int* entityListHead = *(int**)FUN_0043c2c0(4); // returns pointer to list head
    for (int* node = entityListHead; node != nullptr; node = (int*)node[1]) {
        int entity = node[0]; // entity pointer
        uint flags = *(uint*)(entity + 0xc88); // flags at offset +0xC88

        // Check if entity is a valid target: bit19 (alive?) and bit9 (dead?)
        bool isAlive = (flags >> 0x13) & 1; // bit 19
        bool isDead = (flags >> 9) & 1;     // bit 9
        if (!isAlive || isDead) {
            // Entity is not a valid target (dead or inactive)
            if (!((flags >> 2) & 1) && isPlayerInCombat(0)) { // FUN_00424f20
                // Compute distance from player
                int player = getPlayer(); // FUN_00471610
                float dx = *(float*)(player + 0x34) - viewDir[2]; // note: order might be different
                float dy = *(float*)(player + 0x38) - viewDir[1];
                float dz = *(float*)(player + 0x30) - viewDir[0];
                distance = sqrt(dx*dx + dy*dy + dz*dz);
                if (DAT_00e44598 < distance) {
                    // Dot product with scaled view direction
                    dotProduct = viewDir[1] * dx + viewDir[0] * dz + viewDir[2] * dy;
                    double threshold = (double)(gameTime * DAT_00e44880);
                    debugDraw(); // FUN_00b99e20
                    if (((float)threshold - DAT_00e4475c) * distance < dotProduct) {
                        // Add to candidate list
                        candidateDistance = distance;
                        candidateEntity = entity;
                        addCandidate(&candidateEntity); // FUN_00875f70
                        // Store in array
                        candidateArray[candidateCount * 2] = candidateEntity;
                        candidateArray[candidateCount * 2 + 1] = *(int*)&candidateDistance; // store float as int
                        candidateCount++;
                    }
                }
            }
            else if ((flags | 0x40000) != flags) {
                // Set flag 0x40000 (mark as not targetable)
                (**(code**)(*(int*)(entity + 0x58) + 0x28))(0x10); // some method call
                *(uint*)(entity + 0xc88) |= 0x40000;
            }
        }
        else if ((flags & 0xfffbffff) != flags) {
            // Entity is valid but has flag set -> clear it
            (**(code**)(*(int*)(entity + 0x58) + 0x28))(0x10);
            *(uint*)(entity + 0xc88) &= 0xfffbffff;
        }
    }

    // Sort candidates by distance (or score)
    sortCandidates(candidateArray, candidateArray + candidateCount * 2,
                   (candidateArray + candidateCount * 2 - candidateArray) >> 3, dotProduct); // FUN_0087eae0

    // Update flag 0x40000 for top 4 candidates
    for (uint i = 0; i < candidateCount; i++) {
        int entity = candidateArray[i * 2];
        uint flags = *(uint*)(entity + 0xc88);
        if (i < 4) {
            if ((flags | 0x40000) != flags) {
                (**(code**)(*(int*)(entity + 0x58) + 0x28))(0x10);
                *(uint*)(entity + 0xc88) |= 0x40000;
            }
        }
        else {
            if ((flags & 0xfffbffff) != flags) {
                (**(code**)(*(int*)(entity + 0x58) + 0x28))(0x10);
                *(uint*)(entity + 0xc88) &= 0xfffbffff;
            }
        }
    }
}