// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x006abcb0
// Initializes the GodfatherGameManager singleton. Sets up vtable pointers, calls base initialization functions,
// then finalizes vtable and clears a global initialization flag.

void __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Set initial vtable (likely base class)
    *(void**)this = (void*)&PTR_FUN_00d5da74;
    // Set secondary pointer (RTTI or shape info, offset +0x4)
    *(void**)((char*)this + 4) = (void*)&PTR_LAB_00d5da64;

    // Call base class initialization on a static member (e.g., subobject at DAT_012069c4)
    FUN_004086d0(&DAT_012069c4);   // BaseInit (subobject constructor)
    FUN_004083d0();                // Additional initialization

    // Update vtable to final derived class
    *(void**)this = (void*)&PTR_LAB_00d5da60;

    // Clear global initialization flag (0 = not fully initialized or ready for use)
    DAT_01129900 = 0;
}