// FUNC_NAME: DialogTreeManager::constructor

// Reconstructed constructor for DialogTreeManager at 0x006b8ab0
// Base class constructor at 0x0046c590 is called first with param_2 (likely a resource/manager pointer)

#include <cstdint>

// Forward declaration for base class constructor
void __thiscall BaseDialogManager::constructor(void* param_2); // param_2 is likely a DialogTreeBank or similar

class DialogTreeManager {
public:
    // Vtable pointer at +0x00
    // Additional function/data pointers at offsets +0x3C and +0x48
    // Many zero-initialized fields at offsets +0x50 through +0x98
    // Two sentinel -1 values at +0x90 and +0x94, then a zero at +0x98
};

uint32_t* __thiscall DialogTreeManager::constructor(uint32_t* this_ptr, uint32_t param_2)
{
    // Call base class constructor (e.g., CoreObject::constructor or ManagerBase::constructor)
    BaseDialogManager::constructor(reinterpret_cast<void*>(param_2)); // base init

    // Set vtable pointer
    this_ptr[0] = reinterpret_cast<uint32_t>(&PTR_FUN_00d5e5e8); // main vtable

    // Set additional virtual-like pointers
    this_ptr[0xF] = reinterpret_cast<uint32_t>(&PTR_LAB_00d5e5d8); // offset +0x3C
    this_ptr[0x12] = reinterpret_cast<uint32_t>(&PTR_LAB_00d5e5d4); // offset +0x48

    // Zero-initialize a block of fields (starting at offset +0x50)

    // Offset +0x50: uint32
    this_ptr[0x14] = 0;

    // Offset +0x54: low 2 bytes (lower half of uint32 at +0x54)
    *(uint16_t*)(this_ptr + 0x15) = 0;
    // Offset +0x56: high 2 bytes (upper half of that uint32)
    *(uint16_t*)(reinterpret_cast<uint8_t*>(this_ptr) + 0x56) = 0;

    // Offset +0x58: uint32
    this_ptr[0x16] = 0;

    // Offset +0x5C: low 2 bytes of uint32 at +0x5C
    *(uint16_t*)(this_ptr + 0x17) = 0;
    // Offset +0x5E: high 2 bytes
    *(uint16_t*)(reinterpret_cast<uint8_t*>(this_ptr) + 0x5E) = 0;

    // Offset +0x60: uint32
    this_ptr[0x18] = 0;

    // Sequence of uint32 fields, set in reverse order (as per original code)
    // Offset +0x70, +0x6C, +0x68, +0x64
    this_ptr[0x1C] = 0;
    this_ptr[0x1B] = 0;
    this_ptr[0x1A] = 0;
    this_ptr[0x19] = 0;

    // More uint32 fields: +0x74, +0x78, +0x7C, +0x80, +0x84, +0x88, +0x8C
    this_ptr[0x1D] = 0;
    this_ptr[0x1E] = 0;
    this_ptr[0x1F] = 0;
    this_ptr[0x20] = 0;
    this_ptr[0x21] = 0;
    this_ptr[0x22] = 0;
    this_ptr[0x23] = 0;

    // Sentinel indices/counters set to -1 and 0
    this_ptr[0x24] = 0xFFFFFFFF; // offset +0x90 - invalid index or ID
    this_ptr[0x25] = 0xFFFFFFFF; // offset +0x94 - invalid index or ID
    this_ptr[0x26] = 0;          // offset +0x98 - clear counter

    return this_ptr;
}