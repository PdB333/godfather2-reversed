// FUNC_NAME: EASTL::allocator::clone
// Function address: 0x008886e0
// Role: Allocates a copy of an EASTL allocator internal data structure (0x20 bytes),
// copies the source data (28 bytes: three uint64_t + one uint32_t), zeros the final
// 4 bytes at offset 0x1c, and returns the new instance.

// The structure is defined by EASTL allocator internal state (32 bytes).
struct EASTLAllocatorData {
    uint64_t field_0;   // +0x00
    uint64_t field_8;   // +0x08
    uint64_t field_10;  // +0x10
    uint32_t field_18;  // +0x18
    uint32_t field_1c;  // +0x1c – explicitly zeroed after copy
};

// Forward declaration of the EASTL debug allocator.
void* __cdecl EASTLAllocateDebug(size_t size, const char* name, int flags, int alignment, const char* file, int line);

// Clone an allocator data object.
EASTLAllocatorData* __cdecl CloneAllocator(EASTLAllocatorData* src) {
    EASTLAllocatorData* dst = (EASTLAllocatorData*)EASTLAllocateDebug(
        0x20, 
        "EASTL", 
        0, 
        0, 
        "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
        0xe9
    );

    if (dst != nullptr) {
        // Copy 28 bytes from source (field_0 through field_18)
        dst->field_0  = src->field_0;   // +0x00
        dst->field_8  = src->field_8;   // +0x08
        dst->field_10 = src->field_10;  // +0x10
        dst->field_18 = src->field_18;  // +0x18

        // Zero the final 4-byte field at offset 0x1c
        dst->field_1c = 0;              // +0x1c
    }

    return dst;
}