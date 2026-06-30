// FUNC_NAME: NetConnection::queueReliablePacket
uint __fastcall NetConnection::queueReliablePacket(const PacketEntry& entry) // this in ESI (custom convention)
{
    // Offset in this:
    // +0x000 to +0x2FF: array of 32 PacketEntry structs (0x18 bytes each)
    // +0x300: count of valid entries (uint32)

    uint currentCount = *(uint*)((uint)this + 0x300);
    if (currentCount < 0x20) // max 32 entries
    {
        // Increment count
        *(uint*)((uint)this + 0x300) = currentCount + 1;

        // Copy entry to next free slot
        PacketEntry* pSlot = (PacketEntry*)((uint)this + currentCount * 0x18);
        *pSlot = entry; // assumes PacketEntry is 6 dwords (0x18 bytes)

        // Return success handle: low byte set to 1, high 3 bytes = address of slot (>>8)
        return ((uint)pSlot >> 8) | 1;
    }
    // Buffer full – return failure (preserve caller's EAX low byte cleared)
    return in_EAX & 0xFFFFFF00; // in_EAX holds previous return value
}