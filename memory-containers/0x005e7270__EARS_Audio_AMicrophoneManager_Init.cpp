// Xbox PDB: EARS::Audio::AMicrophoneManager::Init
// FUNC_NAME: PoolManager::createSlots
// Address: 0x005e7270
// Allocates 4 slots of size 0x70 using a virtual allocator, stores pointers at +0x04, +0x08, +0x0C, +0x10.
// Uses a custom allocator object stored at +0x14.
// Returns 1 on success, 0 on failure.

#include <cstdint>

class PoolManager
{
public:
    // Virtual table likely at offset 0
    // +0x04: m_slots[0] (pointer to allocated block)
    // +0x08: m_slots[1]
    // +0x0C: m_slots[2]
    // +0x10: m_slots[3]
    // +0x14: m_pAllocator (pointer to allocator object with virtual allocate method)
    void** m_slots; // Actually array of 4 pointers starting at +4
    void*  m_pAllocator; // +0x14

    int __fastcall createSlots(void* allocator);
};

// External functions
extern void __cdecl initializeSlot();         // FUN_005e7c20 – likely initializes a slot
extern void __cdecl logMessage(const char*);  // FUN_005dbc10 – prints a string

// Allocation flags structure (size 12 bytes)
struct AllocInfo {
    uint32_t field0_0x00; // = 2
    uint32_t field4_0x04; // = 0x10
    uint32_t field8_0x08; // = 0
};

int __fastcall PoolManager::createSlots(void* allocator)
{
    // allocator is passed in param_1 (ECX), this is in unaff_EDI (unknown register)
    // But the decompiler shows param_1 stored, so likely allocator is the argument.
    // this pointer is unaff_EDI; we'll assume correct.

    if (allocator == nullptr) {
        logMessage("FAIL!");
        return 0;
    }

    this->m_pAllocator = allocator;

    bool bFailed = false;

    // Call a virtual method on the allocator? The decompiler shows:
    // (**(code **)(*param_1 + 8))(); – that's calling function at vtable+8 on allocator.
    // Possibly a "preAllocate" or "beginAllocation" hook.
    // Accept it as a side effect.
    (*(void (**)(void))(*(uint32_t*)allocator + 8))(); // virtual call at offset 8

    uint32_t* slotPtr = reinterpret_cast<uint32_t*>(&this->m_slots[0]); // start at +4
    for (int i = 0; i < 4; i++) {
        AllocInfo info = {2, 0x10, 0}; // allocation flags
        // Call allocator's allocate method (virtual at vtable+0) with size 0x70 and flags
        void* allocated = (*(void* (*)(int, AllocInfo*))(*(uint32_t*)allocator))(0x70, &info);
        *slotPtr = reinterpret_cast<uint32_t>(allocated);
        if (allocated == nullptr) {
            bFailed = true;
        } else {
            initializeSlot(); // Initialize the allocated block
        }
        slotPtr++; // move to next slot (4 bytes each)
    }

    if (!bFailed) {
        logMessage((const char*)0x00e3f4d0); // success message
        return 1;
    }

    logMessage("FAIL!");
    return 0;
}