// FUNC_NAME: Allocator::allocateBlocks

class Allocator {
public:
    // vtable pointer at offset 0
    Allocator* fallbackAllocator; // offset +0x04
    void* allocatedBase;          // offset +0x08
    void* currentPtr;             // offset +0x0C
    void* endPtr;                 // offset +0x10

    __thiscall int allocateBlocks(uint count);
};

// External error handler
extern void handleAllocationFailed(); // 0x005d9ed0

const uint kMaxAllocSize = 0x6666666; // Maximum block count
const uint kBlockSize = 0x28;         // Size of each element (40 bytes)

__thiscall int Allocator::allocateBlocks(uint count)
{
    if (count > kMaxAllocSize) {
        handleAllocationFailed();
        return 1; // error
    }

    // Determine the allocator to use
    Allocator* alloc = fallbackAllocator;
    undefined4 stackBuffer[3]; // fallback buffer if no allocator

    if (alloc == nullptr) {
        // Use stack buffer as temporary allocator context
        stackBuffer[0] = 0;
        stackBuffer[1] = 0;
        stackBuffer[2] = 0;
        alloc = reinterpret_cast<Allocator*>(&stackBuffer);
    }

    // Call the first virtual function of the allocator (allocate)
    void* result = reinterpret_cast<void*(__thiscall*)(Allocator*, uint, void**)>(alloc->vtable[0])(alloc, count * kBlockSize, &stackBuffer);

    allocatedBase = result;
    currentPtr = result;
    endPtr = reinterpret_cast<char*>(result) + count * kBlockSize;

    return 1; // success
}