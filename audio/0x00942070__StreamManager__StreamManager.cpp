// FUNC_NAME: StreamManager::StreamManager

/* 0x00942070 - Constructor for StreamManager (EA EARS engine)
 * Initializes a pool of 64 stream slots (each 0x80 bytes) with debug sentinel values,
 * allocates two textures, and sets up global configuration.
 */

#include <cstdint>

// Forward declarations
extern uint32_t DAT_00d8b2ac;
extern uint32_t DAT_00d8b2a8;
extern uint32_t DAT_00d8b2a4;
extern uint32_t DAT_00d5f378;
extern uint32_t DAT_00e446f4;
extern uint32_t DAT_00d8b2a0;
extern uint32_t DAT_00d8b29c;
extern uint32_t DAT_00d8b298;
extern uint32_t _DAT_00d5780c;
extern uint32_t DAT_00d75ca0;
extern uint32_t DAT_01218ea0;
extern uint32_t DAT_01218e80;

// Engine helper functions
void* getEngineInstance();
uint32_t getEnginePointerFrom(void*);
uint32_t createTexture(uint32_t width, uint32_t height, uint32_t usageFlags, uint32_t pool, uint32_t format, void* extra, uint32_t zero, uint32_t unk);

// Slot structure (0x80 bytes)
struct StreamSlot {
    uint32_t field00;          // +0x00: always zero
    uint8_t pad_04[0x68];      // +0x04: unused? (up to +0x6C)
    uint32_t sentinel1;        // +0x6C: debug sentinel (0xbadbadba)
    uint32_t sentinel2;        // +0x70: debug sentinel (0xbeefbeef)
    uint32_t sentinel3;        // +0x74: debug sentinel (0xeac15a55)
    uint32_t field78;          // +0x78: always zero
    uint32_t state;            // +0x7C: initialized to 2
};

// Size: 0x80 bytes

class StreamManager {
public:
    // vtable pointer at offset 0
    void* vtable;              // +0x00

    // Pool of 64 stream slots (size 0x80 each) starting at offset 4
    StreamSlot slots[64];      // +0x04, total 0x2000 bytes

    // Total size after slots: +0x2004

    // Texture handles (allocated via createTexture)
    uint32_t texture1;         // +0x2010 (offset 0x804 * 4)
    uint32_t texture2;         // +0x2014 (offset 0x805 * 4)

    // Configuration values from global data
    uint32_t config1;          // +0x800 (offset 0x200)
    uint32_t config2;          // +0x801
    uint32_t config3;          // +0x802
    uint32_t config4;          // +0x803
    uint32_t config5;          // +0x804
    uint32_t config6;          // +0x805
    uint32_t config7;          // +0x806

    // More fields at high offsets
    uint32_t field_0x2020;     // +0x2020 (offset 0x808 * 4)
    uint32_t field_0x2024;     // +0x2024 (offset 0x809 * 4)
    uint32_t field_0x2028;     // +0x2028 (offset 0x80a * 4)
    uint32_t field_0x202c;     // +0x202c (offset 0x80b * 4)
    uint32_t field_0x2030;     // +0x2030 (offset 0x80c * 4)
    uint32_t field_0x2034;     // +0x2034 (offset 0x80d * 4)
    uint32_t field_0x2038;     // +0x2038 (offset 0x80e * 4)
    uint32_t field_0x203c;     // +0x203c (offset 0x80f * 4)
    uint32_t field_0x2040;     // +0x2040 (offset 0x810 * 4)
    uint32_t field_0x2044;     // +0x2044 (offset 0x811 * 4)
    uint32_t field_0x2048;     // +0x2048 (offset 0x812 * 4)
    uint32_t field_0x204c;     // +0x204c (offset 0x813 * 4)
    uint32_t field_0x2050;     // +0x2050 (offset 0x814 * 4)
    uint32_t field_0x2054;     // +0x2054 (offset 0x815 * 4)
    uint32_t field_0x2058;     // +0x2058 (offset 0x816 * 4)
    uint32_t field_0x205c;     // +0x205c (offset 0x817 * 4)
    uint32_t field_0x2060;     // +0x2060 (offset 0x818 * 4)
    uint32_t field_0x2064;     // +0x2064 (offset 0x819 * 4)
    uint32_t field_0x2068;     // +0x2068 (offset 0x81a * 4)

