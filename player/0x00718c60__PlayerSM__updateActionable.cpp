// FUNC_NAME: PlayerSM::updateActionable
void __thiscall PlayerSM::updateActionable(int thisObj)
{
    int targetData;
    char healthCheck;
    int targetPtr;
    int someCounter;
    int otherObj;
    int distance;

    // Check if the "disabled" bit (bit 2) is clear in the data object's flags at offset 0x1f54.
    if ((*(uint *)(*(int *)(thisObj + 0x18) + 0x1f54) >> 2 & 1) == 0) {
        // Not disabled – check game mode
        int gameMode = FUN_00806440(); // GetGameMode
        if (gameMode == 2) {
            // In game mode 2 (e.g., combat?), check if the player can act based on health
            int playerIndex = FUN_00471610(); // GetLocalPlayerIndex
            healthCheck = FUN_00787260(playerIndex + 0x30); // Check health threshold (e.g., < 30%)
            if (healthCheck == 0) {
                // Health too low – clear action flag
                goto clearActionFlag;
            }
        }
        else {
            // Not in game mode 2 – evaluate based on target data
            targetPtr = *(int *)(*(int *)(thisObj + 0x18) + 0x1ed8); // m_pTarget or m_pCurrentAction
            if ((targetPtr != 0) && (targetPtr != 0x48)) {
                someCounter = *(int *)(targetPtr + 0x20); // e.g., m_timeRemaining or m_range
                if (someCounter > 0) {
                    otherObj = *(int *)(*(int *)(thisObj + 0x18) + 0x2134); // m_pSecondaryTarget or m_pInteraction
                    if (otherObj == 0) {
                        // No secondary target – compute remaining distance
                        int targetPos = *(int *)(targetPtr + 0x40); // position/offset?
                        distance = FUN_0043c2a0(targetPos) - someCounter; // ComputeDistanceToTarget - currentCount
                    }
                    else {
                        // Has secondary target – get distance from it
                        otherObj = FUN_006b0ee0(otherObj); // Resolve to object pointer
                        if (otherObj == 0) {
                            // Invalid – jump to set action flag
                            goto setActionFlag;
                        }
                        // Check if target matches
                        if (*(int *)(otherObj + 0x40) == *(int *)(targetPtr + 0xc)) {
                            // Same target – use combined distances
                            distance = (*(int *)(otherObj + 0xac) + *(int *)(otherObj + 0xa0)) - someCounter;
                        }
                        else {
                            // Different target – use single distance
                            distance = *(int *)(otherObj + 0x88) - someCounter;
                        }
                    }
                    // If the residual distance is negative (target out of range?) – clear flag
                    if (someCounter < 0) { // Equivalent to SBORROW check: iVar3 < iVar1
                        goto clearActionFlag;
                    }
                }
            }
        }
setActionFlag:
        // Set action flag (bit 3) at this +0x308
        *(uint *)(thisObj + 0x308) |= 8;
        return;
    }
clearActionFlag:
    // Clear action flag (bit 3) at this +0x308
    *(uint *)(thisObj + 0x308) &= 0xfffffff7;
    return;
}