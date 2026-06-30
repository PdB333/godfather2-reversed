// FUNC_NAME: GodfatherGameManager::shutdown
#include <cstdint>

// External function pointers and globals (from EARS engine globals)
extern void releaseSubObject();                // FUN_005ba710 - possibly releases sub-object state
extern void (*gDeallocFunc)(void*, int);       // DAT_0119caf8 - custom deallocation routine, takes pointer and size/type (0x48)

// Destructor table indexed by low 15 bits of the first word of each manager object
extern void (*gDestructorTable[])(void*);      // DAT_0103aee0

// Global singleton pointers (manager instances) to be cleaned up
extern uint32_t* gManager1;   // DAT_012055bc
extern uint32_t* gManager2;   // DAT_012055b8
extern uint32_t* gManager3;   // DAT_012055dc
extern uint32_t* gManager4;   // DAT_012055c4
extern uint32_t* gManager5;   // DAT_012055c8
extern uint32_t* gManager6;   // DAT_012055cc
extern uint32_t* gManager7;   // DAT_012055d0
extern uint32_t* gManager8;   // DAT_012055d8
extern uint32_t* gManager9;   // DAT_012055d4
extern uint32_t* gManager10;  // DAT_012055c0
// (There are 11 global manager slots – names are arbitrary, adjust if known)

// Helper macro to destroy a manager via its embedded type index (vtable-like)
#define DESTROY_MANAGER(ptr) \
    if (ptr) { \
        uint32_t typeIdx = (*ptr) & 0x7FFF; \
        gDestructorTable[typeIdx](ptr); \
        ptr = nullptr; \
    }

void GodfatherGameManager::shutdown() {
    // +0x04? Actually offset +0x0c from this: a sub-object pointer
    uint32_t* subObj = *(uint32_t**)(this + 0x0C);
    if (subObj) {
        releaseSubObject();                             // Pre-release step
        gDeallocFunc(subObj, 0x48);                     // Deallocate with custom function; 0x48 may be object size
        *(uint32_t**)(this + 0x0C) = nullptr;
    }

    // Destroy global manager singletons
    DESTROY_MANAGER(gManager1);
    DESTROY_MANAGER(gManager2);
    DESTROY_MANAGER(gManager3);
    DESTROY_MANAGER(gManager4);
    DESTROY_MANAGER(gManager5);
    DESTROY_MANAGER(gManager6);
    DESTROY_MANAGER(gManager7);
    DESTROY_MANAGER(gManager8);
    DESTROY_MANAGER(gManager9);
    DESTROY_MANAGER(gManager10);
}