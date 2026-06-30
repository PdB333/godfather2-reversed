// FUN_00500120: GhostObject::initializeFromTemplate
void GhostObject::initializeFromTemplate(GhostObjectTemplate* templateObj) // param_1 is templateObj pointer
{
    // Call base class constructor/initializer (likely EARSObjectBase)
    EARSObjectBase::baseInit();

    // Set vtable to GhostObject's vtable
    this->vtable = &GhostObject_vtable;  // 0x00e37c78

    this->field_0x30 = 0;                // unaff_ESI[0xc] = 0
    *(char*)&this->field_0x34 = 0;       // byte at +0x34
    *(char*)((uintptr_t)this + 0x35) = 0; // byte at +0x35

    if (*(char*)(templateObj + 0xD) == '\0') // check some condition in template
    {
        this->field_0x28 = 0;                  // unaff_ESI[10] = 0
        this->field_0x38 = g_globalData1;      // DAT_00e2b1a4
        uint32_t tempData = g_globalData2;     // DAT_00e2eff4
        this->sourceData = m_pSourceData;      // unaff_EDI pointer stored at +0x24 (unaff_ESI[9])
        this->field_0x3C = tempData;           // unaff_ESI[0xf]

        int32_t sourceFirstInt = *m_pSourceData; // *unaff_EDI
        this->field_0x2C = sourceFirstInt;      // unaff_ESI[0xb]

        if ((sourceFirstInt < 0) &&
            (m_pSourceData[2] == 0 && m_pSourceData[3] == 0) &&
            (m_pSourceData[4] == 0 && m_pSourceData[5] == 0))
        {
            *(char*)(templateObj + 0xC) = 1; // mark template as valid
            return;
        }
    }
    return;
}