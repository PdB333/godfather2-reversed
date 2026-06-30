// FUNC_NAME: ControllerManager::clearControllerActiveFlag
void __thiscall ControllerManager::clearControllerActiveFlag(ControllerManager* this)
{
    uint32_t* flagPtr;
    int32_t arg;

    // Check that both controller device objects exist (offsets 0x70, 0x78)
    if (this->m_pDevice1 != 0 && this->m_pDevice2 != 0) {
        // Access controller state at [this->m_pStateBase + 0x564] and clear bit 0
        flagPtr = (uint32_t*)(*(int32_t*)(this->m_pStateBase) + 0x564);
        *flagPtr &= 0xfffffffe;

        // Global structure at 0x012233a0; read pointer at offset 4, then dereference
        int32_t** globalPtr = (int32_t**)0x012233a0;
        int32_t* valuePtr = globalPtr[1]; // offset 4 (assuming 4-byte pointers)
        if (*valuePtr != 0) {
            arg = *valuePtr - 0x1f30;
            FUN_00761620(arg);
            return;
        }
        arg = 0;
        FUN_00761620(0);
        return;
    }
    return;
}