// FUNC_NAME: PauseMapManager::create (placement new)
#include <cstdint>
#include <cstring>

// Forward declarations for external functions used
namespace EARS {
    namespace MessageSystem {
        // Retrieves a message ID from a string name. Returns 0 if not found.
        uint32_t findMessageId(const char* name);

        // Subscribes a subscriber object (interface at offset 4) to a message.
        // Flags (0x8000) likely indicate persistent or high-priority subscription.
        void subscribe(void* subscriber, uint32_t messageId, uint32_t flags);
    }
}

// External globals from the binary
extern uint32_t g_unkGlobal1;           // _DAT_00d5780c
extern PauseMapManager* g_pPauseMapManager; // DAT_0112991c
extern uint32_t g_someMessageId;        // DAT_012069c4 (pre‑existing message pointer)
extern uint32_t g_iMsgEnteredPauseMap;  // DAT_011302b8 (will hold message id)
extern uint32_t g_iMsgExitedPauseMap;   // DAT_01130248

// Vtable symbols (void* to prevent automatic initialization)
extern void* g_vtablePauseMapManager;   // &PTR_FUN_00d6f4f8
extern void* g_vtableSubscriber;        // &PTR_LAB_00d6f4e8 (interface vtable)

// Size and layout per analysis:
// Offset 0x00: vtable pointer (PauseMapManager)
// Offset 0x04: vtable pointer (IMessageSubscriber interface)
// Offset 0x08: uint32_t enabled (1)
// Offset 0x0C: uint32_t someFlag (0)
// Offset 0x10: bool8 bool1 (0)
// Offset 0x11: bool8 bool2 (0)
// Offset 0x14–0x28: misc zeros (8 uint32s)
// Offset 0x34, 0x4C, 0x5C, 0x6C: uint32_t fields (all 0)
// Offset 0x7C: uint32_t storedGlobal (copied from g_unkGlobal1)
// Offset 0x80, 0x84, 0x88: uint32_t zeros
// Offset 0x20: uint32_t flags (ORed with 0x3080)

struct PauseMapManager {
    void* vtable;           // +0x00
    void* subscriberVtable; // +0x04

    // Fields initialized in constructor
    uint32_t enabled;       // +0x08 = 1
    uint32_t someFlag;      // +0x0C = 0
    uint8_t bool1;          // +0x10 = 0
    uint8_t bool2;          // +0x11 = 0
    // 0x14..0x28: uint32_t zero[6] (from param_1[5]..param_1[10])
    uint32_t zeroA;         // +0x14
    uint32_t zeroB;         // +0x18
    uint32_t zeroC;         // +0x1C
    uint32_t flags;         // +0x20 (ORed with 0x3080)
    uint32_t zeroD;         // +0x24
    uint32_t zeroE;         // +0x28
    // +0x2C..+0x30: padding/unused (two more uint32 from param_1[11], [12]? but not set)
    uint32_t field34;       // +0x34 (param_1[0xd])
    // ... (multiple fields follow, not all named)
    uint32_t field4C;       // +0x4C (param_1[0x13])
    uint32_t field5C;       // +0x5C (param_1[0x17])
    uint32_t field6C;       // +0x6C (param_1[0x1b])
    uint32_t storedGlobal;  // +0x7C (param_1[0x1f])
    uint32_t field80;       // +0x80 (param_1[0x20])
    uint32_t field84;       // +0x84 (param_1[0x21])
    uint32_t field88;       // +0x88 (param_1[0x22])
};

// __fastcall: ECX = pThis (the only parameter)
PauseMapManager* __fastcall PauseMapManager_create(PauseMapManager* pThis) {
    // Store the global pointer (singleton)
    g_pPauseMapManager = pThis;

    // Set vtable pointers
    pThis->subscriberVtable = &g_vtableSubscriber;   // Overwritten later by second vtable set
    pThis->enabled = 1;
    pThis->someFlag = 0;

    // Set main vtable and correct subscriber vtable
    pThis->vtable = &g_vtablePauseMapManager;       // *param_1 = &PTR_FUN_00d6f4f8
    pThis->subscriberVtable = &g_vtableSubscriber;  // param_1[1] = &PTR_LAB_00d6f4e8

    // Bool fields
    pThis->bool1 = 0;   // +0x10
    pThis->bool2 = 0;   // +0x11

    // Zero fields at various offsets
    pThis->zeroA = 0;   // param_1[5]
    pThis->zeroB = 0;   // param_1[6]
    pThis->zeroC = 0;   // param_1[7]
    pThis->zeroD = 0;   // param_1[9]
    pThis->zeroE = 0;   // param_1[10]
    pThis->field34 = 0; // param_1[0xd] (13)
    pThis->field4C = 0; // param_1[0x13] (19)
    pThis->field5C = 0; // param_1[0x17] (23)
    pThis->field6C = 0; // param_1[0x1b] (27)
    pThis->storedGlobal = g_unkGlobal1; // param_1[0x1f] (31)
    pThis->field80 = 0; // param_1[0x20] (32)
    pThis->field84 = 0; // param_1[0x21] (33)
    pThis->field88 = 0; // param_1[0x22] (34)

    // Set flags (OR with 0x3080 = 12416 decimal)
    pThis->flags |= 0x3080; // param_1[8] |= 0x3080

    // If there is a pre‑existing message ID, subscribe to it
    if (g_someMessageId != 0) {
        EARS::MessageSystem::subscribe(&pThis->subscriberVtable, &g_someMessageId, 0x8000);
    }

    // Retrieve message IDs for PauseMap events
    g_iMsgEnteredPauseMap = EARS::MessageSystem::findMessageId("iMsgEnteredPauseMap");
    g_iMsgExitedPauseMap = EARS::MessageSystem::findMessageId("iMsgExitedPauseMap");

    // Subscribe to both messages if they exist
    if (g_iMsgEnteredPauseMap != 0) {
        EARS::MessageSystem::subscribe(&pThis->subscriberVtable, &g_iMsgEnteredPauseMap, 0x8000);
    }
    if (g_iMsgExitedPauseMap != 0) {
        EARS::MessageSystem::subscribe(&pThis->subscriberVtable, &g_iMsgExitedPauseMap, 0x8000);
    }

    return pThis;
}