    // Constructor (__thiscall)
    void __thiscall constructor();
};

void StreamManager::constructor() {
    // Initialize the slot pool (64 slots starting at this+4)
    for (int i = 0; i < 64; i++) {
        StreamSlot* slot = &slots[i];

        // Set debug sentinel values (then cleared below)
        slot->sentinel1 = 0xBADBADBA;
        slot->sentinel2 = 0xBEEFBEEF;
        slot->sentinel3 = 0xEAC15A55;

        // Clear first field and zero sentinels
        slot->field00 = 0;
        slot->field78 = 0;
        slot->sentinel1 = 0;
        slot->sentinel2 = 0;
        slot->sentinel3 = 0;

        // Set state to 2 (active? used?)
        slot->state = 2;
    }

    // Store global configuration values at high offsets
    field_0x2024 = DAT_00d8b2ac;
    field_0x2028 = DAT_00d8b2ac;   // Note: actually uVar6 = DAT_00d8b2ac from earlier; same value
    field_0x202c = DAT_00d8b2a4;
    field_0x2030 = DAT_00d5f378;
    field_0x2034 = DAT_00e446f4;
    field_0x2038 = 0;
    field_0x203c = DAT_00d8b2a0;
    field_0x2040 = DAT_00d8b29c;
    field_0x2044 = DAT_00d8b298;

    // Note: order of assignments may vary; we follow the decompiled sequence
    // Temporaries for clarity
    uint32_t uVar6 = DAT_00d8b2ac;
    uint32_t uVar5 = DAT_00d8b2a8;

    field_0x204c = uVar5;
    field_0x2048 = _DAT_00d5780c;
    field_0x2050 = DAT_00d75ca0;
    field_0x2054 = _DAT_00d5780c;

    // Clear config7
    field_0x2058 = 0; // actually config7? offset 0x806*4 = +0x2018

    // Set vtable pointer
    vtable = getEngineInstance(); // FUN_00434cc0

    // Obtain renderer/engine objects for texture creation
    void* engineObj1 = getEnginePointerFrom(getEngineInstance()); // chain: FUN_0060d860 -> FUN_00606370 -> deref +8
    uint32_t textureWidth; // from initial size calculation
    // Get width from some global object
    void* objA = DAT_01218ea0;
    void* objB = DAT_01218e80;
    // More engine object access for size
    uint32_t width = *(uint16_t*)((uint8_t*)getEnginePointerFrom(DAT_01218ea0) + 4) >> 1;

    // Allocate two textures
    texture1 = createTexture(engineObj1, 0x200098, width, width, 1, objB, 0, 0xFFFFFFFF);   // param order from call
    texture2 = createTexture(/*engineObj2*/ engineObj2, 0x40200098, width, width, 1, objA, 0, 0xFFFFFFFF); // second call

    // Initialize remaining fields to -1 or 0
    field_0x2058 = 0xFFFFFFFF;   // +0x816
    field_0x205c = 0xFFFFFFFF;   // +0x817
    field_0x2064 = 0xFFFFFFFF;   // +0x819
    field_0x2068 = 0xFFFFFFFF;   // +0x81a
    field_0x2060 = 0;            // +0x808
    config7 = 0;                 // +0x807? Actually offset 0x807 *4 = +0x201c, but we have field_0x2058 at +0x2018; need to check ordering
    // The decompiled set param_1[0x806]=0, param_1[0x807]=0, param_1[0x808]=0, param_1[0x818]=0.
    // We'll map as:
    config6 = 0;                 // +0x806*4 = +0x2018
    config5 = 0;                 // +0x807*4 = +0x201c?
    config4 = 0;                 // +0x808*4 = +0x2020
    field_0x2060 = 0;            // +0x818*4 = +0x2060
}