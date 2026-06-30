// FUN_00452450: PacketBuffer::addPacketRecord
uint __fastcall PacketBuffer::addPacketRecord(PacketBuffer* thisPtr, const PacketRecord& source)
{
    // source pointer passed in EDI (not in standard parameter)
    uint count = *(uint*)((uint)thisPtr + 0x500); // +0x500: count of records

    if (count < 32) {
        // Increment count
        *(uint*)((uint)thisPtr + 0x500) = count + 1;

        // Copy first byte (likely type/flag)
        *(byte*)((uint)thisPtr + count * 0x28) = *(byte*)&source;

        // Copy four dwords at offsets 4, 8, 0xC, 0x10
        uint dest = (uint)thisPtr + count * 0x28;
        *(uint32*)(dest + 4) = *(uint32*)((uint)&source + 4);
        *(uint32*)(dest + 8) = *(uint32*)((uint)&source + 8);
        *(uint32*)(dest + 0xC) = *(uint32*)((uint)&source + 0xC);
        *(uint32*)(dest + 0x10) = *(uint32*)((uint)&source + 0x10);

        // Copy string/block at offset 0x14 (16 bytes?) via helper
        // FUN_004d3e20 is likely a memcpy or string assignment
        FUN_004d3e20((void*)((uint)&source + 0x14));

        // Copy final byte at offset 0x24
        *(byte*)(dest + 0x24) = *(byte*)((uint)&source + 0x24);

        return 1; // success
    }
    // Return error: low byte cleared (original count with flags)
    return count & 0xFFFFFF00;
}