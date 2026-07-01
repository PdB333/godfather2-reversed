// FUNC_NAME: GlobalStateManager::Constructor
#include <cstdint>

// Forward declarations of external functions (unknown names)
extern void someInitFunction(void* global);
extern void anotherInitFunction(void* global);
extern void finalInitFunction();

// Global data references (static members of class or external)
extern uint32_t g_someGlobal1;   // +0x0000
extern uint32_t g_someGlobal2;   // +0x0004
extern uint32_t g_someGlobal3;   // +0x0008
extern uint32_t g_someGlobal4;   // +0x000C
extern uint32_t g_someGlobal5;   // +0x0010
extern uint32_t g_someGlobal6;   // +0x0014
extern uint32_t g_someGlobal7;   // +0x0018
extern uint32_t g_someGlobal8;   // +0x001C
extern uint32_t g_initializedFlag; // +0x0000 (different address)

// Vtable pointers (likely from data section)
extern void* const VTABLE_BASE1;  // 0x00d74124
extern void* const VTABLE_BASE2;  // 0x00d74114
extern void* const VTABLE_DERIVED; // 0x00d74078

class GlobalStateManager {
public:
    // This constructor sets up base class vtables and initializes static members
    __fastcall GlobalStateManager() {
        // Set base class vtable pointers (two for multiple inheritance)
        this->vtable1 = &VTABLE_BASE1;   // +0x00
        this->vtable2 = &VTABLE_BASE2;   // +0x04

        // Initialize static member objects (likely memory pools, queues, etc.)
        someInitFunction(&g_someGlobal1);  // DAT_0112dc14
        anotherInitFunction(&g_someGlobal1); // DAT_0112dc14
        anotherInitFunction(&g_someGlobal2); // DAT_0112dc24
        anotherInitFunction(&g_someGlobal3); // DAT_0112dc2c
        anotherInitFunction(&g_someGlobal4); // DAT_0112dc0c
        anotherInitFunction(&g_someGlobal5); // DAT_0112dc34
        anotherInitFunction(&g_someGlobal6); // DAT_0112dc00
        anotherInitFunction(&g_someGlobal7); // DAT_0112dc1c

        // Another global object
        someInitFunction(&g_someGlobal8);  // DAT_012069c4

        // Perform final initialization (e.g., create subsystems)
        finalInitFunction();

        // Overwrite vtable pointer to derived class vtable
        this->vtable1 = &VTABLE_DERIVED;  // +0x00

        // Set global flag to indicate uninitialized / reset state
        g_initializedFlag = 0;            // _DAT_0112dbfc
    }

    // Member variables (first 8 bytes are vtables)
    void* vtable1;  // +0x00
    void* vtable2;  // +0x04
    // ... other members follow
};