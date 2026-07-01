// FUNC_NAME: GodfatherGameManager::initializeFromData
void __fastcall GodfatherGameManager::initializeFromData() {
    // +0x5F4 (param_1[0x17d]) is a pointer to a subsystem with flags at +0x18
    SystemFlags* sysFlags = reinterpret_cast<SystemFlags*>(this->m_pSubsystem); // m_pSubsystem at offset 0x5F4
    sysFlags->field_0x18 &= ~0x20000; // Clear bit 0x12 (byte offset +0x1a?)

    // +0x3C (param_1 + 0x0F) is a data buffer (e.g., string or hash)
    // Build a temporary string from global constant DAT_0112dd94
    StackString tempString; // local_54..local_4c..local_50, small stack string
    FUN_00408bf0(&tempString, this->m_dataBuffer + 0x3C, 0); // loads string/hash into tempString

    sysFlags->field_0x18 |= 0x20000; // Set same bit again

    if (FUN_0089c630() != 0) { // Some condition (e.g., debug mode, loaded state)
        int foundObject = 0;
        // vtable method at +0x10: likely findObjectByHash or resolveReference
        if (this->vtable_method_0x10(0x383225A1, &foundObject) && foundObject) {
            FUN_008a0af0(foundObject); // Perform action on found object (e.g., play FX, spawn)
        }
    }

    // Cleanup stack objects constructed by FUN_0084dd20 / FUN_0084d760
    if (this->m_stackObj1[0] != 0) { // +0x__ (local_3c)
        FUN_004daf90(this->m_stackObj1); // Delete object
    }
    if (this->m_stackObj2[0] != 0) { // +0x__ (aiStack_44)
        FUN_004daf90(this->m_stackObj2);
    }
}