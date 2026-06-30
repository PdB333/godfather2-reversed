// FUN_004c9900: CharacterAttachmentSystem::updateBestAttachment

// This function iterates over all available attachment points (e.g., weapon holster positions, 
// car attachment spots) and selects the one with the highest "score" (likely based on distance, angle, 
// or animation state). It then detaches the current attachment (if any) and attaches to the new best point.
// The attachment points are managed by a linked list stored in the attachment manager (this +0x10).
// The current attachment is stored at this +0x18.

void CharacterAttachmentSystem::updateBestAttachment(int this) {
    int currentItem;          // iVar2 – current list node being iterated
    int bestItemData;         // iVar3 – data from the node (e.g., bone handle)
    char canAttachResult;     // cVar4 – result of canAttach check
    float currentScore;       // fVar5 – score for each candidate
    int bestCandidate;        // local_18 – data of the best candidate
    float bestScore;          // local_14 – highest score seen

    currentScore = 0.0f;
    currentItem = **(int**)(*(int*)(this + 0x10) + 0x1c);  // dereference to head of attachment list
    bestCandidate = 0;
    bestScore = 0.0f;

    while (true) {
        // Get the list terminator from the manager (probably null or sentinel)
        int listEnd = *(int*)(*(int*)(this + 0x10) + 0x1c);  // same as initial, but constant
        if ((currentItem == 0) || (currentItem != *(int*)(this + 0x10))) { // sanity check
            FUN_00b97aea();   // failed assertion / debug break
        }
        if (currentItem == listEnd) break; // reached end of list

        if (currentItem == 0) {
            FUN_00b97aea(); // assertion
        }
        if (currentItem == *(int*)(currentItem + 0x1c)) { // maybe self-reference check?
            FUN_00b97aea(); // assertion
        }

        // Extract the actual attachment point data from the node
        int candidateData = *(int*)(currentItem + 0x10);  // e.g., bone index or handle

        // Evaluate the candidate: sets currentScore based on some criteria
        FUN_004c90f0();  // computeAttachmentScore – score stored in global? likely sets currentScore

        if (bestScore < currentScore) {
            bestCandidate = candidateData;
            bestScore = currentScore;
        }

        // Advance to next node in the list (actual next pointer is hidden in decompilation)
        FUN_004cab50();  // getNextAttachmentNode – likely updates currentItem internally
        // Note: The original loop does not explicitly reassign currentItem; the above call probably 
        // modifies a global pointer or currentItem is implicitly updated. For clarity, we assume 
        // currentItem becomes the next node.
    }

    int currentAttached = *(int*)(this + 0x18);
    if (bestCandidate != currentAttached) {
        // Detach old attachment
        if (currentAttached != 0) {
            FUN_0043e500(currentAttached);               // releaseAttachment / detachFromBone
            currentAttached = *(int*)(this + 0x18);       // re-read after detach (may have changed)
            if ((*(char*)(currentAttached + 4) != '\0') && (*(int*)(currentAttached + 0x290) != 0)) {
                FUN_005ddd90(DAT_01223508, *(int*)(currentAttached + 0x290)); // sendDetachEvent(global, handle)
                *(char*)(currentAttached + 4) = '\0';    // clear attached flag
            }
        }

        // Attach new candidate
        if (bestCandidate != 0) {
            FUN_0043e500(bestCandidate);                 // prepareAttachment
            if (*(int*)(bestCandidate + 0x290) != 0) {
                canAttachResult = FUN_005ddc30(DAT_01223508); // canAttach(global)
                if (canAttachResult != '\0') {
                    *(char*)(bestCandidate + 4) = 1;     // set attached flag
                }
            }
        }

        *(int*)(this + 0x18) = bestCandidate;            // store new attachment
    }
    return;
}

// Fields:
// this + 0x10: pointer to attachment manager (list owner)
// this + 0x18: current attachment data (e.g., bone handle)
// Manager + 0x1c: pointer to head of attachment node list (or sentinel)
// Attachment node + 0x10: actual attachment handle (bone index or slot ID)
// Attachment node + 0x1c: internal list management field (next node or self check)
// Current attachment + 0x04: flag indicating if attached
// Current attachment + 0x290: event/notifier handle for detach/attach events
// DAT_01223508: global bone/attachment manager instance