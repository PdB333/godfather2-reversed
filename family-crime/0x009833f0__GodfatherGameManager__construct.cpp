// FUNC_NAME: GodfatherGameManager::construct
// Address: 0x009833f0
// Constructor for the GodfatherGameManager singleton. Sets up multiple vtable pointers,
// initializes sub-objects at offsets 0x54 and 0x58, then finalizes the vtable at +0x4C
// and zeros a global flag indicating initialization is complete.

void __fastcall GodfatherGameManager::construct(GodfatherGameManager* this)
{
    // Set primary vtable at offset 0x00
    *(void**)this = &PTR_FUN_00d90890;                  // +0x00: main vtable

    // Set secondary vtable at offset 0x10
    *(void**)((uint8*)this + 0x10) = &PTR_LAB_00d90868; // +0x10: secondary interface

    // Set temporary vtable for sub-object initialization at offset 0x4C
    *(void**)((uint8*)this + 0x4C) = &PTR_LAB_00d90864; // +0x4C: init phase vtable

    // Initialize sub-object at offset 0x58
    initSubObject(*(void**)((uint8*)this + 0x58));

    // Initialize sub-object at offset 0x54
    initSubObject(*(void**)((uint8*)this + 0x54));

    // Replace vtable at +0x4C with final operational vtable
    *(void**)((uint8*)this + 0x4C) = &PTR_LAB_00d90860; // +0x4C: final vtable

    // Clear global flag indicating singleton initialization is finished
    g_initializationComplete = 0;                        // _DAT_01130904

    // Post-initialization hook (e.g., register managers, start services)
    finalizeInit();
}