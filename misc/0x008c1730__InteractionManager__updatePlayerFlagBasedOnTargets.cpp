//FUNC_NAME: InteractionManager::updatePlayerFlagBasedOnTargets
void __thiscall InteractionManager::updatePlayerFlagBasedOnTargets(int thisPtr, char setFlag, int excludeId)
{
    // Get the head of the target list from this+0x88
    // FUN_0043c2c0 likely returns a pointer to the list head structure
    int* listHeadPtr = (int*)FUN_0043c2c0(*(int*)(thisPtr + 0x88));
    int* currentNode = (int*)*listHeadPtr; // first node in linked list

    while (currentNode != (int*)0x0) {
        int targetId = *currentNode; // node value (e.g., entity ID)
        // Skip null IDs and the excluded ID
        if ((targetId != excludeId) && (targetId != 0)) {
            // Get the global player object via DAT_01130950 (likely a singleton)
            int playerObj = FUN_0043b870(DAT_01130950);
            if (playerObj != 0) {
                // Check some condition (FUN_008a4380 returns false means condition not met)
                char conditionResult = FUN_008a4380();
                if (conditionResult == '\0') {
                    // Set or clear bit 8 (0x100) at playerObj+0x4c
                    if (setFlag == '\0') {
                        *(uint*)(playerObj + 0x4c) |= 0x100;
                    } else {
                        *(uint*)(playerObj + 0x4c) &= ~0x100;
                    }
                }
            }
        }
        currentNode = (int*)currentNode[1]; // next node (offset 4)
    }
}