// FUNC_NAME: CoverState::SetCurrentCoverNode

// Address: 0x006A8850
// Role: Updates the current cover node link and associated flags/state.
// Called when the player/npc switches cover nodes (e.g., from one wall to another).

void __thiscall CoverState::SetCurrentCoverNode(int* pNewCoverRef, int* pNewNodeLink)
{
    int iVar1;
    byte bFlags;
    int iNewCoverId;
    int iCurrentCoverId;
    bool bSameCover;
    int iOldCoverNodeState; // pointer to cover node state (from pNewCoverRef)
    int iNewCoverNodeState; // pointer to cover node state (from pNewNodeLink)
    bool bOldCoverActive;

    // Check if cover state is enabled (flag at +0x10)
    if (*(char *)(this + 0x10) != '\0') {
        iCurrentCoverId = *pNewCoverRef; // ID of the current cover reference
        bSameCover = false;

        // Compare IDs and node state pointers
        if ((iCurrentCoverId == *pNewNodeLink) && 
            ((iCurrentCoverId == 0 || (pNewCoverRef[2] == pNewNodeLink[2])))) {
            bSameCover = true;
        }

        iOldCoverNodeState = 0; // from pNewCoverRef[2] or 0
        bOldCoverActive = false;
        iOldCoverId = 0; // Renamed from iVar8 to avoid confusion but could be iOldCoverId

        if (!bSameCover) {
            iOldCoverId = iCurrentCoverId; // Store the cover ID from ref
            if (iCurrentCoverId == 0) {
                iOldCoverNodeState = 0;
            }
            else {
                iOldCoverNodeState = pNewCoverRef[2]; // Pointer to old node state object
                // Clear bit 3 (0x8) of flags: "occupied"?
                *(byte *)(iOldCoverNodeState + 0x21) = *(byte *)(iOldCoverNodeState + 0x21) & 0xf7;
                bOldCoverActive = true;
            }
        }

        // Clear the "active" flag at +0x20 (maybe move version)
        *(undefined1 *)(this + 0x20) = 0;

        iCurrentCoverId = *pNewNodeLink; // ID from new link
        if (iCurrentCoverId == 0) {
            // New cover is null (no cover)
            if (bOldCoverActive) {
                // Clear bit 1 (0x2) and send notification
                *(byte *)(iOldCoverNodeState + 0x21) = *(byte *)(iOldCoverNodeState + 0x21) & 0xfd;
                // FUN_006a8100 likely a cover transition/event function
                // Parameters: coverId, nodeState, bEnter?=1, bExit?=0, unk=0
                FUN_006a8100(iOldCoverId, iOldCoverNodeState, 1, 0, 0);
            }
        }
        else {
            iNewCoverNodeState = pNewNodeLink[2]; // Pointer to new node state
            bFlags = *(byte *)(iNewCoverNodeState + 0x21);

            // Set bit 3 (0x8) to mark as "occupied" or "active"
            *(byte *)(iNewCoverNodeState + 0x21) = bFlags | 8;

            if (((bFlags & 2) == 0) || (bSameCover)) {
                // If not already marked as "current" (bit 1) or it's the same cover
                if ((bFlags & 0x10) == 0) {
                    // Generate a unique version/timestamp and store at +0x20
                    char uVar7 = FUN_006a8020(); // returns a byte (version?)
                    *(byte *)(iNewCoverNodeState + 0x21) = *(byte *)(iNewCoverNodeState + 0x21) | 0x10;
                    *(char *)(iNewCoverNodeState + 0x20) = uVar7;
                }

                // Set bit 1 (0x2) to mark as "current"
                *(byte *)(iNewCoverNodeState + 0x21) = *(byte *)(iNewCoverNodeState + 0x21) | 2;

                if (bOldCoverActive) {
                    // Notify old cover exit
                    FUN_006a8100(iOldCoverId, iOldCoverNodeState, 1, 0, 0);
                }

                // Notify new cover enter
                FUN_006a8100(iCurrentCoverId, iNewCoverNodeState, 0, 1, 0);
            }

            // Copy the version from new cover node state to this object
            *(char *)(this + 0x20) = *(char *)(iNewCoverNodeState + 0x20);
        }

        // Update the linked list node: replace the current node link with the new one
        int** ppPrevLink = (int**)(this + 0x14); // pointer to prev pointer of a doubly linked list node
        if (ppPrevLink != pNewNodeLink) {
            int iNewLinkId = *pNewNodeLink; // first field of the link structure (ID or pointer)
            if (*ppPrevLink != iNewLinkId) {
                if (*ppPrevLink != 0) {
                    // Unlink the old node
                    FUN_004daf90(ppPrevLink); // Probably removes itself from the list
                }
                *ppPrevLink = iNewLinkId;
                if (iNewLinkId != 0) {
                    // Link the new node into the chain: set next pointer at +0x18 of this to old next?
                    *(undefined4 *)(this + 0x18) = *(undefined4 *)(iNewLinkId + 4);
                    // And set the new node's prev to point back to this link slot
                    *(int **)(iNewLinkId + 4) = ppPrevLink;
                }
            }
        }

        // Store the node state pointer at +0x1c
        *(int *)(this + 0x1c) = pNewNodeLink[2];
    }
    return;
}