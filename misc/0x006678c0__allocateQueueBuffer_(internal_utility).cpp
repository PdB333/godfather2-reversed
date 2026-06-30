// FUNC_NAME: allocateQueueBuffer (internal utility)
// Address: 0x006678c0
// Role: Allocates and initializes a circular queue buffer for 4-byte elements.
// The queue structure (at pointer in EDI) has 4 fields:
//   +0x00: head index (int)
//   +0x04: capacity (element count)
//   +0x08: tail index (int)
//   +0x0C: buffer pointer (int*)
// The allocated buffer size is rounded up to a multiple of 64 elements,
// with a minimum additional 128 elements.
// Returns 0 on success, -2 (0xFFFFFFFE) on allocation failure.

int __fastcall allocateQueueBuffer(void* queue, uint requestedCapacity)
{
    uint uVar1;
    size_t elementCount;
    int* buffer;

    // Extract low 6 bits (mod 64) considering possible sign extension.
    uVar1 = requestedCapacity & 0x8000003f;
    if ((int)uVar1 < 0) {
        uVar1 = (uVar1 - 1 | 0xffffffc0) + 1;
    }
    // Calculate element count: add 128, subtract the remainder mod 64.
    elementCount = requestedCapacity + (0x80 - uVar1);
    buffer = (int*)_calloc(4, elementCount);
    ((int**)queue)[3] = (int*)buffer;      // +0x0C: buffer pointer
    if (buffer == NULL) {
        return -2;
    }
    ((int*)queue)[1] = elementCount;       // +0x04: capacity
    *(int*)queue = 0;                       // +0x00: head
    ((int*)queue)[2] = 0;                   // +0x08: tail
    return 0;
}