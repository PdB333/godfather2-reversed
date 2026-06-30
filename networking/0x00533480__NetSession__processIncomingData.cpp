// FUNC_NAME: NetSession::processIncomingData
// Address: 0x00533480 - Parses incoming network packet header/payload and processes ack
void __thiscall NetSession::processIncomingData(void)
{
    // 16 bytes: likely packet header (sequence, ack, flags)
    byte header[16];
    // 28 bytes: packet payload (mirrors TNL packet structure)
    byte payload[28];

    // FUN_00535640 - Reads payload and header from receive buffer (order: payload* then header*)
    readIncomingPacket(payload, header);
    // FUN_00534ea0 - Process acknowledgement window, update sequence numbers
    processAckWindow();
    // FUN_00534e20 - Unpack header fields into member variables
    unpackHeader(header);
}