// FUNC_NAME: GameResourceManager::GameResourceManager
// Function address: 0x00834ff0
// Role: Constructor for the global game resource manager singleton.
// Copies preloaded asset data (sound, textures, etc.) from global pointers into internal buffer.

GameResourceManager* __fastcall GameResourceManager::GameResourceManager(GameResourceManager* this)
{
    // Store global pointer to this singleton
    g_pResourceManager = this;

    // Initial vtable pointers (overwritten later)
    this->m_pVTable1 = (uint32_t)&label_00e32854;
    this->m_pVTable2 = (uint32_t)&func_00e2f19c;
    this->m_refCount = 1; // +0x0C
    this->m_flags = 0;    // +0x10

    uint32_t* pVtableBase = &this->m_dataBuffer; // actually &this[2], offset 0x08

    // Set final vtable pointers (three virtual function tables)
    this->m_pPrimaryVTable = (uint32_t)&func_00d73b34;  // +0x00
    this->m_pSecondaryVTable = (uint32_t)&label_00d73b30; // +0x04
    *pVtableBase = (uint32_t)&label_00d73b20;            // +0x08 (overwrites initial)

    this->m_field5 = 0;  // +0x14
    this->m_field6 = 0;  // +0x18
    this->m_field7 = 0;  // +0x1C

    ResourceManager::initResourceSystem(); // FUN_008340e0

    // Zero out region from offset 0xB8 to 0xD8
    this->m_count1 = 0;  // +0xB8 (index 0x2E)
    this->m_count2 = 0;  // +0xBC
    this->m_count3 = 0;  // +0xC0
    this->m_count4 = 0;  // +0xC4
    this->m_count5 = 0;  // +0xC8
    this->m_count6 = 0;  // +0xCC
    this->m_count7 = 0;  // +0xD0
    this->m_count8 = 0;  // +0xD4
    this->m_count9 = 0;  // +0xD8

    // Copy up to 32KB of asset data from global sources into the buffer at offset 0x08
    if (g_pSoundData != 0)
        copyData(pVtableBase, &g_pSoundData, 0x8000); // FUN_00408900
    if (g_pTextureData != 0)
        copyData(pVtableBase, &g_pTextureData, 0x8000);
    if (g_pModelData != 0)
        copyData(pVtableBase, &g_pModelData, 0x8000);
    if (g_pScriptData != 0)
        copyData(pVtableBase, &g_pScriptData, 0x8000);

    // Re-initialize some counts after the copy
    this->m_count5 = 0;  // +0xC8
    this->m_count6 = 0;  // +0xCC
    this->m_count4 = 0xC; // +0xC4 (set to 12)

    return this;
}