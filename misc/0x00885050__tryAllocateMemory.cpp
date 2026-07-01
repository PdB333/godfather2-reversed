// FUNC_NAME: tryAllocateMemory
undefined4 __stdcall tryAllocateMemory(undefined4 allocContext, undefined4 allocFlags)
{
    // Allocation request descriptor: alignment=2, elementSize=0x10, tag=0
    struct {
        uint alignment; // +0x00: always 2
        uint elementSize; // +0x04: always 0x10
        uint tag; // +0x08: always 0
    } allocRequest;
    
    allocRequest.alignment = 2;
    allocRequest.elementSize = 0x10;
    allocRequest.tag = 0;

    // Check if heap can support a 0x100-block allocation with the given request
    int canAlloc = heapCheckAllocation(0x100, &allocRequest); // FUN_009c8ed0
    if (canAlloc != 0) {
        return heapAllocate(allocContext, allocFlags); // FUN_00884e40
    }
    return 0;
}