// FUNC_NAME: AllocateAndConstruct
undefined4 __cdecl AllocateAndConstruct(undefined4 objectType, undefined4 allocParams)
{
    int allocatedMem;
    undefined4 result;
    typedef struct {
        int heapId;       // +0x00
        int alignment;    // +0x04
        int flags;        // +0x08
    } AllocationParams;
    AllocationParams params;
    params.heapId = 2;
    params.alignment = 0x10;
    params.flags = 0;

    // Attempt to allocate memory of size 0x2d0 (720 bytes) for an object
    allocatedMem = EngineAllocation(0x2d0, &params, allocParams);
    if (allocatedMem != 0) {
        // Construction/initialization of the object at given type slot
        result = ObjectConstructor(objectType);
        return result;
    }
    return 0;
}