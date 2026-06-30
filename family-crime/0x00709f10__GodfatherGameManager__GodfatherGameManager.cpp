// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Initialize vtable pointer (set to class-specific vtable at 0x00d613b4)
    this->vtable = reinterpret_cast<void**>(&PTR_LAB_00d613b4);
    // Reset static initialization flag to 0 (uninitialized)
    GodfatherGameManager::s_bInitialized = 0;
}