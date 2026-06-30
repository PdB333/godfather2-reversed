// FUNC_NAME: ComponentAllocator::AllocateAndInitialize
// Address: 0x00684cf0
// This function allocates a component block (size 0x8c = 140 bytes) via a custom memory manager
// and then initializes the object using the context parameter. The allocation descriptor (type=2,
// extraSize=16, flags=0) suggests this is part of EARS engine's memory pool system.
void* __cdecl ComponentAllocator::AllocateAndInitialize(void* context, int allocationTag) {
    // Allocation descriptor: usually { type, extraSize, flags }
    int allocDesc[3] = {2, 0x10, 0};
    
    // Attempt to allocate 0x8c bytes through the custom memory manager
    bool allocationSuccess = (FUN_0043b980(0x8c, allocDesc, allocationTag) != 0);
    
    if (allocationSuccess) {
        // Call the initializer (probably a constructor that returns the object pointer)
        return (void*)FUN_0099de20(context);
    }
    
    return 0;
}