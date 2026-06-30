// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this) {
    // Set vtable to base class (likely EARS::Framework::Object)
    *(void **)this = &PTR_FUN_00e3a5d0; // base vtable
    // Call base class constructor
    FUN_00ae97f0(); // BaseObject::BaseObject()
    // Set vtable to derived class
    *(void **)this = &PTR_LAB_00e3a5d4; // derived vtable
    // Initialize global initialization flag
    DAT_012234dc = 0; // g_gameManagerInitialized flag
}