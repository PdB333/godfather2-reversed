// FUNC_NAME: MemoryManager::createObject
undefined4* __thiscall MemoryManager::createObject(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5) {
    undefined4* allocator;  // puVar1
    int result;            // iVar2
    AllocationFlags flags; // local_c, local_8, local_4

    allocator = (undefined4*)GetMemoryManager(); // FUN_009c8f80

    // Set allocation parameters: heap type, alignment, zero-init flag
    flags.heapType = 2;       // +0x00
    flags.alignment = 0x10;   // +0x04
    flags.zeroInit = 0;       // +0x08

    // Call virtual allocator method (first vtable entry) with size and flags
    result = (**(code**)*allocator)(0xf0, &flags);
    if (result == 0) {
        allocator = (undefined4*)0x0;
    } else {
        // Construct the object using the original arguments
        allocator = (undefined4*)ConstructObject(param_2, param_3, param_4, param_5); // FUN_00519760
    }

    // If the object's +4 byte has bit 0 set, deallocate and return null
    if ((*(byte*)(allocator + 4) & 1) != 0) {
        (**(code**)*allocator)(1);
        allocator = (undefined4*)0x0;
    }

    return allocator;
}