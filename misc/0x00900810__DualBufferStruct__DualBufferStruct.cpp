// FUNC_NAME: DualBufferStruct::DualBufferStruct
// Address: 0x00900810
// Role: Constructor for a structure containing two fixed-capacity buffers (each 0x48 bytes, capacity 6). Used in networking or stream management.

// Forward declaration of EARS memory allocator (likely pool allocator)
void* __fastcall allocateMemory(uint size);  // FUN_009c8e80

// Structure holding two buffer descriptors
struct DualBufferStruct {
    void* buffer1;      // +0x00: pointer to first allocated buffer (size 0x48)
    int   count1;       // +0x04: number of elements in buffer1 (initially 0)
    int   capacity1;    // +0x08: maximum elements in buffer1 (6)
    void* buffer2;      // +0x0C: pointer to second allocated buffer (size 0x48)
    int   count2;       // +0x10: number of elements in buffer2
    int   capacity2;    // +0x14: maximum elements in buffer2 (6)
};

// __fastcall: ECX = this
DualBufferStruct* __fastcall DualBufferStruct_ctor(DualBufferStruct* this) {
    // Allocate first buffer (e.g., for reliable packet data, each element 12 bytes)
    this->buffer1 = allocateMemory(0x48);  // 72 bytes
    this->count1 = 0;
    this->capacity1 = 6;                  // 6 elements of 12 bytes each

    // Allocate second buffer (e.g., for unreliable data)
    this->buffer2 = allocateMemory(0x48);
    this->count2 = 0;
    this->capacity2 = 6;

    return this;
}