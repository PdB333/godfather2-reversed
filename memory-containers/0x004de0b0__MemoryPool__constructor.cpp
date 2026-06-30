// FUNC_NAME: MemoryPool::constructor
// Address: 0x004de0b0
// Role: Initializes a pool/allocator object with given size and alignment, inserts it into a global linked list.

class MemoryPool {
public:
    static MemoryPool* ms_pHead; // +0x012054b8 global head of pool list

    void* vtable;          // +0x00 vtable pointer (PTR_FUN_00e36f14)
    MemoryPool* pNext;     // +0x04 linked list next
    int field_0x08;        // +0x08 param_4
    int field_0x0c;        // +0x0c zeroed
    int field_0x10;        // +0x10 zeroed
    int field_0x14;        // +0x14 zeroed
    int field_0x18;        // +0x18 param_3
    int field_0x1c;        // +0x1c zeroed
    int alignment;         // +0x20 param_6 (alignment factor)
    int field_0x24;        // +0x24 param_5
    int alignedSize;       // +0x28 size rounded up to alignment boundary
    int originalSize;      // +0x2c param_2 (original size)
    int field_0x30;        // +0x30 zeroed
    int field_0x34;        // +0x34 zeroed

    // Constructor: stores parameters, zeroes fields, registers in global list, computes aligned size
    void __thiscall constructor(int size, int param3, int param4, int param5, int alignmentParam) {
        pNext = ms_pHead;
        ms_pHead = this;

        vtable = (void*)&PTR_FUN_00e36f14; // VTable for MemoryPool

        field_0x08 = param4;
        field_0x18 = param3;
        field_0x24 = param5;

        field_0x0c = 0;
        field_0x10 = 0;
        field_0x14 = 0;
        field_0x1c = 0;
        field_0x30 = 0;
        field_0x34 = 0;

        alignment = alignmentParam;
        originalSize = size;
        alignedSize = (size + alignmentParam - 1) & ~(alignmentParam - 1);
    }
};