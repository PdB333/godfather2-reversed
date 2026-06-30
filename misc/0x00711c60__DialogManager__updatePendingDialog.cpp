// FUNC_NAME: DialogManager::updatePendingDialog
void __fastcall DialogManager::updatePendingDialog(DialogManager* this) {
    DialogSpeaker* speaker = *(DialogSpeaker**)((char*)this + 4);
    if (speaker->m_bDialogPlaying != 0) {
        return; // already in a dialog
    }

    bool allQueueEmpty = (speaker->m_aDialogQueue[0] == 0 &&
                          speaker->m_aDialogQueue[1] == 0 &&
                          speaker->m_aDialogQueue[2] == 0 &&
                          speaker->m_aDialogQueue[3] == 0);

    // getNextQueuedDialog returns pointer to first non-zero entry, or null
    int* pQueuedEntry = nullptr; // will be set in condition
    bool doLookTarget = false;

    if (allQueueEmpty) {
        doLookTarget = true;
    } else {
        pQueuedEntry = (int*)getNextQueuedDialog(speaker->m_aDialogQueue); // FUN_006e7750
        if (pQueuedEntry == nullptr) {
            doLookTarget = true;
        } else {
            // If speaker is talking and dialog animation is not playing, also do look target
            bool isTalking = (*(char*)((char*)pQueuedEntry + 0x8a) & 1) != 0;
            bool animPlaying = (isDialogAnimPlaying(*(void**)((char*)this + 4)) != 0); // FUN_006e6830
            if (isTalking && !animPlaying) {
                doLookTarget = true;
            } else {
                doLookTarget = false;
            }
        }
    }

    if (doLookTarget) {
        Vector2 lookAtPoint; // local_c
        bool gotLook = getDialogLookTarget(&lookAtPoint); // FUN_00711bc0, returns false on success?
        if (!gotLook) { // actually getDialogLookTarget returns false if successful?
            // Or the code: if (cVar1 == '\0') { iVar2 = FUN_00471610(); set lookAtPoint from camera }
            // Let's follow decompiled: if (getDialogLookTarget returns false) use camera
            // But decompiled checks cVar1 == '\0' meaning false
            Camera* cam = (Camera*)FUN_00471610();
            lookAtPoint.x = *(float*)((char*)cam + 0x30);
            lookAtPoint.y = *(float*)((char*)cam + 0x38);
            // No z? local_c is 8 bytes, so likely 2 floats
        }
        // Now check if an entity exists at that screen position
        Entity* entity = (Entity*)getEntityAtScreenPosition(&lookAtPoint, 0); // FUN_006e68b0
        if (entity != nullptr) {
            bool isTrigger = isEntityDialogTrigger((Entity*)((char*)entity + 0x44)); // FUN_00718d40
            if (isTrigger) {
                playDialogLine(1, *(void**)((char*)this + 4)); // FUN_006e6430
            } else {
                entity = nullptr; // iVar2 = 0
            }
        }
        finalizeDialogStart(entity); // FUN_0071ab70 takes entity (or queued entry)
    } else {
        // Play the queued dialog directly
        playDialogLine(1, *(void**)((char*)this + 4)); // FUN_006e6430
        finalizeDialogStart(pQueuedEntry); // iVar2 = pQueuedEntry from earlier
    }
}