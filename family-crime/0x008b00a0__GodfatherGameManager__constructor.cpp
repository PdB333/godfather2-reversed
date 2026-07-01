// FUNC_NAME: GodfatherGameManager::constructor
undefined4* __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this) {
    // Global singleton pointer
    g_GodfatherGameManager = this;

    // Set vtable pointer
    this->vtable = &g_GodfatherGameManager_vtable; // 0x00d7a648

    // Clear many fields
    this->field_4 = 0;
    this->field_8 = 0;
    this->field_C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;

    // Allocate 0x30 bytes for sub-object
    void* subObject = operator_new(0x30); // FUN_009c8e80 expects size
    this->m_pSubObject = subObject;

    // Initialize more fields
    this->m_someCount = 0;            // +0x2C
    this->m_maxEntries = 0xC;         // +0x30 (12)
    this->field_38 = 0xFFFFFFFF;      // +0x38
    this->field_3C = 0;               // +0x3C
    this->field_40 = 0;               // +0x40
    this->field_44 = 0;               // +0x44

    // Debug sentinel values (appear to be leftovers, then cleared)
    this->m_debugMarker1 = 0xBADBADBA; // +0x48 (later zeroed)
    this->m_debugMarker2 = 0xBEEFBEEF; // +0x4C (later zeroed)
    this->m_debugMarker3 = 0xEAC15A55; // +0x50 (later zeroed)
    this->m_debugMarker4 = 0x91100911; // +0x54 (later zeroed)

    this->m_field58 = 0;               // +0x58
    this->m_field5C = 0;               // +0x5C

    // Zero out the debug markers (likely debugging artifacts)
    this->m_debugMarker4 = 0;
    this->m_debugMarker3 = 0;
    this->m_debugMarker2 = 0;
    this->m_debugMarker1 = 0;

    return this;
}