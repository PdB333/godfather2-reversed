// FUNC_NAME: Sentient::Sentient(SentientInitData* initData)
// Address: 0x0070bae0
// Purpose: Constructor for Sentient class (base for Player/NPC). Initializes vtable pointers, debug sentinels, flags, and sub-objects.

#include <cstdint> // For fixed-size types if needed

// Forward declarations (actual class definitions not available)
struct SentientInitData;

// Sentinel values for memory corruption detection
static const uint32_t SENTINEL_DEADBEAF = 0xbadbadba;
static const uint32_t SENTINEL_5AE55A5C = 0xeac15a55;
static const uint32_t SENTINEL_FEEDBEEF = 0xbeefbeef;
static const uint32_t SENTINEL_91100911 = 0x91100911;

// Global data referenced
extern void* PTR_FUN_00d61640; // Main vtable
extern void* PTR_LAB_00d61630; // IFace vtable 1 (offset +0x3C)
extern void* PTR_LAB_00d6162c; // IFace vtable 2 (offset +0x48)
extern void* PTR_LAB_00d61628; // IFace vtable 3 (offset +0x50)
extern void* PTR_LAB_00d615c8; // IFace vtable 4 (offset +0x54)
extern void* PTR_LAB_00d61560; // IFace vtable 5 (offset +0x58)
extern uint32_t _DAT_00d5780c; // Some initial value
extern uint32_t DAT_00d5d7b8;
extern uint32_t DAT_00d61444;
extern uint32_t DAT_00e2e37c;
extern void* DAT_0112ac6c; // Data blob for copy
extern void* DAT_0112ac5c;
extern void* DAT_0112ac64;
extern void* DAT_0112b36c;

// External functions (simplified declarations)
extern void FUN_00708560(SentientInitData* initData); // Base class constructor
extern void FUN_004daf90(void* ptr); // Deallocate/free
extern void FUN_00408900(void* dst, void* src, uint32_t size); // Memory copy
extern void* FUN_009c8e50(uint32_t size); // Allocate
extern void* FUN_0084e6f0(Sentient* obj); // Initialize sub-object (returns pointer to allocated block)

