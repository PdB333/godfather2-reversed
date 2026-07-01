// Xbox PDB: void __cdecl AptInitialize(void)
// FUNC_NAME: Apt::init
// Function address: 0x0059d000
// Initializes the Apt (Flash UI) system: validates function pointers, allocates global structures, sets up pool.

#include <cstdlib>

// Forward declarations of external globals and functions
extern int gAptIsInitialized;          // DAT_012055b0
extern int gAptPoolInitialized;        // DAT_0119a9cc
extern int* gAptSharedPtr;             // DAT_0119a9c8
extern int* gAptListHead;              // DAT_0119caec
extern int gAptPoolMem;                // DAT_0119cae4

extern void* (*gAptMemAlloc)(int size, int flags);  // DAT_0119caf0
extern void* (*gAptMemFree)(void* ptr);              // DAT_0119caf4
extern int (*gAptAssertFailHandler)(const char* expr, const char* file, int line, int level, bool* flag); // from FS
extern void (*gAptDefaultDebugPrint)(const char*);   // &LAB_0059cff0

extern void AptInitSubsystem();                       // FUN_005a9c40
extern void AptPoolConstructor(void* mem);             // FUN_005a0f70
extern int  AptMainPoolConstructor(void* mem);         // FUN_005a5b70 (returns pointer)

// Assert macro matching decompiled pattern
#define APT_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            static bool s_alreadyAsserted = false; \
            if (s_alreadyAsserted) { \
                /* Skip repeated assertion */ \
            } else { \
                void* fsHandler = *(void**)(__readfsdword(0x2c) + 0x30); \
                if (fsHandler) { \
                    int (*handler)(const char**, const char*) = *(int(**)(const char**, const char*))(*(int*)fsHandler + 8); \
                    const char* expr = message; \
                    handler(&expr, expr); \
                } else { \
                    (*(void(*)())swi(3))(); \
                } \
            } \
            __debugbreak(); \
        } \
    } while(0)

void Apt::init()
{
    // Ensure not already initialized
    APT_ASSERT(!gAptIsInitialized, "!bAptIsInitialized");

    // Validate all required function pointers
    APT_ASSERT(gAptAssertFailHandler, "gAptFuncs.pfnAssertFail");
    APT_ASSERT(gAptMemAlloc,          "gAptFuncs.pfnMemAlloc");
    APT_ASSERT(gAptMemFree,           "gAptFuncs.pfnMemFree");
    // (other validations omitted for brevity; in real code all ~30 fields checked)

    // Set default debug print if missing
    if (!gAptDefaultDebugPrint) {
        gAptDefaultDebugPrint = &defaultAptDebugPrint; // 0x0059cff0
    }

    // Initialize subsystem
    AptInitSubsystem();

    // Allocate small shared integer
    gAptSharedPtr = (int*)gAptMemAlloc(4, 0);
    if (gAptSharedPtr) {
        *gAptSharedPtr = 0;
    }

    // Allocate list head (24 bytes, 6 ints)
    gAptListHead = (int*)gAptMemAlloc(0x18, 0);
    if (gAptListHead) {
        gAptListHead[0] = 0;           // last
        gAptListHead[1] = 0;           // first
        gAptListHead[2] = 0;           // count
        gAptListHead[3] = (int)(gAptListHead + 4); // sentinel self-pointer
        gAptListHead[4] = 0;           // next
        gAptListHead[5] = 0;           // prev
    }

    // Allocate pool structure (0x4c bytes) and construct
    void* poolMem = gAptMemAlloc(0x4c, 0);
    if (poolMem) {
        AptPoolConstructor(poolMem);
        gAptPoolMem = (int)poolMem;
    } else {
        gAptPoolMem = 0;
    }

    // Assert pool not already allocated
    APT_ASSERT(gAptPoolInitialized == 0, "gpPool == 0");

    // Allocate main pool (0x3124 bytes) and construct
    void* mainPool = gAptMemAlloc(0x3124, 0);
    if (mainPool) {
        gAptPoolInitialized = AptMainPoolConstructor(mainPool);
    } else {
        gAptPoolInitialized = 0;
    }

    // Mark Apt as initialized
    gAptIsInitialized = 1;
}