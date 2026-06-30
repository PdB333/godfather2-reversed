// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00565f40
// Role: Constructor for GodfatherGameManager, sets vtable, calls base initialization, clears a global flag.
//        If the contruction flag (bit 0) is set, calls a post-construction registration function.

#include <cstdint>

// Vtable pointers for base and derived class
#define VTABLE_BASE     ((void**)0x00e3a5d0)
#define VTABLE_DERIVED  ((void**)0x00e3a5d4)

// External: base initialization function (likely EARSObject::constructor)
extern void __thiscall baseInitialization(void* this); // 0x00ae97f0

// External: registration/cleanup function called after construction if flag & 1
extern void __thiscall postConstructRegistration(void* this); // 0x009c8eb0

// Global: game manager initialization flag
extern int g_gameManagerInitialized; // 0x012234dc

class GodfatherGameManager {
    void* vtable; // +0x00

public:
    // Constructor with optional registration flag
    // flag & 1 indicates whether to call postConstructRegistration (heap allocated?)
    GodfatherGameManager* __thiscall constructor(GodfatherGameManager* this, byte flag);
};

GodfatherGameManager* __thiscall GodfatherGameManager::constructor(GodfatherGameManager* this, byte flag) {
    // Set base vtable (base class is likely EARSObject or similar)
    this->vtable = VTABLE_BASE;

    // Call base class initialization
    baseInitialization(this);

    // Set final derived vtable
    this->vtable = VTABLE_DERIVED;

    // Clear the global initialization flag
    g_gameManagerInitialized = 0;

    // If the contruction flag is set, perform additional registration
    if ((flag & 1) != 0) {
        postConstructRegistration(this);
    }

    return this;
}