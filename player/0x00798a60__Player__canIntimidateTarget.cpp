// FUNC_NAME: Player::canIntimidateTarget
bool __thiscall Player::canIntimidateTarget(int thisPtr, int targetPtr) {
    bool result = false;
    GodfatherGameManager* gameMgr = GodfatherGameManager::getInstance();
    if (gameMgr != nullptr && ((*(uint*)(thisPtr + 0x8e0) >> 10) & 1) != 0 && targetPtr != nullptr) {
        uint donLevel = *(uint*)(gameMgr + 0x328); // +0x328: m_donLevel
        if (*(char*)(targetPtr + 0x1b8c) == '\0') { // +0x1b8c: m_isBoss? (0 = normal, 1 = boss)
            bool cheatsEnabled = FUN_00701010(); // likely areCheatsEnabled()
            if (cheatsEnabled) {
                return 2 < donLevel;
            }
            if (*(char*)(gameMgr + 0x1aa) == '\x01') { // +0x1aa: m_isDon
                return 1 < donLevel;
            }
        } else {
            if (*(char*)(targetPtr + 0x1b8c) != '\x01') {
                return false;
            }
            bool cheatsEnabled = FUN_00701010();
            if (cheatsEnabled) {
                return 2 < donLevel;
            }
        }
        result = donLevel != 0;
    }
    return result;
}