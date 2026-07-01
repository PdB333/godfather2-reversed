// Xbox PDB: EARS_Modules_GameplayTracking_GameplayTracking
// FUNC_NAME: GamePlayLogging::constructor (0x008d2110)
// This function initializes the singleton GamePlayLogging object, sets up its vtable,
// registers for the "iMsgGameplayTrackingComputed" message, and attaches data buffers.
// It is called once during game initialization.

#include <cstdint>

// Forward declarations for known functions
extern void sub_8d5d00(); // initializes some internal state (called multiple times)
extern void sub_8d5df0(); // another initialization

// Message registration: registers an object to receive a message string
extern void RegisterForMessage(void* receiver, const char* messageName);

// Attaches a data buffer to an object (size 0x8000)
extern void AttachDataBuffer(void* obj, void** bufferPtr, uint32_t bufferSize);

// Global singleton pointer for GamePlayLogging
extern GamePlayLogging* g_gameplayLogging;

// External data symbols (from Ghidra)
extern uint32_t DAT_00d5ef50; // some initial value
extern uint32_t _DAT_00d5780c; // another initial value
extern uint32_t DAT_012069d4; // pointer to buffer (non-zero if allocated)
extern uint32_t DAT_0112b36c; // pointer to buffer (non-zero if allocated)

// Vtable pointers (pointers to arrays of function pointers)
extern void* PTR_FUN_00d7d394; // primary vtable
extern void* PTR_LAB_00d7d38c; // secondary vtable (initially)
extern void* PTR_LAB_00d7d390; // secondary vtable (final)

// Message receiver object (global)
extern SomeReceiverObject DAT_0112f9c0;

class GamePlayLogging {
public:
    // Vtable pointer at +0x00
    void** vtable;

    // +0x04
    int field_04;
    // +0x08
    int field_08;
    // +0x0C
    void* secondaryVtable;
    // +0x10
    uint32_t field_10;
    // +0x14
    int field_14;
    // +0x58
    uint32_t field_58;
    // +0x70
    uint32_t field_70;
    // ... other fields

    // Constructor (__thiscall)
    __thiscall GamePlayLogging* constructor() {
        uint32_t uVar1 = DAT_00d5ef50; // some initial value

        field_04 = 1;
        field_08 = 0;
        secondaryVtable = &PTR_LAB_00d7d38c; // initial secondary vtable
        g_gameplayLogging = this; // store global singleton
        field_10 = uVar1;
        vtable = &PTR_FUN_00d7d394; // primary vtable
        secondaryVtable = &PTR_LAB_00d7d390; // update secondary vtable
        field_14 = 0;

        // Initialize some internal objects (called three times)
        sub_8d5d00();
        sub_8d5d00();
        sub_8d5d00();

        field_58 = _DAT_00d5780c;

        sub_8d5d00(); // additional initialization

        field_70 = _DAT_00d5780c;

        sub_8d5df0(); // final initialization

        // Register this object to receive "iMsgGameplayTrackingComputed" messages
        RegisterForMessage(&DAT_0112f9c0, "iMsgGameplayTrackingComputed");

        // Attach data buffers (if they exist)
        if (DAT_012069d4 != 0) {
            AttachDataBuffer(this, &DAT_012069d4, 0x8000);
        }
        if (DAT_0112b36c != 0) {
            AttachDataBuffer(this, &DAT_0112b36c, 0x8000);
        }

        return this;
    }
};