// FUNC_NAME: NetSession::SetPacketData
// Function address: 0x005e6820
// Purpose: Update two data fields in a packet record identified by handle.
// The handle's low 16 bits index into a global packet table (DAT_012234bc).
// Each record is 0x30 bytes, with an internal header offset of 0x10 before the first entry.
// Fields at +0x24 and +0x28 are set to data1 and data2.
// Field at +0x2C stores the handle for validation.
// Returns 1 on success, 0 if handle out of range or entry invalid.

uint NetSession::SetPacketData(uint handle, uint data1, uint data2)
{
    uint index = handle & 0xFFFF;
    if (index >= 0x200)
        return 0;

    // Global array base pointer (declared elsewhere)
    byte* base = (byte*)DAT_012234bc;
    if (base == 0)
        return 0;

    // Each record starts at base + 0x10 + index * 0x30
    byte* entry = base + 0x10 + index * 0x30;
    if (entry == 0)
        return 0;

    // Verify that the entry is assigned to this handle
    if (*(uint*)(entry + 0x2C) != handle)
        return 0;

    // Store the two data values
    *(uint*)(entry + 0x24) = data1;
    *(uint*)(entry + 0x28) = data2;

    return 1;
}