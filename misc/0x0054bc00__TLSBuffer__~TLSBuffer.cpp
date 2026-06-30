// FUNC_NAME: TLSBuffer::~TLSBuffer
void TLSBuffer::__destructor(void)
{
    // Set vtable pointer to base class vtable.
    vtable = reinterpret_cast<void**>(&PTR_LAB_00e397fc);

    uint32_t sizeField = this->field_18; // +0x18: size/count with possible top bits

    // Check if the buffer is allocated (sizeField not -1).
    if (static_cast<int32_t>(sizeField) >= 0) {
        // Retrieve thread-local storage manager.
        void* tlsManager = TlsGetValue(g_tlsIndex); // DAT_01139810

        // Deallocate the buffer using the TLS manager.
        // First arg: pointer to buffer at +0x10
        // Second: actual size = (sizeField & 0x3fffffff) * 48 (0x30 bytes per element)
        // Third: tag 0x17 (23)
        FUN_00aa26e0(this->field_10, (sizeField & 0x3fffffff) * 0x30, 0x17);
    }

    // Revert vtable to another base (or leaf) vtable for further destruction.
    vtable = reinterpret_cast<void**>(&PTR_LAB_00dc4710);
    return;
}