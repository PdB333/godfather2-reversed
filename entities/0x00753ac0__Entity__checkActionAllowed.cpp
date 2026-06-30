// FUNC_NAME: Entity::checkActionAllowed
bool __thiscall Entity::checkActionAllowed(int actionId, int param2, int param3, int param5) {
    bool result = false;
    int basePtr;

    switch (actionId - 10) {
        case 0:
            if (m_stateFlags & 1) { // +0xA4 bit0
                triggerAction(); // FUN_00752f30
                return true;
            }
            break;
        case 1:
            if (!(m_stateFlags & 1)) return false;
            if (m_stateFlags & 4) return false; // bit2
            if (m_pActionData == nullptr) return false; // +0x98
            result = (*(uint32*)(m_pActionData + 4) >> 5) & 1; // bit5
            goto checkAndTrigger;
        case 2:
            if (!(m_stateFlags & 1)) break;
            if (m_stateFlags & 4) break; // bit2
            if (m_pActionData == nullptr) break;
            if ((*(uint8*)(m_pActionData + 4) & 0xC0) != 0) { // bits6+7
                triggerAction();
                return true;
            }
            break;
        case 3:
            if (!(m_stateFlags & 1)) return false;
            if (m_pActionData == nullptr) return false;
            result = (*(uint32*)(m_pActionData + 4) >> 8) & 1; // bit8
            goto checkAndTrigger;
        case 4:
            if (!(m_stateFlags & 1)) return false;
            if (m_pActionData == nullptr) return false;
            result = (*(uint32*)(m_pActionData + 4) & 0x20400) != 0; // bits 10+17
            goto checkAndTrigger;
        case 5:
            if (!(m_stateFlags & 1)) break;
            if (m_pCharacter == nullptr) break; // +0x9C
            if (m_pCharacter == (void*)0x48) break;
            {
                int t1 = getGameTime(); // FUN_0043b490
                int t2 = getGameTime(); // call same function
                if (t1 != t2) {
                    triggerAction();
                    return true;
                }
            }
            break;
        case 6:
            if (!(m_stateFlags & 1)) break;
            if (m_pCharacter == nullptr) break;
            if (m_pCharacter == (void*)0x48) break;
            {
                int t1 = getGameTime();
                int t2 = getGameTime();
                if (t1 != t2) {
                    basePtr = (m_pCharacter == nullptr) ? 0 : (int)m_pCharacter - 0x48;
                    if (*(char*)(basePtr + 0x1B8C) != '\x03') {
                        if (m_pCharacter == nullptr) basePtr = 0;
                        else basePtr = (int)m_pCharacter - 0x48;
                        if (*(char*)(basePtr + 0x1B8C) != '\x02') return false;
                    }
                    triggerAction();
                    return true;
                }
            }
            break;
        case 7:
            if (m_someObject == nullptr) { // +0x50
                return someCheck(); // FUN_004ac260
            }
            {
                float cur = getCurrentTime(); // FUN_0045fa40
                float dt = getDeltaTime();   // FUN_0045fa60
                if (cur / dt >= g_timeThreshold) // DAT_00d5f378
                    return true;
            }
            break;
        default:
            return defaultActionHandler(param2, param3, actionId, param5); // FUN_004ac640
    }
    return result;

checkAndTrigger:
    if (result) {
        triggerAction();
        return true;
    }
    return false;
}