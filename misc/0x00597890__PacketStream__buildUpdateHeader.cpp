// FUNC_NAME: PacketStream::buildUpdateHeader
// Address: 0x00597890
// This function constructs a packet header or update structure in a buffer.
// It uses a global vtable pointer at DAT_01205590 (likely a stream vtable).
// The function writes a series of values into the buffer (param_1) at specific offsets.
// param_3 appears to be an index used to compute a masked value (not used later?).
// Returns 0x5c (92), the size of the completed structure.

uint __thiscall PacketStream::buildUpdateHeader(void* thisPtr, uint param2, int index)
{
    int iVar1;
    int iVar2;
    uint uStack_1c;
    int iStack_18;
    undefined4* puStack_14;
    uint uStack_10;
    uint local_8;
    uint local_4;

    // Compute a masked offset from the index (0x14 = 20, 0xc = 12)
    local_4 = (index * 0x14 + 0xc) & 0xFFFF;

    // Prepare values to write
    uStack_10 = 2;                  // Short value 2 (likely a version or type tag)
    puStack_14 = &local_8;          // Pointer to local_8 (address of the 0x202 value)
    local_8 = 0x202;                // Another constant (possibly a packet type ID)
    uStack_1c = 0x5978c8;          // Constant address (might be a string or another constant)
    iStack_18 = (int)thisPtr;      // Save this pointer (though not used directly)

    // First virtual call: maybe reset/clear the stream or prepare for writing.
    // The vtable at *DAT_01205590 + 0x10 is likely a "beginWrite" or similar.
    (*(code**)(*DAT_01205590 + 0x10))();

    // Overwrite uStack_1c with 2 for the next write
    uStack_1c = 2;
    iVar2 = (int)thisPtr + 2;      // Offset 2 in the buffer

    // Write a 2-byte value (2) at offset 2
    (*(code**)(*DAT_01205590 + 0x10))(iVar2, &uStack_10);

    iVar1 = 4;
    // Write a 4-byte value (0x202) at offset 4 (note: 3rd argument = size)
    (*(code**)(*DAT_01205590 + 0x10))((int)thisPtr + 4, &puStack_14, 4);

    // Write a 2-byte value (2) at offset 8
    (*(code**)(*DAT_01205590 + 0x10))((int)thisPtr + 8, &uStack_1c);

    // Copy 0x50 bytes from offset 2 to offset 0xc (duplicate the header section)
    (*(code**)(*DAT_01205590 + 0x10))((int)thisPtr + 0xc, iVar2, iVar1 * 0x14); // 4*20=80=0x50

    // Return the total structure size (0x5c = 92 bytes)
    return 0x5c;
}