// FUNC_NAME: GodfatherGameManager::evaluateActionCondition
void __thiscall GodfatherGameManager::evaluateActionCondition(int *pCondition) {
    char cVar1;

    // Virtual call to condition object's check method (vtable offset +0x10, index 4) with hash 0x55859efa
    // Likely bool ConditionObject::checkCondition(uint hash)
    cVar1 = ((char (__thiscall *)(int *, uint))(*pCondition + 0x10))(pCondition, 0x55859efa);

    // The comparison with stack address and DAT_00000004 is a compiler artifact; effectively if first check succeeds
    if (cVar1 != '\0') {
        // Global function check (e.g., g_fnGlobalCondition at pcRam0000028c)
        cVar1 = ((char (*)(void))pcRam0000028c)();
        if (cVar1 != '\0') {
            *(int8_t *)(this + 0x7c) = 1;   // m_bFlag (byte at +0x7c)
            goto LAB_006ca455;
        }
    }
    *(int8_t *)(this + 0x7c) = 0;             // m_bFlag = false

LAB_006ca455:
    if (*(int8_t *)(this + 0x7c) != '\0') {
        *(int32_t *)(this + 0x80) = _DAT_00d5780c; // m_dwValue (dword at +0x80) from global
        return;
    }
    *(int32_t *)(this + 0x80) = 0;             // m_dwValue = 0
    return;
}