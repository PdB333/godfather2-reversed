// FUNC_NAME: createGameObject
uint createGameObject(uint param1, uint param2) {
    struct AllocationInfo {
        uint type;   // +0x00: object type identifier
        uint size;   // +0x04: allocation size (16 bytes)
        uint flags;  // +0x08: allocation flags (0)
    } info;

    // Initialize allocation parameters for a 16-byte object of type 2
    info.type = 2;
    info.size = 0x10;
    info.flags = 0;

    // Attempt to allocate resource 0x68 through the memory manager
    if (resourceAllocate(0x68, &info, param2)) {
        // If allocation succeeded, initialize the object with param1
        return objectInit(param1);
    }
    return 0;
}