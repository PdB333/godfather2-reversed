// FUN_0049ec70: FamilyManager::FamilyManager

#include <cstdint>

// Forward declarations for external functions used
extern void* FUN_009c8f80(); // Memory allocator / object factory
extern uint32_t FUN_004265d0(void* buffer, void* param); // Initialize some engine resource?
extern uint32_t DAT_00e2b1a4; // Some global sentinel value (likely -1)
extern uint32_t DAT_01218a14; // Default/fallback data pointer

// Virtual table pointers (from data section)
extern void* PTR_FUN_00e352ac;  
extern void* PTR_FUN_00e32808;  
extern void* PTR_LAB_00e352b4;  
extern void* PTR_FUN_00e352b8;  

// Structure representing a single family member data block (5 ints)
struct FamilyMemberSlot {
    int32_t sentinel; // +0x00
    int32_t field_04; // +0x04
    int32_t field_08; // +0x08
    int32_t field_0C; // +0x0C
    int32_t field_10; // +0x10
};

// FamilyManager class (size at least 0xB8 bytes)
class FamilyManager {
public:
    // Vtable pointers (multiple inheritance)
    void* vtable0;              // +0x00
    void* vtable1;              // +0x04
    int32_t field_08;           // +0x08 (zero)
    // Padding?
    void* vtable2;              // +0x10
    int32_t field_14;           // +0x14 (zero)
    int32_t field_18;           // +0x18 (zero)
    int32_t field_1C;           // +0x1C (zero)
    int32_t field_20;           // +0x20 (zero)
    int32_t field_24;           // +0x24 (zero)

    // Array of 4 family member slots (each 5 ints = 20 bytes)
    // Offsets: 0x30 (0x0C), 0x44, 0x58, 0x6C
    FamilyMemberSlot members[4]; // +0x30

    int32_t field_80;           // +0x80 (zero)
    int32_t field_84;           // +0x84 (zero)
    int32_t field_88;           // +0x88 (zero)

    // Internal allocator/context pointers
    int32_t field_90;           // +0x90 (zero) 
    int32_t memberCount;        // +0x94 = 8 (max 8 members)
    
    // Engine resource handle and allocator pointer
    uint32_t resourceHandle;    // +0x98 (from FUN_004265d0)
    void* allocatorPtr;         // +0x9C (from FUN_009c8f80)

    // Result from virtual call
    uint32_t allocationResult;  // +0x8C (offset 0x23)

    int32_t field_A0;           // +0xA0 (zero)
    int32_t sentinel2;          // +0xA4
    int32_t field_A8;           // +0xA8 (zero)
    // byte at +0xAC - bitwise manipulation (low nibble cleared)
    uint8_t byte_AC;            // +0xAC
    // int at +0xB0 - low nibble cleared
    int32_t field_B0;           // +0xB0
    int32_t field_B4;           // +0xB4 (zero)
};

// Constructor implementation
void __thiscall FamilyManager::FamilyManager(void) {
    // Set up vtable pointers for multiple inheritance
    this->vtable1 = &PTR_FUN_00e32808;
    this->field_08 = 0;
    this->vtable0 = &PTR_FUN_00e352ac;
    this->vtable1 = &PTR_LAB_00e352b4; // Overwrites previous vtable1
    this->field_14 = 0;
    this->vtable2 = &PTR_FUN_00e352b8;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_80 = 0;
    this->field_84 = 0;
    this->field_88 = 0;

    // Temporary local buffer (used for resource initialization)
    uint32_t local_1c = 0;
    uint32_t local_18 = 0;
    uint32_t local_14 = 0;

    // Acquire an allocator/factory object
    void* allocator = FUN_009c8f80();
    this->field_90 = 0;
    this->memberCount = 8; // Set maximum members to 8
    uint32_t handle = FUN_004265d0(&local_1c, allocator);
    this->resourceHandle = handle;
    this->allocatorPtr = allocator;

    // Call a virtual method on the allocator (offset +0x08 in its vtable)
    // This likely initializes the allocator's internal state
    (*(void (__thiscall**)(void*))(*(uint32_t*)allocator + 8))(allocator);

    // Obtain a default resource pointer if handle is null
    uint32_t* resourcePtr = (uint32_t*)this->resourceHandle;
    if (resourcePtr == nullptr) {
        resourcePtr = &DAT_01218a14;
    }

    // Call another virtual method on the allocator: allocate 0x20 bytes of something
    uint32_t allocResult = (*(uint32_t (__thiscall**)(void*, uint32_t, uint32_t*))(**(uint32_t**)allocator))(allocator, 0x20, resourcePtr);
    uint32_t sentinelVal = DAT_00e2b1a4;
    this->allocationResult = allocResult;

    // Bitwise manipulations on fields at byte offsets 0xAC (low nibble cleared) and 0xB0 (low 4 bits cleared)
    this->byte_AC = this->byte_AC & 0xF0;
    this->field_B0 = this->field_B0 & 0xFFFFFFF0;

    this->sentinel2 = sentinelVal;
    this->field_A8 = 0;
    this->field_B4 = 0;
    this->field_A0 = 0;

    // Initialize the 4 family member slots with sentinel values
    // Each slot: sentinel = sentinelVal, rest = 0
    for (int i = 0; i < 4; i++) {
        this->members[i].sentinel = sentinelVal;
        this->members[i].field_04 = 0;
        this->members[i].field_08 = 0;
        this->members[i].field_0C = 0;
        this->members[i].field_10 = 0;
    }

    // Also set the first field of a possible extra slot (index 4) with sentinel and zeros
    // This is the 5th group at offset 0x6C (members[4] if array had 5 elements, but we only defined 4)
    // The original code writes to offsets 0x1B through 0x1F relative to base.
    // Offset 0x1B = members[4].sentinel, 0x1C = members[4].field_04, etc.
    // Since we don't have a fifth member in our struct, we treat it as an overflow initialization
    // For reconstruction, we might extend members array to 5 or note it separately.
    // Here we'll just note it as part of the initialization.
    // Actually, the loop already sets indices 0-3 (0xC,0x11,0x16). The remaining 0x1B-0x1F is a fourth group (index 3? Wait careful.)
    // Let's recalc: The code sets:
    // [0xC]=sentinel, [0xD]=0, [0xE]=0, [0xF]=0, [0x10]=0
    // [0x11]=sentinel, [0x12]=0, [0x13]=0, [0x14]=0, [0x15]=0
    // [0x16]=sentinel, [0x17]=0, [0x18]=0, [0x19]=0, [0x1A]=0
    // [0x1B]=sentinel, [0x1C]=0, [0x1D]=0, [0x1E]=0, [0x1F]=0
    // That's 4 groups exactly. Our members array has 4 elements.
    // So loop should set all 4 groups. The code after the loop sets [0x1B] and then [0x1C-0x1F], which is the 4th group.
    // So the loop above sets groups 0,1,2 and then explicit sets group 3.
    // I'll adjust the reconstruction to set all 4 in a loop for clarity.
    // Actually the decompiled code shows explicit writes for the 4th group, not a loop.
    // We'll just replicate the original order.
    // The loop above already does indices 0..2 from offsets 0xC,0x11,0x16.
    // Then we set index 3 explicitly.
}