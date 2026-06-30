// FUNC_NAME: MemoryManager::allocateAndConstructObject
undefined4* __thiscall MemoryManager::allocateAndConstructObject(undefined4 param_2, undefined4 param_3, undefined4 param_4) {
    undefined4* manager;
    int result;
    undefined4 local_c;  // alignment flags? 2 = maybe alignment, 0x10 = pool ID
    undefined4 local_8;
    undefined4 local_4;

    // Get memory manager singleton (likely via a static instance or global)
    manager = (undefined4*)FUN_009c8f80();

    // Setup allocation parameters: size=2, alignment=0x10, flags=0
    // These might be fields of a memory allocation request struct
    local_c = 2;   // +0x00: maybe size field? Or alignment type
    local_8 = 0x10; // +0x04: alignment boundary
    local_4 = 0;    // +0x08: flags (e.g., from which pool)

    // Allocate memory via vtable call: allocate(size=0xf0, allocParams)
    result = (**(code**)*manager)(0xf0, &local_c);
    if (result == 0) {
        manager = nullptr;
    } else {
        // Construct object at allocated memory with parameters
        manager = (undefined4*)FUN_00519760((int)manager, param_2, param_3, param_4);
    }

    // Check if the object's flag byte (at offset +4) has bit 0 set
    if ((*(byte*)(manager + 4) & 1) != 0) {
        // If set, call a method (likely release/free) via vtable with parameter 1
        (**(code**)*manager)(1);
        manager = nullptr;
    }

    return manager;
}