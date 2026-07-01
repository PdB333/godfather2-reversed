// FUNC_NAME: PlayerController::updateTargetSelection
void __fastcall PlayerController::updateTargetSelection(PlayerController* this) {
    // +0x58: pointer to some player state/character data (e.g., t2Game::PlayerData*)
    PlayerData* playerData = *(PlayerData**)(this + 0x58);
    
    // Check if game is paused (e.g., during menus or cutscenes)
    if (IsGamePaused()) {
        return;
    }
    
    // Get the main controller/manager singleton (e.g., ControllerManager*)
    ControllerManager* controllerMgr = (ControllerManager*)GetControllerManager();
    if (controllerMgr->flags & 2) { // +0x04: bit 2 = disabled/override flag
        return;
    }
    
    int targetHandle = 0;
    if (!IsInCombatMode()) {
        // Simple direct target lookup (e.g., nearest enemy via game query)
        targetHandle = FindClosestTarget(*(int*)(this + 0x58), DAT_00d5f52c, DAT_00d6f97c);
    }
    else {
        // Combat mode: find the nearest valid target from active enemies list
        if (((*(uint*)(playerData + 0x1ee0) >> 6) & 1) == 0) goto cleanup;
        int targetId = *(int*)(playerData + 0x1ef4);
        if (targetId == -1) goto cleanup;
        
        float minDistSq = DAT_00d5ccf8; // Large initial distance (e.g., 1e20)
        Vector3* playerPos = GetPlayerPosition(); // Player's current position
        EntityList* entityList = (EntityList*)DAT_012233a0; // Global entity list manager
        int numEntities = GetNumActiveEntities();
        
        for (int i = 0; i < numEntities; i++) {
            Entity* entity = *(Entity**)(*(int*)(entityList + 4) + i * 4);
            if (entity == nullptr) continue;
            
            // Offset -0x1f30: some base class/data offset (e.g., to Sentient base)
            Sentient* sentient = (Sentient*)(entity - 0x1f30); // pointer arithmetic
            if (sentient == nullptr) continue;
            
            // Check if entity's target ID matches current target
            if (*(int*)(entity - 0x3c) == targetId) {
                // Check flags and line-of-sight/target validity
                if (CheckFlag(0x17) && IsValidTarget(playerData, sentient, DAT_00d5f52c, DAT_00d6f97c)) {
                    Vector3 entityPos = GetEntityPosition(entity);
                    float dx = playerPos->x - entityPos.x;
                    float dy = playerPos->y - entityPos.y;
                    float dz = playerPos->z - entityPos.z;
                    float distSq = dx*dx + dy*dy + dz*dz;
                    
                    if (distSq < minDistSq || minDistSq == DAT_00d5ccf8) {
                        minDistSq = distSq;
                        targetHandle = (int)sentient;
                    }
                }
            }
        }
    }
    
    if (targetHandle != 0) {
        SetTargetEntity(targetHandle);
        // Call vtable function at index 1 (offset 4) – likely "engage target" or "acquire"
        (*(void (__thiscall**)(ControllerManager*, int))(*(int*)controllerMgr + 4))(controllerMgr, 2);
        return;
    }
    
cleanup:
    // If target not found, release previous target handle (if any)
    // +0x134 (0x4d * 4): offset to cached target handle
    if (controllerMgr->cachedTarget != 0) {
        ReleaseTarget(controllerMgr + 0x4d);
        controllerMgr->cachedTarget = 0;
    }
}