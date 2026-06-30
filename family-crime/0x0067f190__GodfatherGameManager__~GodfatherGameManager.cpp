// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable pointer to derived class vtable (likely for virtual cleanup)
    this->vtable = (void**)&PTR_FUN_00d58188;
    
    // Check if sub-object exists at offset 0x4
    if (this->m_pSubObject != 0) {
        // Call destructor on sub-object (e.g., StreamManager, SoundComponent, etc.)
        FUN_009c8f10(this->m_pSubObject);
    }
    
    // Reset vtable pointer to base class vtable (or null vtable to avoid double deletion)
    this->vtable = (void**)&PTR_LAB_00d580d4;
    
    // Clear global shutdown flag (DAT_011298c4) - indicates manager is no longer active
    g_bShutdown = 0;
}