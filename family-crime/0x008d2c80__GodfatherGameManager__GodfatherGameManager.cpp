// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x008d2c80
// Constructor for a manager class with vtable and state pointer at +0xC.
// The second parameter (allocationFlag) indicates whether object was heap-allocated;
// if bit 0 is set, the object will be deleted if construction fails (or cleanup called).
namespace GodfatherGameManager {
    class GodfatherGameManager {
        void* vtable;      // +0x00
        // Unknown fields...
        void* statePtr;    // +0x0C (set twice during init)
        // Probably more members...
    };
}

// Global variables (addresses from decompiled)
extern int DAT_012069d4; // Some global reference counter or singleton flag
extern int DAT_011299a0; // Another global state variable

// Forward declarations for callees
void incrementGlobalRefCount(int* global); // FUN_004086d0
void initializeGlobalState();                // FUN_004083d0
void destroyManager(GodfatherGameManager* obj); // FUN_009c8eb0 (likely destructor/free)

GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, byte allocationFlag) {
    // Set vtable pointer (virtual function table)
    this->vtable = &PTR_FUN_00d7d420; // VTable for GodfatherGameManager

    // Set internal state pointer (temporary?)
    this->statePtr = &PTR_LAB_00d7d41c; // Some static structure

    // Increment global reference count (e.g., singleton usage)
    incrementGlobalRefCount(&DAT_012069d4);

    // Update state pointer to another static variable
    this->statePtr = &PTR_LAB_00d7d418;

    // Reset global flag
    DAT_011299a0 = 0;

    // Perform other initialization (e.g., register with manager)
    initializeGlobalState();

    // If the object was heap-allocated (allocationFlag & 1), call destructor/cleanup
    // This pattern handles the case where construction fails after allocation.
    if (allocationFlag & 1) {
        destroyManager(this);
    }

    return this;
}