class Sentient {
public:
    // Constructor
    void* __thiscall construct(SentientInitData* initData) {
        // Call base class constructor
        FUN_00708560(initData);

        // Set up vtable pointers (multiple inheritance)
        *(void**)this = &PTR_FUN_00d61640; // Main vtable

        // Interface vtable pointers (at specific offsets from this)
        *(void**)((uint8_t*)this + 0x3C) = &PTR_LAB_00d61630; // +0x3C
        *(void**)((uint8_t*)this + 0x48) = &PTR_LAB_00d6162c; // +0x48
        *(void**)((uint8_t*)this + 0x50) = &PTR_LAB_00d61628; // +0x50
        *(void**)((uint8_t*)this + 0x54) = &PTR_LAB_00d615c8; // +0x54
        *(void**)((uint8_t*)this + 0x58) = &PTR_LAB_00d61560; // +0x58

        // Initialize state fields
        // +0x2D0 (m_subObject?) = 0
        *(uint32_t*)((uint8_t*)this + 0x2D0) = 0; // param_1[0xb4]
        *(uint32_t*)((uint8_t*)this + 0x2D4) = 0; // param_1[0xb5]
        *(uint32_t*)((uint8_t*)this + 0x2D8) = 0; // param_1[0xb6]

        // Set debug sentinel values for corruption detection
        // +0x314, +0x31C, +0x318, +0x320
        *(uint32_t*)((uint8_t*)this + 0x314) = SENTINEL_DEADBEAF; // param_1[0xc5]
        *(uint32_t*)((uint8_t*)this + 0x31C) = SENTINEL_5AE55A5C; // param_1[199] (0xc7)
        *(uint32_t*)((uint8_t*)this + 0x318) = SENTINEL_FEEDBEEF; // param_1[0xc6]
        *(uint32_t*)((uint8_t*)this + 0x320) = SENTINEL_91100911; // param_1[200] (0xc8)

        // More sentinels at +0x324, +0x328, +0x32C, +0x330
        *(uint32_t*)((uint8_t*)this + 0x324) = SENTINEL_DEADBEAF; // param_1[0xc9]
        *(uint32_t*)((uint8_t*)this + 0x328) = SENTINEL_FEEDBEEF; // param_1[0xca]
        *(uint32_t*)((uint8_t*)this + 0x32C) = SENTINEL_5AE55A5C; // param_1[0xcb]
        *(uint32_t*)((uint8_t*)this + 0x330) = SENTINEL_91100911; // param_1[0xcc]

        // Other initializations
        *(uint32_t*)((uint8_t*)this + 0x334) = 0; // param_1[0xcd]
        *(uint32_t*)((uint8_t*)this + 0x344) = 0; // param_1[0xd1]
        *(uint32_t*)((uint8_t*)this + 0x348) = 0; // param_1[0xd2]
        *(uint32_t*)((uint8_t*)this + 0x34C) = 0; // param_1[0xd3]

        // +0x364 sentinels (again)
        *(uint32_t*)((uint8_t*)this + 0x364) = SENTINEL_DEADBEAF; // param_1[0xd9]
        *(uint32_t*)((uint8_t*)this + 0x368) = SENTINEL_FEEDBEEF; // param_1[0xda]
        *(uint32_t*)((uint8_t*)this + 0x36C) = SENTINEL_5AE55A5C; // param_1[0xdb]
        *(uint32_t*)((uint8_t*)this + 0x370) = SENTINEL_91100911; // param_1[0xdc]

        // Clear fields
        *(uint32_t*)((uint8_t*)this + 0x374) = 0; // param_1[0xdd]
        *(uint32_t*)((uint8_t*)this + 0x378) = 0; // param_1[0xde]
        *(uint32_t*)((uint8_t*)this + 0x380) = 0; // param_1[0xe0]
        *(uint32_t*)((uint8_t*)this + 0x384) = 0; // param_1[0xe1]
        *(uint32_t*)((uint8_t*)this + 0x388) = 0; // param_1[0xe2]
        *(uint16_t*)((uint8_t*)this + 0x38C) = 0; // param_1[0xe3] (low word)
        *(uint16_t*)((uint8_t*)this + 0x38E) = 0; // high word of param_1[0xe3]?? Actually param_1+0xe3 is 0x38C, so 0x38E is next word? Wait: *(undefined2 *)(param_1 + 0xe3) = 0; *(undefined2 *)((int)param_1 + 0x38e) = 0; That's two separate 16-bit writes.
        // We interpret as: set 16-bit at +0x38C and +0x38E to 0.
        *(uint32_t*)((uint8_t*)this + 0x390) = 0; // param_1[0xe4]
        *(uint16_t*)((uint8_t*)this + 0x394) = 0; // param_1[0xe5] (low)
        *(uint16_t*)((uint8_t*)this + 0x396) = 0; // high word of param_1[0xe5]? Actually separate 16-bit at +0x396.
        // So +0x394 and +0x396 = 0.
        *(uint32_t*)((uint8_t*)this + 0x398) = 0xFFFFFFFF; // param_1[0xe6]
        *(uint16_t*)((uint8_t*)this + 0x39E) = 0; // param_1[0xe7?] Actually param_1+0x39E is +0x39E, which is (0xe7*4?) Wait: (int)param_1+0x39E = 0x39E, that's not aligned. The decompiled line: *(undefined2 *)((int)param_1 + 0x39e) = 0; appears twice. So we set uint16 at +0x39E to 0.
        *(uint32_t*)((uint8_t*)this + 0x3A0) = 0; // param_1[0xe8]
        *(uint32_t*)((uint8_t*)this + 0x3A4) = 0; // param_1[0xe9]

        // Set flags/type values
        *(uint8_t*)((uint8_t*)this + 0x1A8) = 5; // param_1[0x6a] - update tick rate? (e.g., every 5 ticks)
        *(uint32_t*)((uint8_t*)this + 0x1D0) |= 0x16; // param_1[0x74] - set bits 1,2,4 (collision flags?)
        *(uint16_t*)((uint8_t*)this + 0x1D4) = 8; // param_1[0x75] - some type (e.g., physics type)
        *(uint32_t*)((uint8_t*)this + 0x1B0) = 0; // param_1[0x6c]

        // Cleanup potential previous sub-object
        uint32_t* pSubObj = (uint32_t*)((uint8_t*)this + 0x2D4); // param_1[0xb5]
        if (*pSubObj != 0) {
            FUN_004daf90(pSubObj);
            *pSubObj = 0;
        }

        // More initializations from globals
        uint32_t uVar5 = _DAT_00d5780c;
        *(uint32_t*)((uint8_t*)this + 0x2E0) = 0; // param_1[0xb8]
        *(uint32_t*)((uint8_t*)this + 0x2E4) = 0; // param_1[0xb9]
        *(uint32_t*)((uint8_t*)this + 0x2E8) = 0; // param_1[0xba]
        *(uint32_t*)((uint8_t*)this + 0x2EC) = 0; // param_1[0xbb]
        *(uint32_t*)((uint8_t*)this + 0x2F4) = uVar5; // param_1[0xbd]
        uVar5 = DAT_00d5d7b8;
        *(uint32_t*)((uint8_t*)this + 0x310) = 0; // param_1[0xc4]
        uint32_t uVar3 = DAT_00d61444;
        *(uint32_t*)((uint8_t*)this + 0x2DC) = 0; // param_1[0xb7]
        *(uint32_t*)((uint8_t*)this + 0x2F8) = uVar5; // param_1[0xbe]

        *(uint8_t*)((uint8_t*)this + 0x39C) = 1; // param_1[0xe7] (byte at +0x39C)
        *(uint32_t*)((uint8_t*)this + 0x304) = 5; // param_1[0xc1] - some count/type
        // (Note: the second *(undefined2 *)((int)param_1 + 0x39e) = 0; is already done above)
        *(uint32_t*)((uint8_t*)this + 0x350) = 0; // param_1[0xd4]
        *(uint32_t*)((uint8_t*)this + 0x354) = uVar3; // param_1[0xd5]
        *(uint32_t*)((uint8_t*)this + 0x358) = uVar3; // param_1[0xd6]
        *(uint32_t*)((uint8_t*)this + 0x35C) = uVar3; // param_1[0xd7]
        *(uint32_t*)((uint8_t*)this + 0x360) = uVar3; // param_1[0xd8]

        // Load data from global blobs into sub-object at +0x3C (interface 1)
        if (DAT_0112ac6c != 0) {
            FUN_00408900((uint8_t*)this + 0x3C, &DAT_0112ac6c, 0x8000);
        }
        if (DAT_0112ac5c != 0) {
            FUN_00408900((uint8_t*)this + 0x3C, &DAT_0112ac5c, 0x8000);
        }
        if (DAT_0112ac64 != 0) {
            FUN_00408900((uint8_t*)this + 0x3C, &DAT_0112ac64, 0x8000);
        }
        if (DAT_0112b36c != 0) {
            FUN_00408900((uint8_t*)this + 0x3C, &DAT_0112b36c, 0x8000);
        }

        // Allocate and initialize sub-object at +0x2D0
        int iVar4 = (int)FUN_009c8e50(12); // alloc 12 bytes
        void* uVar5_ptr;
        if (iVar4 == 0) {
            uVar5_ptr = 0;
        } else {
            uVar5_ptr = FUN_0084e6f0(this); // initialize sub-object
        }
        *(void**)((uint8_t*)this + 0x2D0) = uVar5_ptr; // param_1[0xb4]

        // Clear sentinel region again
        *(uint32_t*)((uint8_t*)this + 0x370) = 0; // param_1[0xdc]
        *(uint32_t*)((uint8_t*)this + 0x36C) = 0; // param_1[0xdb]
        *(uint32_t*)((uint8_t*)this + 0x368) = 0; // param_1[0xda]
        *(uint32_t*)((uint8_t*)this + 0x364) = 0; // param_1[0xd9]

        // Cleanup another sub-object if needed (at +0x374)
        uint32_t* pSubObj2 = (uint32_t*)((uint8_t*)this + 0x374); // param_1[0xdd]
        if (*pSubObj2 != 0) {
            FUN_004daf90(pSubObj2);
            *pSubObj2 = 0;
            // Set another field
            *(uint32_t*)((uint8_t*)this + 0x37C) = DAT_00e2e37c; // param_1[0xdf]
            return this;
        }
        *(uint32_t*)((uint8_t*)this + 0x37C) = DAT_00e2e37c; // param_1[0xdf]
        return this;
    }
};

// Note: The actual class definition would include the vtable pointers and member offsets derived from this constructor.
// This function is the implementation of the constructor for Sentient (or similar entity).