// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable pointer for this class (offset 0)
    this->vtable = &PTR_FUN_00d5d8b8;
    // Set vtable pointer for base class or secondary vtable (offset 12)
    this->baseVtable = &PTR_LAB_00d5d8b4;

    // Decrement global reference count or release global resource
    releaseGlobalResource(&DAT_012069c4);

    // If sub-object at offset 20 exists, destroy it
    if (this->subObject != 0) {
        destroySubObject(&this->subObject);
    }

    // Update vtable pointer for base class (offset 12) to a different vtable (post-destruction state)
    this->baseVtable = &PTR_LAB_00d5d898;

    // Reset global flag to 0
    DAT_011299b4 = 0;

    // Perform final cleanup
    cleanup();
}