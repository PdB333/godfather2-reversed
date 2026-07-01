// FUNC_NAME: EntityVisibilityProcessor::advanceToNextVisible

void __thiscall EntityVisibilityProcessor::advanceToNextVisible(int thisPtr)
{
    int *currentNodeData; // piVar1, pointer to m_currentNodeData at +0x88
    int nodeHeader;       // iVar3, computed as (currentNodeData ? *currentNodeData - 0x48 : 0)
    int *prevNodeLink;    // piVar5, used to retrieve vtable at nodeHeader
    int localFlag;        // local_4, output flag for visibility check
    char visibleStatus;   // cVar2, result from visibility check

    currentNodeData = (int *)(thisPtr + 0x88); // pointer to current node data pointer

    // If current node is the terminator (0 or 0x48 sentinel), start iteration
    if ((*currentNodeData == 0) || (*currentNodeData == 0x48)) {
        do {
            // Convert node data pointer to node header (subtract 0x48 offset)
            if (*currentNodeData == 0) {
                nodeHeader = 0;
            } else {
                nodeHeader = *currentNodeData - 0x48;
            }

            // Get next node data from iterator at +0x78
            nodeHeader = FUN_00446100(thisPtr + 0x78, nodeHeader);
            if (nodeHeader == 0) {
                nodeHeader = 0;
            } else {
                nodeHeader = nodeHeader + 0x48; // convert header back to data pointer
            }

            // If the node changed, release old and link new
            if (*currentNodeData != nodeHeader) {
                if (*currentNodeData != 0) {
                    FUN_004daf90(currentNodeData); // release node (likely decrement refcount or delete)
                }
                *currentNodeData = nodeHeader;
                if (nodeHeader != 0) {
                    *(int *)(thisPtr + 0x8c) = *(int *)(nodeHeader + 4); // store previous link
                    *(int **)(nodeHeader + 4) = currentNodeData;          // backlink to this pointer
                }
            }

            // If we have a valid node (not terminator), check visibility
            if ((*currentNodeData != 0) && (*currentNodeData != 0x48)) {
                // Get node header from data pointer
                if (*currentNodeData == 0) {
                    prevNodeLink = (int *)0x0;
                } else {
                    prevNodeLink = (int *)(*currentNodeData - 0x48);
                }

                localFlag = 0;
                // Virtual function at vtable+0x10 (index 4) – “isVisible” test
                visibleStatus = (**(code **)(*prevNodeLink + 0x10))(0x38523fc3, &localFlag);

                if (((visibleStatus == '\0') || (localFlag == 0)) ||
                    (visibleStatus = FUN_00481620(), visibleStatus != '\0')) {
                    // Node is visible – store associated object
                    if ((*currentNodeData == 0) || (*currentNodeData == 0x48)) {
                        *(int *)(thisPtr + 0x90) = 0;
                    } else {
                        *(int *)(thisPtr + 0x90) = FUN_0043b870(DAT_01131018); // get global object (e.g., camera)
                    }
                    goto LAB_0090167a; // exit search
                }
            }
        } while ((*currentNodeData != 0) && (*currentNodeData != 0x48));
        // Reached terminator – clear associated object
        *(int *)(thisPtr + 0x90) = 0;
    }

LAB_0090167a:
    // If we found a visible node and it hasn't been processed yet (bit 1 of flags is clear)
    if (((*currentNodeData != 0) && (*currentNodeData != 0x48)) &&
        (*(int *)(thisPtr + 0x90) != 0) &&
        ((*(unsigned int *)(thisPtr + 0x94) >> 1 & 1) == 0)) {
        FUN_009af050(thisPtr + 0x50); // process the node/update
        *(unsigned int *)(thisPtr + 0x94) |= 2; // mark bit 1 as processed
    }
}