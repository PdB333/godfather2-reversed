// FUNC_NAME: TNLConnection::extendReliablePacketRange
void __thiscall TNLConnection::extendReliablePacketRange(int startSequence, int count)
{
    // this: PacketQueue object (likely TNLConnection send queue)
    // Offsets (int* this):
    // +0x00: m_packetBuffer (pointer to packet buffer structure)
    // +0x0C: m_headerArray (pointer to array of uint packet headers, derived from m_packetBuffer+0xC)
    // +0x18: m_writeIndex (index of next packet slot, also count of written packets)
    // +0x1C: m_maxPackets (capacity)
    // +0x0C? Actually param_1[3] is at +0xC: m_allocator (pointer to allocation object)
    //    then +0x8 in that object is the allocation size/function? Used in fallback call.

    uint *puVar1;
    uint uVar2;
    uint uVar3;

    // Check if we have previously written a packet (m_writeIndex < m_maxPackets is likely a size check)
    if (this[7] < this[6]) { // if m_maxPackets < m_writeIndex (i.e., not full? Actually reversed?)
        // Get the last written packet header (index m_writeIndex - 1)
        puVar1 = (uint *)(*(int *)(this[0] + 0xc) + -4 + this[6] * 4);
        uVar2 = *puVar1;

        // Check packet type (lower 6 bits) == 3 (reliable ordered)
        if ((((byte)uVar2 & 0x3f) == 3) &&
            // Extract the existing end sequence (bits 15-23: count field)
            (uVar3 = (int)uVar2 >> 0xf & 0x1ff,
             // Check that the stored start sequence (bits 24-31) <= requested startSequence
             (int)uVar2 >> 0x18 <= startSequence) &&
            // And that requested startSequence <= existing end sequence + 1 (i.e., adjacent or overlapping)
            (startSequence <= (int)(uVar3 + 1))) {
            // Check if requested range is already fully covered (startSequence + count - 1 <= existing end)
            if (startSequence + count - 1 <= (int)uVar3) {
                return; // Already covered, nothing to do
            }
            // Extend the existing packet's end sequence to cover the new range
            // New count = startSequence + count - 1; update bits 15-23
            *puVar1 = ((startSequence + count) * 0x8000 - 0x8000U ^ uVar2) & 0xff8000 ^ uVar2;
            return;
        }
    }
    // If no existing packet to extend, allocate a new packet header with type=3
    // Build header: (type=3) | (startSequence << 24) | ((startSequence+count-1) << 15)
    FUN_006438e0(
        (startSequence + count) * 0x8000 - 0x8000U | startSequence << 0x18 | 3,
        *(undefined4 *)(this[3] + 8)   // Allocator parameter (size? alloc function)
    );
    return;
}