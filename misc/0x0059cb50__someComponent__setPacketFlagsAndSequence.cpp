// FUNC_NAME: someComponent::setPacketFlagsAndSequence
void __thiscall setPacketFlagsAndSequence(void* this, uint sequenceNumber)
{
    // this points to a packet header or control block
    // Clear lower bits (0-2 and 12-16) and set flag bits 1 and 2 (value 6)
    // This sets some packet type flags (likely reliable/ordered/sequence)
    uint* header = (uint*)this;
    *header = *header & 0xffff8006 | 6; // Keep bit 1 and 2 set, clear others in lower 16 bits
    
    // Clear the 2-byte field at offset +2 (likely sub-flags or padding)
    *(undefined2*)((int)header + 2) = 0;
    
    // Set bit 15 (0x8000) - likely indicates "has sequence number"
    *header = *header | 0x8000;
    
    // Store the sequence number at offset +4
    header[1] = sequenceNumber;
    
    return;
}