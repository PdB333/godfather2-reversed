// FUNC_NAME: MemoryStackAllocator::pushDataBlock

class MemoryStackAllocator {
public:
    // Offset 0x00: pointer to the memory pool context (int*)
    // The pool context structure has a stack pointer at +0x14
    void __thiscall pushDataBlock(uint32_t param2, const uint64_t* param3) {
        // Get the memory pool context pointer from this
        int* poolContext = *reinterpret_cast<int**>(this); // *this is a pointer to pool context
        int* stackPtrPtr = reinterpret_cast<int*>(poolContext + 0x14 / sizeof(int)); // +0x14: pointer to stack pointer

        // Push a vtable pointer (address of a global) onto the stack
        *reinterpret_cast<uint32_t**>(*stackPtrPtr) = &PTR_LAB_01124af4; // Write global address
        *stackPtrPtr = *stackPtrPtr + 1; // Advance stack pointer by 4 bytes

        // Push param2 (likely a type or flags)
        *reinterpret_cast<uint32_t*>(*stackPtrPtr) = param2;
        *stackPtrPtr = *stackPtrPtr + 1; // Advance by 4 bytes

        // Align stack pointer to 16-byte boundary
        uint32_t alignedAddr = (*stackPtrPtr + 0x13) & 0xFFFFFFF0;
        *stackPtrPtr = alignedAddr;

        // Copy 16 bytes from param3 into the aligned location
        uint64_t* dest = reinterpret_cast<uint64_t*>(alignedAddr);
        dest[0] = param3[0];
        dest[1] = param3[1];

        // Advance stack pointer past the 16-byte block
        *stackPtrPtr += 0x10;
    }
};