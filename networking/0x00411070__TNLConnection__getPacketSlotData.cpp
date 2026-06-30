// FUNC_NAME: TNLConnection::getPacketSlotData
// 0x00411070 - Returns a 32-bit value from the per-slot array at offset 0x4EC (packet window data, likely sequence or ack number)
// slotIndex: byte index into the 32-slot array (0-31)
int __thiscall TNLConnection::getPacketSlotData(void* this, byte slotIndex)
{
    // Array of ints at this+0x4EC, each slot 4 bytes
    return *(int*)((char*)this + 0x4EC + (uint)slotIndex * 4);
}