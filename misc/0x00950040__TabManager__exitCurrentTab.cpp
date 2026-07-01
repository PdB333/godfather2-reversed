// FUNC_NAME: TabManager::exitCurrentTab

// Reconstructed from 0x00950040 - Handles exiting the current tab by updating index and state, removing callbacks.
// Assumes class TabManager with fields:
//   +0x14: list of registered callbacks/handlers (likely a linked list or array)
//   +0x50: currentTabIndex (int)
//   +0x54: currentTabState (int)
// Global arrays: tabCount (DAT_00e57394), tabStateTable (DAT_00e5738c)
// Global objects: gSomeSingleton1 (DAT_011304fc), gSomeSingleton2 (DAT_01130000)
//   These singletons have a vtable method at +0x2c (likely "onTabExit" or "notifyTabChange")

#include <cstdint>

// Forward declarations for called functions
void FUN_00408a00(void* param_1, int param_2);
void FUN_005a04a0(const char* string, int zero, const char* label, int zero2);
void FUN_005c0d50(void* list, void* callbackPtr, int zero);

// Global variables (addresses from Ghidra)
extern int tabCount;               // DAT_00e57394
extern int tabStateTable[];        // DAT_00e5738c - indexed by tab index
extern void* gSingletonA;          // DAT_011304fc
extern void* gSingletonB;          // DAT_01130000
extern const char* exitTabLabel;   // DAT_00d8bb90

struct TabManager {
    // +0x14: list of callbacks (type unknown, likely a custom linked list of handler structs)
    // We'll treat it as an opaque pointer for now
    void* callbackList; // +0x14

    int currentTabIndex; // +0x50
    int currentTabState; // +0x54

    void exitCurrentTab(int delta);
};

void __thiscall TabManager::exitCurrentTab(int delta) {
    // Local struct used for some initialization (maybe a temporary context or stack vars)
    struct TempVars {
        uint32_t var0; // corresponds to local_c
        uint32_t var1; // corresponds to local_8
        uint8_t var2;  // corresponds to local_4
    } temp;
    // Initialize from global data
    temp.var0 = *(uint32_t*)(0x011302e8);
    temp.var1 = 0;
    temp.var2 = 0;
    FUN_00408a00(&temp, 0);  // Unclear initialization call

    void* singletonPtr;
    if (currentTabState == 0) {
        singletonPtr = gSingletonA; // DAT_011304fc
    } else {
        if (currentTabState != 1) {
            goto SKIP_NOTIFY;
        }
        singletonPtr = gSingletonB; // DAT_01130000
    }
    // Call a vtable method at offset 0x2c on the singleton
    (*(void (**)(void))(*(uint32_t*)singletonPtr + 0x2c))();

SKIP_NOTIFY:
    // Log "ExitTab" with a label
    FUN_005a04a0("ExitTab", 0, exitTabLabel, 0);

    // Update the tab index by adding delta, wrap around modulo tabCount
    currentTabIndex = (currentTabIndex + delta) % tabCount;

    // Retrieve the new state from the state table
    currentTabState = tabStateTable[currentTabIndex];

    // Remove three callbacks from the callback list at +0x14
    void* list = &callbackList;  // +0x14
    FUN_005c0d50(list, (void*)0x005bfc10, 0);
    FUN_005c0d50(list, (void*)0x0094fea0, 0);
    FUN_005c0d50(list, (void*)0x005bfbe0, 0);
}