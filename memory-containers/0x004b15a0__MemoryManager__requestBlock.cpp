// FUNC_NAME: MemoryManager::requestBlock

/**
 * Function address: 0x004b15a0
 * Role: Requests a memory block from the EARS memory manager.
 * Calls the first virtual function of an interface obtained via a global getter.
 * The descriptor struct contains type=2 (likely pool type), alignment=0x10, flags=0.
 */
void MemoryManager::requestBlock() {
    // Get singleton interface pointer
    uint32* pInterface = (uint32*)FUN_009c8f80();  // Returns pointer to MemoryManager singleton

    // Descriptor structure passed to the allocator
    struct {
        uint32 type;     // +0x00: allocation type (2 = dynamic pool?)
        uint32 alignment; // +0x04: requested alignment (0x10 = 16 bytes)
        uint32 flags;    // +0x08: flags (0 = none)
    } descriptor;

    descriptor.type = 2;
    descriptor.alignment = 0x10;
    descriptor.flags = 0;

    // Call the first virtual method (RequestBlock) on the interface
    // The vtable pointer is the first dword of the interface object
    typedef void (__thiscall* RequestBlockFunc)(void* this, uint32 size, void* descriptor);
    RequestBlockFunc func = *(RequestBlockFunc*)(*pInterface);
    func(pInterface, 0x60, &descriptor);
}