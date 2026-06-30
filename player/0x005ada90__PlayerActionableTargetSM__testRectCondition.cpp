// FUNC_NAME: PlayerActionableTargetSM::testRectCondition
uint* PlayerActionableTargetSM::testRectCondition(uint param_1)
{
    uint* pResult;
    // unaff_ESI is likely a member variable like m_currentState
    if ((this->m_state != 1) && (1 < this->m_state)) {
        setRectIndex(0);                // FUN_005a0d00(0)
        float fY = getRectComponent();  // FUN_005a9040()
        setRectIndex(1);                // FUN_005a0d00(1)
        float fX = getRectComponent();  // FUN_005a9040()
        if (2 < this->m_state) {
            setRectIndex(2);            // FUN_005a0d00(2)
            getOtherComponent();        // FUN_005a8fe0()
        }
        processCondition(param_1);      // FUN_005b5a40(param_1)
        // local_10, local_8, local_c, local_4 are rectangle bounds loaded from member fields or global state
        if ((rectXMin <= fX && fX <= rectXMax) &&
            (rectYMin <= fY && fY <= rectYMax)) {
            // Allocate 8-byte object from global custom allocator
            pResult = (uint*)(*g_allocator)(8, 0); // DAT_0119caf0
            if (pResult != nullptr) {
                // Set flags: bits 0-2 = 7 (type?), clear bits 3-14, set bit 15
                *pResult = (*pResult & 0xFFFF8007) | 7;
                *(uint16*)((int)pResult + 2) = 0;   // Clear short at offset 2
                *pResult |= 0x8000;                 // Set bit 15
                pResult[1] = 1;                     // Second dword = 1
                return pResult;
            }
            return nullptr;
        }
    }
    return g_defaultResult; // DAT_0119cbbc
}