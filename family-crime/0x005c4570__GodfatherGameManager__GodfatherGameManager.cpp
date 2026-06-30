// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable pointer to base class vtable
    this->vtable = (void*)&PTR_FUN_00e3ea08;

    // Call base constructor (likely BaseGameManager::BaseGameManager)
    FUN_005c4290();

    // Call virtual Init method on member object (stored at this+0x4)
    // The member's vtable has a virtual function at offset 0xC (3rd virtual)
    // This is likely an embedded component initializer
    SomeInternalComponent* comp = *(SomeInternalComponent**)((uint8_t*)this + 4);
    comp->vtable[3](); // (void (*)()) (comp->vtable[3])();

    // Switch vtable to derived class vtable
    this->vtable = (void*)&PTR_LAB_00e3ea0c;

    // Zero out global state variables
    g_GodfatherGameManager_someFlag1 = 0;  // DAT_0119caf0
    g_GodfatherGameManager_someFlag2 = 0;  // DAT_0119caf4
    g_GodfatherGameManager_someCounter = 0; // DAT_0119caf8
    g_GodfatherGameManager_someGlobalFlag = 0; // DAT_012234ec

    return;
}