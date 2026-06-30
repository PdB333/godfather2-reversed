// FUNC_NAME: GodfatherGameManager::destroy
void __thiscall GodfatherGameManager::destroy(GodfatherGameManager* this)
{
    // Set vtable to cleanup state (base class destructor entry)
    this->vtable = (void**)&PTR_FUN_00e3f470;
    
    // Call base class cleanup (likely framework shutdown)
    GodfatherGameManager::cleanupBase(); // FUN_005e1e50
    
    // Release resource container at offset +0x1738 (5CE * 4)
    if (this->resourceContainer != nullptr) {
        operator delete(this->resourceContainer); // FUN_009c8f10
    }
    
    // Release 5 sub-components (e.g., modules, managers)
    for (int i = 0; i < 5; i++) {
        GodfatherGameManager::releaseComponent(); // FUN_005e8260
    }
    
    // Finalize vtable to destroyed state
    this->vtable = (void**)&PTR_LAB_00e3f474;
    
    // Clear global singleton instance pointer
    g_GodfatherGameManagerInstance = nullptr; // DAT_0122350c
}