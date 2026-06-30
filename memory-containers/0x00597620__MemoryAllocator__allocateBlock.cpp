// FUNC_NAME: MemoryAllocator::allocateBlock
undefined4 __thiscall MemoryAllocator::allocateBlock(void *thisObject)
{
    // Global allocator vtable pointer
    MemoryAllocator *allocator = (MemoryAllocator *)DAT_01205590;
    // Stack temporary for allocation parameters
    struct AllocParams {
        uint32_t size;      // +0x00
        uint32_t alignment; // +0x04
        uint32_t flags;     // +0x08
        uint32_t tag;       // +0x0C
    } params;

    // Setup first allocation: size 0x200, alignment 0x38
    params.size = 0x200;
    params.alignment = 0x38;
    params.flags = 2;
    params.tag = 0x59764b; // likely a debug tag string pointer
    allocator->vtable->allocate(allocator, &params);

    // "in_EAX + 2" suggests thisObject is a buffer index or pointer
    uint32_t *pField2 = (uint32_t *)((char *)thisObject + 2);
    params.size = 0;       // reused for other call
    params.alignment = 2;  // flags
    params.tag = 0x597663;
    allocator->vtable->allocate(allocator, &params);

    // Setup another allocation: size 0x20? (from later puStack_6c=0x20)
    uint32_t field4 = (uint32_t)thisObject + 4;
    uint8_t tempBuffer[20]; // stack buffer for string "default"
    // ... (similar pattern)

    // Final field writes
    allocator->vtable->write((char *)thisObject + 0x2C, nullptr, 0);
    allocator->vtable->write((char *)thisObject + 0x30, &params, 4);
    allocator->vtable->write((char *)thisObject + 0x34, &tempBuffer, 4);

    return 0x38; // size of allocated object
}