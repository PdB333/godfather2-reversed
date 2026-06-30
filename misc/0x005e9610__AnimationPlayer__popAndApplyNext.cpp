// FUNC_NAME: AnimationPlayer::popAndApplyNext
void AnimationPlayer::popAndApplyNext() {
    if (m_activeAnimCount > 0) {
        int idx = m_activeAnimIndex;
        AnimQueueItem* item = &m_animQueue[idx]; // array of 4 items at +0x294, each 0x78 bytes
        int newIdx = idx + 1;
        m_activeAnimIndex = newIdx;
        if (newIdx > 3) {
            newIdx = idx - 3; // wrap around modulo 4
        }
        m_activeAnimIndex = newIdx;
        m_activeAnimCount--;

        // Notify that queue decreased (likely deallocation or state update)
        FUN_005dbc10(m_activeAnimCount);

        // Clear some state on the animation object itself
        int* animObj = item->m_pAnimObject; // first dword of item
        if (animObj) {
            *(animObj + 0x60) = 0; // +0x60 often some "flags" or "active" field
        }

        // Set current animation object
        m_pActiveAnim = animObj;

        // Copy global timestamp (from DAT_01223518 + 8) to two fields
        unsigned int timestamp = *(unsigned int*)(DAT_01223518 + 8);
        m_animStartTime = timestamp; // +0x204
        m_animTimeOffset = timestamp; // +0x208

        // Store animation duration from the object (+0x54)
        m_animDuration = 0; // +0x1d8
        m_animMaxDuration = *(animObj + 0x54); // +0x1dc

        // Copy parameters from the queue item
        m_animExtraParam1 = item->m_extra1; // +0x20c, item[0x1c]
        m_animFlag1 = 0; // +0x283
        m_animFlag2 = 0; // +0x284
        m_animExtraParam2 = item->m_extra2; // +0x27c, item[0x1d]

        // Copy parameter block (0x1b ints = 108 bytes) from item after the first dword
        int* dest = &m_animParamBlock; // +0x210
        int* src = &item[1]; // item as int*, skip first dword
        for (int i = 0; i < 27; i++) {
            *dest++ = *src++;
        }

        // Reset some animation IDs
        m_prevAnimId = -1; // +0x1cc
        m_curAnimId2 = -1; // +0x1d0

        // Set flags
        m_animActiveFlag = 1; // +0x285
        m_animPausedFlag = 0; // +0x286

        // State transition check
        m_prevAnimState = m_animState; // +0x480 = +0x484
        if (m_animState != 4) {
            m_animState = 4; // +0x484 set to 4 (likely "playing" state)
            int transitionAllowed = FUN_005e8900();
            if (transitionAllowed) {
                m_prevAnimState = m_animState;
            }
        }
    }
}