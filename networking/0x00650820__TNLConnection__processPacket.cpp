// FUNC_NAME: TNLConnection::processPacket
void __thiscall TNLConnection::processPacket(int *this, uint packetData)
{
    // Check if packet is valid (offset +0x210 = 0x84 * 4)
    if (this[0x84] == 0) {
        FUN_00653080("Invalid packet.");
        return;
    }
    // Call virtual function at vtable+0x58 (likely handlePacket or processPacketData)
    (**(code **)(*this + 0x58))();
    // Continue processing with the packet data
    FUN_00650930(this, packetData);
}