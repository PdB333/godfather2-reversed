// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Function address: 0x006ea830
// Destructor for GodfatherGameManager (singleton manager).
// Calls global mutex operations and cleans up child component at +0x30.

void __thiscall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager *this, byte param_2)
{
    // Set vtable to class vtable (most derived)
    *(void **)this = &PTR_FUN_00d5fd40;
    // Set secondary vtable at offset +0x0C (likely second base class)
    *(void **)((char *)this + 0x0C) = &PTR_LAB_00d5fd3c;

    // Lock the global mutex associated with this manager
    lockGlobalMutex(&gGlobalMutex);

    // Release a child/component stored at offset +0x30
    if (*(void **)((char *)this + 0x30) != 0) {
        destroyComponent(*(void **)((char *)this + 0x30));
    }

    // Switch vtable to base class vtable for base destructor chain
    *(void **)((char *)this + 0x0C) = &PTR_LAB_00d5fd38;

    // Mark the manager as no longer initialized
    gIsInitialized = 0;

    // Call base class destructor (unlock and finalize)
    unlockGlobalMutex();

    // If the flag indicates we should deallocate, free the object
    if ((param_2 & 1) != 0) {
        operatorDelete(this);
    }
}