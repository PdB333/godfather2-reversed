// FUNC_NAME: PlayerActionableTargetSM::getInteractionAction
int __thiscall PlayerActionableTargetSM::getInteractionAction(int thisPtr, int message, int* outTarget) {
    uint msgHash;
    char tempChar;
    int entityId;
    int ownerId;
    int* component;
    bool isSpecificHash;
    
    // Extract target entity from message (+8 points to some member, subtract 0x48 to get base)
    if (*(int*)(message + 8) == 0) {
        entityId = 0;
    } else {
        entityId = *(int*)(message + 8) - 0x48;
    }
    
    // If target is same as current selection, ignore
    if (entityId == *(int*)(thisPtr + 0x28)) {
        return -1;
    }
    
    msgHash = *(uint*)(message + 4);
    
    // Large hash-based dispatch for interaction types
    if (0x7c9a0ecd < msgHash) {
        if (msgHash < 0xc7dc3516) {
            // Hashes: 0xc7dc3515, 0x8b284db6, 0xa2741529 -> invalid
            // 0xb6988728 -> conditional return
            if (((msgHash != 0xc7dc3515) && (msgHash != 0x8b284db6)) && (msgHash != 0xa2741529)) {
                isSpecificHash = msgHash == 0xb6988728;
                goto LAB_0078303d;
            }
        } else {
            // Hashes: 0xde578cc7, 0xf4846c64 -> return 0x15 if flag set
            if ((msgHash != 0xde578cc7) && (msgHash != 0xf4846c64)) {
                if (msgHash != 0xf7b11ea8) {
                    return -1;
                }
                // Handle "use" or "interact" message (0xf7b11ea8)
                if (*outTarget == 0) {
                    return 8;
                }
                // Get component from target (hash 0x55859efa = "Entity"?)
                entityId = getComponent(*outTarget, 0x55859efa);
                if (entityId == 0) {
                    return 8;
                }
                // Get owner via vtable+0x34
                component = (int*)getOwner(entityId);
                ownerId = (**(code**)(*component + 0x34))();
                if (*(int*)(ownerId + 0xc) == 0) {
                    ownerId = 0;
                } else {
                    ownerId = *(int*)(ownerId + 0xc) - 0x48;
                }
                *outTarget = ownerId;
                
                ownerId = (**(code**)(*component + 0x34))();
                if (*(int*)(ownerId + 0x30) == 3) {
                    // Owner is a specific type (e.g., player-controlled)
                    entityId = getComponent(entityId, 0x369ac561);
                    if ((entityId != 0) && ((*(byte*)(entityId + 0x1f54) & 1) != 0)) {
                        return 0x10; // 16
                    }
                    return 0xf; // 15
                }
                // Check game mode
                int gameMode = getGameMode();
                if (gameMode == 2) {
                    return 10;
                }
                if (gameMode == 3) {
                    return 9;
                }
                entityId = getComponent(entityId, 0x369ac561);
                if (entityId == 0) {
                    return 8;
                }
                if ((*(byte*)(entityId + 0x1f54) & 1) == 0) {
                    return 8;
                }
                return 0xb; // 11
            }
            // For 0xde578cc7 and 0xf4846c64: check flag
            if ((*(uint*)(thisPtr + 0x74) >> 1 & 1) == 0) {
                return -1;
            }
            return 0x15; // 21
        }
    } else if (msgHash == 0x7c9a0ecd) {
        // Handle "don control" or "family" message
        if ((*(uint*)(thisPtr + 0x74) >> 1 & 1) == 0) {
            return -1;
        }
        if (*outTarget == 0) {
            return -1;
        }
        // Get component with hash 0xa5975eb2 (e.g., "DonControlComponent")
        component = (int*)getComponent(*outTarget, 0xa5975eb2);
        if (component == (int*)0x0) {
            return -1;
        }
        // Call vtable+0x1e4 to get the don control entity
        *outTarget = (**(code**)(*component + 0x1e4))();
        return 0x15; // 21
    } else if (0x2fd81222 < msgHash) {
        if (msgHash == 0x736760b2) {
            return 0;
        }
        isSpecificHash = msgHash == 0x7b35500e;
LAB_0078303d:
        if (!isSpecificHash) {
            return -1;
        }
        // For 0x7b35500e: return 4 or 21 based on flag
        return (-(uint)((*(uint*)(thisPtr + 0x74) >> 1 & 1) != 0) & 0x11) + 4;
    } else {
        if (msgHash != 0x2fd81222) {
            if (msgHash == 0x1970c04) {
                return 2;
            }
            if (msgHash != 0xbd2a751) {
                if (msgHash != 0x1bb845c9) {
                    return -1;
                }
                return 1;
            }
            return 0x11; // 17
        }
        // Handle "attack" or "fight" message (0x2fd81222)
        entityId = 0;
        if ((*(int*)(message + 8) != 0) && (*(int*)(message + 8) != 0x48)) {
            if (*(int*)(message + 8) == 0) {
                ownerId = 0;
            } else {
                ownerId = *(int*)(message + 8) - 0x48;
            }
            // Get component from target
            component = (int*)getComponent(ownerId, 0x55859efa);
            tempChar = isMultiplayer();
            if (tempChar == '\0') {
                // Single player: check if target is player-controlled
                tempChar = (**(code**)(*component + 0x1f8))();
                if ((tempChar == '\0') || (ownerId = getPlayer(), ownerId == 0)) goto LAB_00782f6e;
                entityId = getComponent(ownerId, 0x55859efa);
            } else {
                // Multiplayer: get local player
                entityId = getLocalPlayer();
            }
            if ((entityId != 0) && (entityId == *(int*)(thisPtr + 0x28))) {
                return -1;
            }
        }
LAB_00782f6e:
        if (((entityId != 0) && (entityId = getComponent(entityId, 0x369ac561), entityId != 0)) &&
           ((*(byte*)(entityId + 0x1f54) & 1) != 0)) {
            return 6;
        }
        return 5;
    }
    // Fallthrough (should not reach)
    return -1;
}