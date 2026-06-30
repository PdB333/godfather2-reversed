// FUNC_NAME: initPacketHeader
void __fastcall initPacketHeader(uint* headerPtr, uint sequenceNumber)
{
    // Clear bits 3-15, keep bits 0-2 and 16-31, then set bits 0-2 to 7 (packet type/flags)
    *headerPtr = (*headerPtr & 0xFFFF8007) | 7;
    // Zero out 16-bit field at offset +2 (likely padding or sub-type)
    *(uint16*)((int)headerPtr + 2) = 0;
    // Set bit 15 (0x8000) – possibly a flag (e.g., reliable or ack request)
    *headerPtr |= 0x8000;
    // Store sequence number at offset +4
    headerPtr[1] = sequenceNumber;
}