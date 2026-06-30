// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Function address: 0x006ea6d0
// EARS::Framework::GodfatherGameManager destructor
// Cleans up internal sub-objects and clears global singleton pointer.
void __fastcall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager *this)
{
    // Set vtable to final destructor vtable (ensures correct virtual dispatch during destruction)
    this->vtable = (void **)&PTR_FUN_00d5fd40;
    // Set secondary interface pointer to initial destruct state
    this->secondaryInterface = (void *)&PTR_LAB_00d5fd3c;

    // Static cleanup for global manager resources (e.g., sound, input)
    // DAT_01206a20 is a global manager object
    FUN_004086d0(&DAT_01206a20);

    // Release owned sub-object at offset 0x30 (e.g., a component or child manager)
    if (this->subObject != (void *)0x0) {
        FUN_009c8f10(this->subObject);
    }

    // Update secondary interface to disabled/tombstone state after sub-object cleanup
    this->secondaryInterface = (void *)&PTR_LAB_00d5fd38;

    // Clear global singleton pointer (marks manager as destroyed)
    DAT_01129880 = 0;

    // Final static cleanup for this manager type
    FUN_004083d0();
}