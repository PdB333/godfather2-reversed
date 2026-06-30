// FUNC_NAME: Animated::~Animated
void __fastcall Animated::~Animated(Animated* this)
{
    uint handle = this->m_handle; // offset +0x10 (param_1[4])
    if ((int)handle >= 0) {
        // Retrieve thread-local storage for the pool manager
        TlsGetValue(gs_TlsIndex); // DAT_01139810 – likely a TLS slot for the allocator

        // Deallocate the animation data block
        // param_1[2] is offset +0x8 – pointer to data array or owning container
        // (handle & 0x3fffffff) * 0x30 – compute byte size from handle (index * 0x30)
        // 0x17 – a type/size identifier (23? maybe a constant like kAnimBlock)
        FUN_00aa26e0(
            this->m_dataBuffer,               // +0x08
            (handle & 0x3fffffff) * 0x30,     // offset/size
            0x17                              // allocation type
        );
    }
    // Clear vtable to sentinel (destructed/invalid object)
    this->vtable = &PTR_LAB_00d96914; // pointer to null vtable
}