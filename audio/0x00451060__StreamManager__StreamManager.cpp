// FUNC_NAME: StreamManager::StreamManager

#include <cstdint>

// Forward declarations for external engine functions
uint32_t registerMessageType(const char* name);
void subscribeToMessage(uint32_t* globalHandle, uint32_t messageId);

// Global singleton pointer
extern StreamManager* g_pStreamManager;

// Vtable pointers (defined elsewhere)
extern void* VTABLE_StreamManager_v1;  // 0x00e316d8
extern void* VTABLE_StreamManager_v2;  // 0x00e2f19c
extern void* VTABLE_StreamManager_v2b; // 0x00e316dc

struct StreamManager {
    void** vtable1;      // +0x00: vtable for primary class
    void** vtable2;      // +0x04: vtable for base/mixin
    int32_t field_8;     // +0x08: initialization flag (set to 1)
    int32_t field_0C;    // +0x0C: some state counter (0)
    int32_t field_10;    // +0x10: unused/zero
    int32_t field_14;    // +0x14: unused/zero
    int32_t field_18;    // +0x18: unused/zero
    uint8_t field_1C;    // +0x1C: flag byte (0)
};

// Extern globals for message sink handles
extern uint32_t DAT_0120e970;  // sink for "iMsgStreamSetLoadComplete"
extern uint32_t DAT_0120e960;  // sink for "iMsgStreamSetLoadCancel"

// __fastcall: this pointer passed in ECX
StreamManager* __fastcall StreamManager_constructor(StreamManager* this_ptr)
{
    // Store this as the global singleton
    g_pStreamManager = this_ptr;

    // Initialize vtable pointers
    this_ptr->vtable2 = &VTABLE_StreamManager_v2;   // +0x04
    this_ptr->field_8 = 1;                          // +0x08: set to 1
    this_ptr->field_0C = 0;                         // +0x0C

    // Set primary vtable (overwrites second vtable?)
    this_ptr->vtable1 = &VTABLE_StreamManager_v1;   // +0x00
    this_ptr->vtable2 = &VTABLE_StreamManager_v2b;  // +0x04: re-assigned

    // Clear remaining fields
    this_ptr->field_10 = 0;                         // +0x10
    this_ptr->field_14 = 0;                         // +0x14
    this_ptr->field_18 = 0;                         // +0x18
    this_ptr->field_1C = 0;                         // +0x1C (byte)

    // Register message handlers for stream loading events
    uint32_t msgStreamLoadComplete = registerMessageType("iMsgStreamSetLoadComplete");
    subscribeToMessage(&DAT_0120e970, msgStreamLoadComplete);

    uint32_t msgStreamLoadCancel = registerMessageType("iMsgStreamSetLoadCancel");
    subscribeToMessage(&DAT_0120e960, msgStreamLoadCancel);

    return this_ptr;
}