// FUNC_NAME: MemoryManager::allocateObject
uint __thiscall MemoryManager::allocateObject(uint param_2) {
    // Allocation parameters: flags=2, alignment=16, reserved=0
    struct AllocParams {
        uint flags;       // +0x00
        uint alignment;   // +0x04
        uint reserved;    // +0x08
    } params = {2, 0x10, 0};
    
    // Allocate 0x230 bytes with these parameters; param_2 likely a pool or heap context
    int result = poolAllocate(0x230, &params, param_2);
    if (result != 0) {
        // Construct the object using the first argument (this pointer) as the object address
        return constructObject(this);
    }
    return 0;
}