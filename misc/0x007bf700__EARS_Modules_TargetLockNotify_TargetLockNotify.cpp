// Xbox PDB: EARS_Modules_TargetLockNotify_TargetLockNotify
// FUNC_NAME: MessageTarget::constructor
// Function address: 0x007bf700
// Description: Constructor for a message-target class (likely related to lock/unlock message dispatching).
// The object contains two string fields for "iMsgTargetLocked" and "iMsgTargetUnLocked".
// Uses debug sentinel values in debug builds.

#include <cstdint>

// Forward declaration of base class constructor (set via a function pointer)
// The base class is likely EARS::Object or similar EA framework object
extern int32_t* BaseClassCtor(int32_t* self, uint32_t baseParam);  // Address 0x0046c590

// Helper to free a pointer if non-null (address 0x004daf90)
extern void FreePointer(void** ptr);

// Helper to set a string member (address 0x00408240)
extern void SetStringMember(int32_t* member, const char* str);

// Global instance counter (address 0x0112ba0c)
extern int32_t g_instanceCount;

// Sentinel values used for debugging
static constexpr uint32_t kMagic1 = 0xbadbadba;
static constexpr uint32_t kMagic2 = 0xbeefbeef;
static constexpr uint32_t kMagic3 = 0xeac15a55;
static constexpr uint32_t kMagic4 = 0x91100911;

// The constructor function; this pointer is passed in ECX (__thiscall)
int32_t* MessageTargetCtor(int32_t* self, uint32_t baseParam) {
    // Call base class constructor (first member is vtable, etc.)
    BaseClassCtor(self, baseParam);

    // Set vtable pointer for this class (from global table)
    self[0] = reinterpret_cast<int32_t>(&PTR_FUN_00d6e258);  // +0x00: vtable

    // Set additional vtable-like pointers for derived behavior
    self[0x0F] = reinterpret_cast<int32_t>(&PTR_LAB_00d6e248); // +0x3C
    self[0x12] = reinterpret_cast<int32_t>(&PTR_LAB_00d6e244); // +0x48

    // Initialize members at offsets +0x50, +0x54, +0x56, +0x58, +0x5C, +0x5E, +0x60, etc.
    self[0x14] = 0;                       // +0x50: pointer (will hold locked string)
    *(uint16_t*)(self + 0x15) = 0;       // +0x54: low 16 bits of a 32-bit field? (bitfield)
    *(uint16_t*)((int8_t*)self + 0x56) = 0; // +0x56: high 16 bits of same field
    self[0x16] = 0;                       // +0x58: pointer (unlocked string)
    *(uint16_t*)(self + 0x17) = 0;       // +0x5C: low 16 bits
    *(uint16_t*)((int8_t*)self + 0x5E) = 0; // +0x5E: high 16 bits

    // Another set of fields at +0x64, +0x68, +0x6E, +0x70, +0x72, +0x76, etc.
    self[0x19] = 0;                       // +0x64: pointer (maybe array list)
    self[0x1A] = 0;                       // +0x68
    *(uint16_t*)(self + 0x1C) = 0;       // +0x70: low
    *(uint16_t*)((int8_t*)self + 0x72) = 0; // +0x72: high
    *(uint16_t*)(self + 0x1E) = 0;       // +0x78: low
    *(uint16_t*)((int8_t*)self + 0x7A) = 0; // +0x7A: high

    // More fields at +0x80, +0x84, +0x88, +0x8C, +0x90, +0x94, +0x98, etc.
    self[0x20] = 0;                       // +0x80: pointer (maybe array list)
    self[0x21] = 0;                       // +0x84
    self[0x22] = kMagic1;                 // +0x88: debug sentinel
    self[0x23] = kMagic2;                 // +0x8C
    self[0x24] = kMagic3;                 // +0x90
    self[0x25] = kMagic4;                 // +0x94

    // Pointers to the two 32-bit fields that will contain array lists
    int32_t** arrayList1 = reinterpret_cast<int32_t**>(self + 0x19); // +0x64
    int32_t** arrayList2 = reinterpret_cast<int32_t**>(self + 0x20); // +0x80

    // Further clear fields for debug
    *(uint16_t*)(self + 0x27) = 0;       // +0x9C: low
    *(uint16_t*)((int8_t*)self + 0x9E) = 0; // +0x9E: high
    *(uint16_t*)(self + 0x29) = 0;       // +0xA4: low
    *(uint16_t*)((int8_t*)self + 0xA6) = 0; // +0xA6: high

    // Zero more pointer-sized fields
    self[0x18] = 0;                       // +0x60
    self[0x1B] = 0;                       // +0x6C
    self[0x1D] = 0;                       // +0x74
    self[0x26] = 0;                       // +0x98
    self[0x28] = 0;                       // +0xA0

    // Initialize field at +0x7C with a global default value
    self[0x1F] = DAT_00d6e288;            // +0x7C: some default data

    // If the array list at +0x80 is non-null, free it and set to null
    if (*arrayList2 != 0) {
        FreePointer(arrayList2);
        *arrayList2 = 0;
    }

    // Reset debug sentinels
    self[0x25] = 0; // +0x94
    self[0x24] = 0; // +0x90
    self[0x23] = 0; // +0x8C
    self[0x22] = 0; // +0x88

    // Similarly free the array list at +0x64 if non-null
    if (*arrayList1 != 0) {
        FreePointer(arrayList1);
        *arrayList1 = 0;
    }

    // Increment global instance counter
    g_instanceCount++;

    // Set name strings for locked/unlocked message targets
    SetStringMember(self + 0x14, "iMsgTargetLocked");   // +0x50
    SetStringMember(self + 0x16, "iMsgTargetUnLocked"); // +0x58

    return self;
}