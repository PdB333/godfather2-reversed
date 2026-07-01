// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00904ec0
// Constructor for GodfatherGameManager. Initializes the base class vtable pointers,
// then calls several EARS engine subsystem initializers, and finally sets the
// derived class vtable. Also zeros a global initialization flag.

void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Set base class vtable pointers (likely multiple inheritance or RTTI)
    *this = (void*)&PTR_FUN_00d82328;          // primary vtable
    this[1] = (void*)&PTR_LAB_00d82318;        // secondary vtable/data pointer

    // Initialize EARS engine subsystems (singletons or static objects)
    initSubsystem1(&DAT_0112ff44);             // e.g., AudioManager, InputManager
    initSubsystem2(&DAT_0112ff44);             // reuse same static object
    initSubsystem2(&DAT_0112ff4c);             // another subsystem object
    initSubsystem3();                          // final subsystem init

    // Overwrite primary vtable with derived class vtable
    *this = (void*)&PTR_LAB_00d82290;

    // Mark global initialization complete (0 = initialized)
    DAT_01129898 = 0;
}