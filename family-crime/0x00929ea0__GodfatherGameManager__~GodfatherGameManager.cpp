// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

extern void *PTR_FUN_00d8859c;   // +0x00 vtable pointer (derived class)
extern void *PTR_LAB_00d88598;   // +0x18 vtable pointer (intermediate base)
extern void *PTR_LAB_00d88594;   // +0x18 final vtable pointer (base)
extern int g_someGlobalPointer;  // _DAT_011304f0

void __fastcall GodfatherGameManager::destructor(void *this) {
    // Set vtable pointers to enable correct virtual calls during sub-object destruction
    *(void**)this = &PTR_FUN_00d8859c;          // set first vtable at +0x00
    ((void**)this)[6] = &PTR_LAB_00d88598;      // set second vtable at +0x18

    // Destroy owned sub-objects
    destroyObject(((void**)this)[8]);            // +0x20
    destroyObject(((void**)this)[10]);           // +0x28
    if (((void**)this)[14] != 0) {               // +0x38 – optional pointer
        destroyObject(((void**)this)[14]);
    }

    // Reset second vtable to base class before final cleanup
    ((void**)this)[6] = &PTR_LAB_00d88594;      // restore base vtable at +0x18

    // Global state cleanup
    g_someGlobalPointer = 0;                     // clear singleton reference
    cleanupStaticState();                        // final cleanup
}