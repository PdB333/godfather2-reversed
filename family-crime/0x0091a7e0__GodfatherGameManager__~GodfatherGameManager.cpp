// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Address: 0x0091a7e0
// Destructor for GodfatherGameManager, cleans up all subsystems and global entity lists

#include <cstdint>

class GodfatherGameManager {
public:
    // vtable pointers at various offsets for multiple inheritance
    // +0x00: main vtable
    // +0x04: secondary vtable
    // +0x4C (0x13*4): tertiary vtable
    void* vtable_main;                 // +0x00
    void* vtable_secondary;            // +0x04
    // ... other members ...
    void* memberAt0x27;                // +0x9C (0x27*4) - released later
    void* memberAt0x2A;                // +0xA8 (0x2A*4)
    void* memberAt0x31;                // +0xC4 (0x31*4) - released early
    void* memberAt0x33;                // +0xCC (0x33*4)
    void* memberAt0x3A;                // +0xE8 (0x3A*4)
    void* memberArray[7];              // +0xF0 (0x3C*4) - 7 elements, released in loop
    // ... additional members ...

    // Global entity lists (likely for different types: e.g., AI agents, vehicles, etc.)
    // These are static/global variables, not members
    static int g_objectCount1;         // DAT_00e54cd8
    static int** g_objectArray1;       // DAT_00e54cd4 (array of pointers to objects)
    static int g_objectCount2;         // DAT_00e54ce4
    static int** g_objectArray2;       // DAT_00e54ce0
    static int g_objectCount3;         // DAT_00e54cf0
    static int** g_objectArray3;       // DAT_00e54cec
    static int g_objectCount4;         // DAT_00e54cfc
    static int** g_objectArray4;       // DAT_00e54cf8
    static void* g_someOtherPointer;   // DAT_00e54d04

    // External functions (provided by engine)
    static void finalizationUpdate();  // FUN_005c16e0
    static void releaseObject(int* obj); // FUN_009c8eb0 - calls vtable[3] destructor and frees memory
    static void freeMemory(void* ptr); // FUN_009c8f10 - frees a block

    // Constructor-like setup (not shown, but initializes vtable)
    GodfatherGameManager();

    // Destructor
    ~GodfatherGameManager() noexcept {
        // Set vtable pointers for destruction context
        vtable_main = (void*)&PTR_FUN_00d85838;
        vtable_secondary = (void*)&PTR_LAB_00d85810;
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + 0x4C) = (void*)&PTR_LAB_00d8580c; // this[0x13]

        // Release internal member objects
        freeMemory(memberAt0x31);
        freeMemory(memberAt0x3A);
        freeMemory(memberAt0x33);
        for (int i = 0; i < 7; i++) {
            freeMemory(memberArray[i]);
        }

        // Clean up global entity list 1
        if (g_objectCount1 != 0) {
            for (uint32_t idx = 0; idx < g_objectCount1; idx++) {
                int* obj = g_objectArray1[idx];
                if (obj != nullptr) {
                    if (obj[0] != 0) { // vtable check
                        // Call virtual destructor via vtable[3]
                        (*(void (*)(int*))obj[3])(obj);
                    }
                    releaseObject(obj);
                }
            }
        }
        g_objectCount1 = 0;
        freeMemory(g_objectArray1);
        g_objectArray1 = nullptr;
        g_objectCount2 = 0; // _DAT_00e54cdc is set to 0 (maybe another count)

        // Clean up global entity list 2
        if (g_objectCount2 != 0) {
            for (uint32_t idx = 0; idx < g_objectCount2; idx++) {
                int* obj = g_objectArray2[idx];
                if (obj != nullptr) {
                    if (obj[0] != 0) {
                        (*(void (*)(int*))obj[3])(obj);
                    }
                    releaseObject(obj);
                }
            }
        }
        g_objectCount2 = 0;
        freeMemory(g_objectArray2);
        g_objectArray2 = nullptr;
        g_objectCount3 = 0; // _DAT_00e54ce8

        // Clean up global entity list 3
        if (g_objectCount3 != 0) {
            for (uint32_t idx = 0; idx < g_objectCount3; idx++) {
                int* obj = g_objectArray3[idx];
                if (obj != nullptr) {
                    if (obj[0] != 0) {
                        (*(void (*)(int*))obj[3])(obj);
                    }
                    releaseObject(obj);
                }
            }
        }
        g_objectCount3 = 0;
        freeMemory(g_objectArray3);
        g_objectArray3 = nullptr;
        g_objectCount4 = 0; // _DAT_00e54cf4

        // Clean up global entity list 4
        if (g_objectCount4 != 0) {
            for (uint32_t idx = 0; idx < g_objectCount4; idx++) {
                int* obj = g_objectArray4[idx];
                if (obj != nullptr) {
                    if (obj[0] != 0) {
                        (*(void (*)(int*))obj[3])(obj);
                    }
                    releaseObject(obj);
                }
            }
        }
        g_objectCount4 = 0;
        freeMemory(g_objectArray4);
        g_objectArray4 = nullptr;
        g_objectCount1 = 0; // _DAT_00e54d00 (maybe another count)

        // Clean up extra global pointer
        if (g_someOtherPointer != nullptr) {
            freeMemory(g_someOtherPointer);
        }
        g_someOtherPointer = nullptr;

        // Release remaining member objects
        if (memberAt0x2A != nullptr) { // offset 0x2A
            freeMemory(memberAt0x2A);
        }
        if (memberAt0x27 != nullptr) { // offset 0x27
            freeMemory(memberAt0x27);
        }

        // Finalization step
        finalizationUpdate();
        // Switch to base class vtable
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + 0x4C) = (void*)&PTR_LAB_00d851ec;
        g_globalFlag = 0; // DAT_01130044

        finalizationUpdate();
    }
};

// Static globals (external definitions)
int GodfatherGameManager::g_objectCount1 = 0; // DAT_00e54cd8
int** GodfatherGameManager::g_objectArray1 = nullptr; // DAT_00e54cd4
int GodfatherGameManager::g_objectCount2 = 0; // DAT_00e54ce4
int** GodfatherGameManager::g_objectArray2 = nullptr; // DAT_00e54ce0
int GodfatherGameManager::g_objectCount3 = 0; // DAT_00e54cf0
int** GodfatherGameManager::g_objectArray3 = nullptr; // DAT_00e54cec
int GodfatherGameManager::g_objectCount4 = 0; // DAT_00e54cfc
int** GodfatherGameManager::g_objectArray4 = nullptr; // DAT_00e54cf8
void* GodfatherGameManager::g_someOtherPointer = nullptr; // DAT_00e54d04
int g_globalFlag = 0; // DAT_01130044

// External function implementations (stubs - actual addresses in binary)
void GodfatherGameManager::finalizationUpdate() { /* FUN_005c16e0 */ }
void GodfatherGameManager::releaseObject(int* obj) { /* FUN_009c8eb0 */ }
void GodfatherGameManager::freeMemory(void* ptr) { /* FUN_009c8f10 */ }