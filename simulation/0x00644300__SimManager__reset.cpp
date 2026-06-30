// FUNC_NAME: SimManager::reset
int SimManager::reset() {
    // +0x51c: byte flag indicating pending reset
    if (this->m_bResetPending) {
        this->m_bResetPending = false;
        // Iterate over global callback list (DAT_012059e4)
        for (CallbackNode* node = g_pCallbackList; node != nullptr; node = node->pNext) {
            node->pCallback(this, 0, node->pUserData);
        }
    }

    // +0x4e8: int flag for active state
    if (this->m_iActiveFlag) {
        clearActiveFlag(); // FUN_00643ed0
    }

    // +0x00: byte flag for overall active state
    if (this->m_bActive) {
        this->m_bActive = false;
        if (hasPendingWork()) { // FUN_00643da0
            processWorkQueue(); // FUN_00647b20
        }

        // Process list A (sentinel at +0x49c, head at +0x4a8)
        while (this->m_pListAHead != reinterpret_cast<ListNode*>(&this->m_listASentinel)) {
            removeFirstNodeFromListA(); // FUN_00643b00
            freeNodeA();                // FUN_00643a80
            updateListAState();         // FUN_00646ea0
        }

        // Process list B (sentinel at +0x448, head at +0x464)
        while (this->m_pListBHead != reinterpret_cast<ListNode*>(&this->m_listBSentinel)) {
            removeFirstNodeFromListB(); // FUN_00647e40
            freeNodeB(1);               // FUN_00648460
        }

        // Generate new ID and store at +0x440
        this->m_iNextId = generateNextId(); // FUN_00643d20

        // Clear 4 bytes at +0x468 (flags or small struct)
        this->m_byteArray468[0] = 0;
        this->m_byteArray468[1] = 0;
        this->m_byteArray468[2] = 0;
        this->m_byteArray468[3] = 0;
    }

    // Second check on active flag
    if (this->m_iActiveFlag) {
        this->m_iActiveFlag = 0;
        cleanupSubsystem1(); // FUN_00643ee0
        cleanupSubsystem2(); // FUN_00643eb0
    }

    return 1;
}