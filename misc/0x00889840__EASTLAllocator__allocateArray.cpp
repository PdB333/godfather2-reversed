// FUNC_NAME: EASTLAllocator::allocateArray
// Address: 0x00889840
// Role: Allocates an array of objects (each 0x50 bytes) with 0x10 alignment via EASTL allocator.

#include <cstdint>

extern void* FUN_0068abc0(uint32_t size, uint32_t alignment, uint32_t flags,
                          const char* name, int32_t sourceLine, int32_t unknown,
                          const char* file, int32_t debugInfo);
extern void FUN_00888850(uint32_t* count, uint32_t alignment, uint32_t flags,
                         void* buffer, uint32_t originalCount);

void* EASTLAllocator::allocateArray(uint32_t elementCount, uint32_t alignment, uint32_t flags) {
    void* result = nullptr;
    if (elementCount != 0) {
        result = FUN_0068abc0(elementCount * 0x50, 0x10, 0, "EASTL", 0, 0,
                              "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xfd);
        FUN_00888850(&elementCount, alignment, flags, result, elementCount);
    }
    return result;
}