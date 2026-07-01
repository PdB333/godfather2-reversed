// FUNC_NAME: GodfatherGameManager::destructor

void __fastcall GodfatherGameManager::destructor(GodfatherGameManager* this)
{
    // +0x00: vtable pointer set to base class vtable
    this->vtable = (void*)0x00d916f8;
    // +0x04: secondary vtable pointer
    this->someVtable1 = (void*)0x00d916d0;
    // +0x4C (0x13*4): another vtable pointer
    this->someVtable2 = (void*)0x00d916c0;
    // +0x58 (0x16*4): yet another vtable pointer
    this->someVtable3 = (void*)0x00d916bc;

    // +0x5C (0x17*4): pointer to sub-manager object
    if (this->m_pSubManager != nullptr)
    {
        // Call virtual destructor of sub-manager with argument 1
        ((void(__thiscall*)(int))(*(this->m_pSubManager)))(1);
    }
    this->m_pSubManager = nullptr;

    // +0x260 (0x98*4): pointer to another sub-manager
    if (this->m_pAudioManager != nullptr)
    {
        // Call its cleanup function pointer stored at +0x26C (0x9B*4)
        ((void(__thiscall*)(void*))(this->m_audioCleanupFunc))(this->m_pAudioManager);
    }

    // Destroy two shared subsystems
    AudioDataManager::destroy();  // FUN_0098bd20
    AudioDataManager::destroy();  // FUN_0098bd20

    // +0x230 (0x8C*4): pointer to resource
    if (this->m_pResource != nullptr)
    {
        StreamManager::releaseResource(this->m_pResource);  // FUN_009c8f10
    }

    // +0x220 (0x88*4): pointer to manager
    InputDeviceManager::shutdown(this->m_pInputManager);  // FUN_0098c020

    // Update vtable pointer for final base
    this->someVtable3 = (void*)0x00d916b0;

    // Reset global reference
    g_gameManagerRefCount = 0;  // DAT_0112a044

    // Perform global cleanup
    GlobalMemoryPool::flush();    // FUN_004083d0
    GlobalStreamPool::flush();    // FUN_005c16e0
}