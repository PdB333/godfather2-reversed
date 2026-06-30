// FUNC_NAME: CoverHintNodeManager::updateCoverNodeList
void __fastcall CoverHintNodeManager::updateCoverNodeList(CoverHintNodeManager* this)
{
    int local_4;
    int playerIndex;
    int* nodeArrayBase;
    int nodeCount;
    int* nodeArray;
    int nodeIndex;
    int* nodePtr;
    int* currentTargetPtr;

    // Get the global manager pointer and player index
    playerIndex = FUN_0077dd80(); // getCurrentPlayerIndex
    nodeArrayBase = (int*)(DAT_01129964 + 0x10 + playerIndex * 0xc); // base of player-specific cover node array

    // Mark this manager as not having a pending cover node?
    FUN_0071dc20(); // clearPendingCoverNode
    *(int*)(this + 0x10) = -1; // reset some index field

    // Determine the target cover node ID (local_4) based on current state
    if (*(int*)(this + 0x78) == 0 || *(int*)(this + 0x78) == 0x48) {
        // No current cover target or cover target is special (0x48 = cover slot disabled?)
        local_4 = *(int*)(this + 0x80);
    }
    else if (*(int*)(this + 0x78) == 0) {
        // This branch is likely dead due to decompiler error; originally: else if target is null?
        local_4 = iRam0000011c; // some global default ID
    }
    else {
        // Use the target's own ID
        local_4 = *(int*)(*(int*)(this + 0x78) + 0xd4);
    }

    // Iterate over all cover nodes in the player's array
    nodeCount = nodeArrayBase[1]; // element count
    nodeArray = (int*)*nodeArrayBase; // pointer to array of 8-byte entries

    for (nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++) {
        int nodeData = *(int*)((char*)nodeArray + nodeIndex * 8);
        if (nodeData == 0) {
            nodePtr = 0;
        }
        else {
            nodePtr = (int*)(nodeData - 0x48); // the actual cover node object (offset to base)
        }

        // Check if this node matches the current target
        if (local_4 == 0) {
            // No target: check if player can use this node
            char canUse = FUN_00727700(*(int*)(this + 0xc)); // isPlayerInRange?(void* player)
            if (canUse != 0) {
                canUse = (**(code**)(*nodePtr + 0x1c))(*(int*)(this + 0xc)); // virtual method: canPlayerUse? (offset 0x1c)
                if (canUse != 0) {
                    FUN_0071dfc0(nodePtr, DAT_00d5ccf8); // addCoverNodeToActiveList(CoverNode*, list)
                }
            }
        }
        else {
            // Has a specific target: only consider this node if it matches the current cover target
            int* currentCover = (*(int*)(this + 0x78) == 0) ? 0 : (int*)(*(int*)(this + 0x78) - 0x48); // Get current cover object pointer
            if (nodePtr == currentCover || (nodePtr && nodePtr[0x47] == local_4)) {
                // This node is the current cover or has the same ID as the target
                // do nothing? Actually the code jumps to LAB_0071e567 if condition fails, else continues loop
                // The loop continues to next iteration without adding
            }
            else {
                // Not matching; proceed to check if player can use it
                // This is the else part of the inner if, actually it jumps to LAB_0071e567
                // So we must replicate the logic
                char canUse = FUN_00727700(*(int*)(this + 0xc));
                if (canUse != 0) {
                    canUse = (**(code**)(*nodePtr + 0x1c))(*(int*)(this + 0xc));
                    if (canUse != 0) {
                        FUN_0071dfc0(nodePtr, DAT_00d5ccf8);
                    }
                }
            }
        }
    }

    // Additional check: if current cover target is non-null and not special (0x48), and if it has some flag set
    if (*(int*)(this + 0x78) != 0 && *(int*)(this + 0x78) != 0x48) {
        int coverBase = (*(int*)(this + 0x78) == 0) ? 0 : (*(int*)(this + 0x78) - 0x48);
        if ((*(byte*)(coverBase + 0x114) & 1) != 0) {
            // The current cover target is available (some flag)
            int* coverObj = (*(int*)(this + 0x78) == 0) ? 0 : (int*)(*(int*)(this + 0x78) - 0x48);
            char canUse = (**(code**)(*coverObj + 0x1c))(*(int*)(this + 0xc));
            if (canUse != 0) {
                int coverBase2 = (*(int*)(this + 0x78) == 0) ? 0 : (*(int*)(this + 0x78) - 0x48);
                FUN_0071dfc0(coverBase2, DAT_00d5ccf8); // add to list
            }
        }
    }

    // If no cover target is set, clear the pending cover node ID
    if (*(int*)(this + 0x74) == 0) {
        *(int*)(this + 0x80) = 0;
    }
    return;
}