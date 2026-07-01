// FUNC_NAME: AudioDataManager::allocateSampleData
// Address: 0x008f1ef0
// Role: Allocates a 60-byte buffer using an allocator function pointer stored at +0x28,
//       then initializes it via FUN_004c01e0() and stores the result at +0x2c.

#include <cstring> // for memset

// Forward declaration of the helper function called on success
int __fastcall FUN_004c01e0(void); // actual purpose unknown, returns a handle/pointer

// Structure for the allocation output (12 bytes)
struct AllocationInfo {
    uint32_t field0; // +0x00
    uint32_t field4; // +0x04
    uint32_t field8; // +0x08
};

// Note: The object layout assumed:
//   +0x28: pointer to allocator function (__fastcall, returns int, first arg size, second arg pointer to AllocationInfo)
//   +0x2c: result of initialization (handle or pointer)

void __fastcall AudioDataManager::allocateSampleData(void)
{
    AllocationInfo info;
    std::memset(&info, 0, sizeof(info));

    // Function pointer at this+0x28 (single indirection; Ghidra's double dereference likely due to vtable-style, but we treat as direct)
    typedef int (__fastcall *AllocFunc)(int size, AllocationInfo *out);
    AllocFunc allocator = *(AllocFunc *)(this + 0x28);

    int result = allocator(0x3c, &info);
    if (result != 0) {
        *reinterpret_cast<int *>(this + 0x2c) = FUN_004c01e0();
    } else {
        *reinterpret_cast<int *>(this + 0x2c) = 0;
    }
}