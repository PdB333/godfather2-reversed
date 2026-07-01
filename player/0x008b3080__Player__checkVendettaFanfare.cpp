// FUNC_NAME: Player::checkVendettaFanfare
void __thiscall Player::checkVendettaFanfare(int targetPlayerId, void* listContext) {
    // param_1 = this (Player*)
    // param_2 = listContext (some iterator context)
    // param_3 = targetPlayerId

    if (targetPlayerId == -1) {
        return;
    }

    // Initialize iterator over vendetta events for this target
    // FUN_004bab20 likely creates an iterator (local_1034) from listContext and targetPlayerId
    // local_1030 and local_102c indicate if the iterator has any items
    int iteratorValid; // local_1030
    int iteratorHasMore; // local_102c
    // local_1034 is a structure with function pointers:
    // [0] = getCurrent() -> returns pointer to current vendetta event
    // [2] = next() -> advances iterator
    // We'll model it as an iterator object
    VendettaIterator* iterator; // local_1034
    FUN_004bab20(&iterator, listContext, targetPlayerId);

    if (iteratorValid == 0 && iteratorHasMore == 0) {
        return;
    }

    // Get first event
    VendettaEvent* firstEvent = (VendettaEvent*)iterator->getCurrent();
    if (firstEvent->eventType != targetPlayerId) { // +0x10
        return;
    }

    int firstTargetId = firstEvent->someId; // +0x14

    int vendettaCount = 0;
    while (true) {
        // Advance iterator
        iterator->next();
        if (iteratorValid == 0 && iteratorHasMore == 0) {
            break;
        }

        VendettaEvent* currentEvent = (VendettaEvent*)iterator->getCurrent();

        // Check if this event belongs to this player (m_playerId at +0x50)
        if (currentEvent->playerId != this->m_playerId) { // +8 vs +0x50
            continue;
        }

        // Check if event matches the vendetta pair (firstTargetId, targetPlayerId)
        if (currentEvent->eventType == firstTargetId && // +0x10
            currentEvent->someId == targetPlayerId && // +0x14
            currentEvent->count >= 1) { // +0xc
            vendettaCount++;
        }
    }

    // Check if vendetta count exceeds threshold (m_maxVendettaCount at +100)
    if (vendettaCount >= this->m_maxVendettaCount) {
        // Log and display fanfare
        FUN_00604be0(); // start logging

        // Get player name for targetPlayerId
        int playerNameHandle = FUN_004baf60(targetPlayerId);
        char** namePtr = (char**)FUN_004bb600(playerNameHandle);
        char* playerName = *namePtr;
        if (playerName == nullptr) {
            playerName = &DAT_0120546e; // default name
        }

        FUN_00604c10(0x70, playerName); // log message

        // Prepare fanfare parameters
        int fanfareParams[3] = {0, 0, 0};
        void* fanfareCallback = nullptr;
        char buffer[4112]; // auStack_1014

        FUN_006038a0(DAT_012234a4, buffer, fanfareParams, "$hud_fanfare_mp_player_vendetta");
        FUN_0094e5d0(fanfareParams); // display HUD fanfare

        if (fanfareParams[0] != 0) {
            ((void (*)(int))fanfareCallback)(fanfareParams[0]);
        }

        FUN_00604c00(); // end logging
    }
}