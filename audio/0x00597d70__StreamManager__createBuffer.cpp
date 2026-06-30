// FUNC_NAME: StreamManager::createBuffer
uint32 StreamManager::createBuffer(void) {
    // g_pStreamManager is a global singleton of StreamManager
    // It uses a function pointer at offset 0x10 (likely a virtual method)
    void* pManager = *DAT_01205590; // global pointer to StreamManager
    
    // First call: allocates a new buffer object (returns pointer in EAX)
    void* pBuffer = (*(code**)(*(uint32*)pManager + 0x10))();
    
    // Write a 2-byte value (type or size) at offset +2
    uint32 args1[2];
    args1[0] = 2; // uStack_10 = 2
    (*(code**)(*(uint32*)pManager + 0x10))( (uint32)pBuffer + 2, &args1[0], 2 );
    
    // Write a pointer to the internal data buffer at offset +4
    void* pDataBuffer = &local_8; // local_8 = 0x208, stack variable acting as placeholder? Actually local_8 = 0x208, but the address is passed
    uint32 args2[2];
    args2[0] = (uint32)&local_8; // pointer to the allocated area? stack address? In original: puStack_14 = &local_8, uStack_10 = 2, local_4 = 8, local_8 = 0x208
    (*(code**)(*(uint32*)pManager + 0x10))( (uint32)pBuffer + 4, &args2[0], 4 );
    
    // Return a constant handle (8)
    return 8;
}