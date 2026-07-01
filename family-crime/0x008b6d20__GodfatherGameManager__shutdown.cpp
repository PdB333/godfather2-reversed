// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager* this)
{
    char isActive;

    // Set vtable pointer to base class vtable (destructor safety)
    *(void**)this = (void*)&PTR_FUN_00d7b238; // vtable

    // Set additional function pointers / internal vtables
    this->field_0x3C = &PTR_LAB_00d7b228; // +0x3C
    this->field_0x48 = &PTR_LAB_00d7b224; // +0x48
    this->field_0x50 = &PTR_LAB_00d7b220; // +0x50
    this->field_0x54 = &PTR_LAB_00d7b1c0; // +0x54
    this->field_0x58 = &PTR_LAB_00d7b158; // +0x58
    this->field_0x180 = &PTR_LAB_00d7b140; // +0x180

    // Deallocate singleton/global memory
    operatorDelete(&DAT_0112abd8); // global audio data

    isActive = someActiveCheck(); // e.g., isGamePlaying()

    // Conditional cleanup: if not active, and the object has a certain sub-object
    // and the flags indicate it's in a specific state
    if ((((isActive == 0) && (this->field_0x194 != 0)) && ((this->field_0x290 & 0x20) != 0)) &&
       ((this->field_0x290 & 0x100) == 0)) {
        operatorDelete(&DAT_0112a5cc); // additional global resources
        operatorDelete(&DAT_0112a618);
    }

    // Clean up more global resources
    operatorDelete(&DAT_0112a660);
    operatorDelete(&DAT_0112a650);
    operatorDelete(&DAT_0112a600);
    operatorDelete(&DAT_0112afa0);

    // Destroy sub-object at +0x29C
    subObjectDestructor(this + 0xa7); // +0x29C
    // Additional sub-object destruction
    subObjectDestructor2(this + 0xa7); // +0x29C (different destructor)
    subObjectDestructor2(this + 0xa5); // +0x294

    // Delete another sub-object if non-null
    if (this->field_0x2A8 != 0) {
        anotherDelete(this + 0xaa); // +0x2A8
    }

    // Final global shutdown (e.g., engine cleanup)
    globalShutdown(); // FUN_008ba520
}