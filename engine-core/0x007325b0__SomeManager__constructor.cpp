// FUNC_NAME: SomeManager::constructor
// Constructor for a manager object. Zero-initializes members, copies a global reference, and performs singleton registration.
// Likely part of EARS engine manager hierarchy. Offsets: +0x00 to +0x44 zeroed, +0x2c set to g_someGlobal, +0x48 initialized to 0.
// Additional sub-object cleanup at +0x34 if already allocated.

#include <cstdint>

class SomeManager {
public:
    void* vtable;  // +0x00 (not explicitly set here, may be set by caller)
    // Many fields follow, up to offset 0x120+
    // Offsets based on param_1 indices:
    // +0x00 to +0x28: zeroed (indices 0-9)
    // +0x2c: g_someGlobal (index 0xb)
    // +0x30: zeroed (index 0xc)
    // +0x34: pointer to sub-object (index 0xd)
    // +0x38 to +0x44: zeroed (indices 0xe-0x10)
    // +0x48: zeroed (index 0x11)
    // +0x4c to +0x58: zeroed (indices 0x12-0x15)
    // +0x5c: zeroed (index 0x16)
    // +0x120: zeroed (index 0x48)

    // Constructor
    void* __fastcall constructor(void* thisPtr) {
        uint32_t* obj = static_cast<uint32_t*>(thisPtr);

        // Zero-initialize indices 0 through 10 (offsets +0x00 to +0x28)
        obj[0] = 0;
        obj[1] = 0;
        obj[2] = 0;
        obj[3] = 0;
        obj[4] = 0;
        obj[5] = 0;
        obj[6] = 0;
        obj[7] = 0;
        obj[8] = 0;
        obj[9] = 0;
        obj[10] = 0;

        // Set index 11 (+0x2c) from global value (likely a singleton pointer or constant)
        obj[0xb] = g_someGlobal;  // DAT_00d5ccf8

        // Zero index 12 (+0x30)
        obj[0xc] = 0;

        // Check if sub-object pointer at +0x34 (index 13) is non-null; if so, destroy it
        uint32_t* subObjPtr = &obj[0xd];
        if (*subObjPtr != 0) {
            // Call destructor on the sub-object
            SomeSubObject::destructor(subObjPtr);  // FUN_004daf90
            *subObjPtr = 0;
        }

        // Register this manager? The argument 1 might indicate a type or mode
        registerManagerWithSystem(1);  // FUN_0072d9e0

        // Zero indices 0x12 through 0x16 (+0x48 to +0x58) and additional fields
        obj[0x12] = 0;  // +0x48
        obj[0x13] = 0;  // +0x4c
        obj[0x14] = 0;  // +0x50
        obj[0x15] = 0;  // +0x54
        obj[0x16] = 0;  // +0x58

        // Call a static initialization routine
        staticInit();  // FUN_007324d0

        // Zero a field at offset +0x120 (index 0x48)
        obj[0x48] = 0;

        return thisPtr;
    }

private:
    static void registerManagerWithSystem(int type);  // FUN_0072d9e0
    static void staticInit();                          // FUN_007324d0
};

// Global variable referenced
extern uint32_t g_someGlobal;  // DAT_00d5ccf8

// Sub-object destructor (forward declaration)
namespace {
    void destructSubObject(uint32_t* ptr);  // FUN_004daf90
}