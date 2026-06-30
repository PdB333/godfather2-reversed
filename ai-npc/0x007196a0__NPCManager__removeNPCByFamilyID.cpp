// FUNC_NAME: NPCManager::removeNPCByFamilyID
void __thiscall NPCManager::removeNPCByFamilyID(int thisPtr, int familyID)
{
    // +0x324: family identifier stored in this manager
    int localFamilyID = *(int *)(thisPtr + 0x324);
    // +0x9c: head of a singly linked list of NPC nodes (each node: [npcPtr, nextPtr])
    int *currentNode = *(int **)(thisPtr + 0x9c);
    int baseThis = thisPtr;

    while (currentNode != nullptr) {
        int *nextNode = (int *)currentNode[1];      // node offset +1: next pointer
        int npcPtr = *currentNode;                  // node offset +0: NPC object pointer

        if (npcPtr != 0) {
            // FUN_0071c120: likely returns a pointer to the player's crew component (or null)
            int playerCrew = getPlayerCrewComponent();
            if (playerCrew != 0 &&
                // +0x1ed4 in playerCrew: family id to match against param_2
                *(int *)(playerCrew + 0x1ed4) == familyID) {
                // FUN_0071c320: check if the local (owner) family matches the NPC's family
                char isLocalPlayer = checkIfLocalPlayer(localFamilyID);

                // +8 in NPC: pointer to a sub-component (e.g. a crew member structure)
                int component = *(int *)(npcPtr + 8);
                if (component != 0) {
                    component -= 0x48; // adjust to base class (reverse a +0x48 offset)
                }

                // FUN_007195f0: remove the component node from the list (updates currentNode)
                removeFromList(component, &currentNode);
                nextNode = currentNode;

                if (isLocalPlayer != 0) {
                    // FUN_00738af0: deactivate the player crew component (e.g., remove from simulation)
                    deactivatePlayerCrew(playerCrew, 0);
                    nextNode = currentNode;
                }
            }
        }
        currentNode = nextNode;
    }

    // Second pass: global manager and special handling for the current game state
    if (*(int *)(baseThis + 0x18) != 0) {
        // FUN_0043b870: retrieve a singleton game manager object (global pointer at 0x01131018)
        int *globalMgr = (int *)getGlobalGameManager(DAT_01131018);
        if (globalMgr != nullptr) {
            // vtable[0x34]: method that returns a pointer to the current game state (e.g., a mission or mode)
            int *gameState = (int *)((*(int (__thiscall **)(int *))(*globalMgr + 0x34))(globalMgr));
            if (gameState != 0 &&
                *(int *)(gameState + 0xc) != 0 &&
                *(int *)(gameState + 0xc) != 0x48) {
                int *adjustedPtr;
                if (*(int *)(gameState + 0xc) == 0) {
                    adjustedPtr = nullptr;
                } else {
                    // offset +0xc in gameState: likely another object, adjusted by -0x48
                    adjustedPtr = (int *)(*(int *)(gameState + 0xc) - 0x48);
                }
                int someFlag = 0;
                // vtable[0x10]: method that takes a hash (0x55859efa) and a pointer to flag; returns bool
                char result = (*(char (__thiscall **)(int *, int, int *))(*adjustedPtr + 0x10))
                                (adjustedPtr, 0x55859efa, &someFlag);

                // unaff_ESI (preserved from loop) is used here – interpreted as the playerCrew pointer
                // It may actually be a third parameter passed in esi by the caller.
                int playerCrew = /* value from unaff_ESI */; // assume the same as from the loop
                if (result != 0 &&
                    playerCrew != 0 &&
                    *(int *)(playerCrew + 0x1ed4) == localFamilyID) {
                    // FUN_009aeca0: some global side effect (e.g., notify, enable something)
                    callGlobalFunction();
                }
            }
        }
    }
}