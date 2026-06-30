// FUNC_NAME: GameObjectFactory::allocateAndConstruct
uint32_t GameObjectFactory::allocateAndConstruct(uint32_t param_1, uint32_t param_2) {
    // Local allocation info struct: { size, alignment, flags }
    AllocationInfo allocInfo;
    allocInfo.size = 2;        // +0x00: Probably object type or subclass size
    allocInfo.alignment = 0x10;// +0x04: 16-byte alignment
    allocInfo.flags = 0;       // +0x08: No special flags

    // Allocate 0x8C (140) bytes from memory pool using info and param_2
    int32_t allocationResult = allocateFromPool(0x8C, &allocInfo, param_2);
    if (allocationResult != 0) {
        // If allocation succeeded, initialize the object identified by param_1
        return initializeObject(param_1);
    }
    return 0;
}