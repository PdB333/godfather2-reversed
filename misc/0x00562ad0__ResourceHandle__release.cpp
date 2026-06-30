// FUNC_NAME: ResourceHandle::release
// Address: 0x00562ad0
// This function releases two handles from thread-local memory pools.
// The structure holds two pool pointers and corresponding indices (or IDs).
// Uses TLS to access the per-thread memory manager and calls the internal free function.

void __fastcall ResourceHandle::release(ResourceHandle *this)
{
    uint handle1; // Offset +0x14 (param_1[5])
    int handle2;  // Offset +0x08 (param_1[2])

    handle1 = this->field_0x14; // param_1[5]
    if ((int)handle1 >= 0) // Valid handle check
    {
        TlsGetValue(DAT_01139810); // Retrieve thread-local memory manager
        // Free first block: pool at this->field_0x0C, offset = (handle1 & 0x3FFFFFFF) * 12, type = 0x17
        FUN_00aa26e0(this->field_0x0C, (handle1 & 0x3FFFFFFF) * 12, 0x17);
    }

    handle2 = this->field_0x08; // param_1[2]
    if (handle2 >= 0)
    {
        TlsGetValue(DAT_01139810); // Same TLS access
        // Free second block: pool at this->field_0x00, offset = handle2 * 16, type = 0x17
        FUN_00aa26e0(this->field_0x00, handle2 << 4, 0x17);
    }
}