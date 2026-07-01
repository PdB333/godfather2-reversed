// FUNC_NAME: GameObject::resetState
// Function address: 0x00839310
// Purpose: Resets game object state, clears timers, initializes sub-objects, and releases a reference.

#include <cstdint>

class GameObject {
    // +0x94: possibly a pointer or handle (smart pointer)
    // +0xe4: flag (bool/int)
    // +0xec, +0xf0, +0xf4: unused/timer counters
    // +0x100: sub-object (e.g., transform or physics state)
    // +0x110: 64-bit value (double or timer)
    // +0x118: integer (e.g., some ID)
    // ... other fields
};

// External global references
extern uint32_t _DAT_00d5780c;  // a constant or global value
extern void* DAT_012233a0;      // pointer to a global data structure

// Forward declarations of internal helper functions
void __fastcall resetTimers(GameObject* obj);                  // FUN_00838cf0
void __fastcall initSubObject(void* dest, void* src);          // FUN_0056cef0
void __fastcall debugRender(GameObject* obj, uint32_t flags);  // FUN_0079e3c0
void __fastcall someOtherInit(GameObject* obj);                // FUN_00838170
void __fastcall releaseHandle(void* handle, int flags);        // FUN_00408a00

void __thiscall GameObject::reset(GameObject* this) {
    // Temporary structures for sub-object initialization
    struct SubObjectData {
        uint32_t member_0;   // local_50
        uint32_t member_4;   // local_4c
        uint32_t member_8;   // local_48
        uint32_t member_c;   // local_40
        uint32_t member_10;  // local_3c
        uint32_t member_14;  // local_38
        uint32_t member_18;  // local_30
        uint32_t member_1c;  // local_2c
        uint32_t member_20;  // local_28
    } subData;  // aligned on stack

    struct DebugData {
        uint32_t d0;  // local_90
        uint32_t d4;  // local_8c
        uint32_t d8;  // local_88
        uint32_t dc;  // local_80
        uint32_t e0;  // local_7c
        uint32_t e4;  // local_78
        uint32_t e8;  // local_70
        uint32_t ec;  // local_6c
        uint32_t f0;  // local_68
    } debugData;

    // Temporary handle for cleanup
    struct Handle {
        uint32_t value;   // local_9c
        uint32_t pad;     // local_98 (zero)
        uint8_t extra;    // local_94 (zero)
    } handleCopy;  // total 9 bytes

    // Step 1: set active flag
    *(uint32_t*)((uint8_t*)this + 0xe4) = 1;

    // Step 2: reset sub-timers/state
    resetTimers(this);

    // Step 3: clear additional fields
    *(uint32_t*)((uint8_t*)this + 0xec) = 0;
    *(uint32_t*)((uint8_t*)this + 0xf0) = 0;
    *(uint32_t*)((uint8_t*)this + 0xf4) = 0;

    // Step 4: initialize sub-object at offset 0x100 using stack data
    initSubObject((uint8_t*)this + 0x100, &subData);

    // Step 5: copy subData into debugData (for optional debug rendering)
    debugData.d0 = subData.member_0;
    debugData.d4 = subData.member_4;
    debugData.d8 = subData.member_8;
    debugData.dc = subData.member_c;
    debugData.e0 = subData.member_10;
    debugData.e4 = subData.member_14;
    debugData.e8 = subData.member_18;
    debugData.ec = subData.member_1c;
    debugData.f0 = subData.member_20;

    // Step 6: read 64-bit value from +0x110 into local_60 (not used further?)
    // local_60 = *(uint64_t*)((uint8_t*)this + 0x110); // but not stored

    // Step 7: if debug condition met, render debugging shape
    if (*(int**)(*(uint32_t*)DAT_012233a0 + 4) != 0 &&
        *(int**)(*(uint32_t*)DAT_012233a0 + 4) != (int*)0x1f30) {
        debugRender(this, 0x800, 0, 0);
    }

    // Step 8: miscellaneous initialization
    someOtherInit(this);

    // Step 9: release a handle stored at +0x94
    handleCopy.value = *(uint32_t*)((uint8_t*)this + 0x94);
    handleCopy.pad = 0;
    handleCopy.extra = 0;
    releaseHandle(&handleCopy, 0);
}