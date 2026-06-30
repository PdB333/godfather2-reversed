// FUNC_NAME: EARSControl::handleMessage
void __thiscall EARSControl::handleMessage(int* message) // message[0] = ID, message[1] = data
{
    int msgId = *message;
    
    if (msgId == s_MSG_SELECT) { // DAT_01206980
        if (m_pDelegate != nullptr) {
            // Delegate's vtable+0x3c = onSelect()
            m_pDelegate->vtable->onSelect();
            FUN_0046c6a0(message); // consume/advance event
            return;
        }
        if ((m_flags & 2) != 0) {
            FUN_004086d0(&s_MSG_SELECT); // deactivate/hide related UI
            m_flags &= ~2;
            FUN_0046c6a0(message);
            return;
        }
    }
    else if (msgId == s_MSG_BACK) { // DAT_01206970
        if (m_pDelegate != nullptr) {
            m_pDelegate->vtable->onBack(); // vtable+0x38
            FUN_0046c6a0(message);
            return;
        }
        if ((m_flags & 1) != 0) {
            FUN_004086d0(&s_MSG_BACK);
            m_flags &= ~1;
            FUN_0046c6a0(message);
            return;
        }
    }
    else {
        if (msgId == s_MSG_CHANGE) { // DAT_012069c4
            if ((m_pData != nullptr) && ((*(int*)(m_pData + 0x30) >> 1 & 1) != 0)) {
                // Base vtable+0x144 = onChange()
                m_pOwner->vtable->onChange();
            }
            m_pOwner->vtable->onUpdate(); // vtable+0x100
            FUN_0046c6a0(message);
            return;
        }
        if (msgId == s_MSG_CONFIRM) { // DAT_0120e93c
            FUN_004086d0(&s_MSG_CONFIRM);
            m_pOwner->vtable->onConfirm(); // vtable+0x70
            m_pOwner->vtable->onResult(1); // vtable+0x134
            FUN_0046c6a0(message);
            return;
        }
        if (msgId == s_MSG_LEFT) { // DAT_0120e944
            if (((m_shortFlags >> 0xd & 1) == 0) || (message[1] != m_pOwner->m_selectedIndex)) {
                goto consumeEvent;
            }
            m_state = 0;
            FUN_00471db0(1); // set mode/state
        }
        else if ((msgId == s_MSG_RIGHT) && ((m_shortFlags >> 0xd & 1) != 0) && (message[1] == m_pOwner->m_selectedIndex)) {
            // DAT_0120e94c
            m_state = 1;
            FUN_00471db0(0); // set mode/state
        }
    }
    consumeEvent:
    FUN_0046c6a0(message);
}