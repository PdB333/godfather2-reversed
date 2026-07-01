// FUNC_NAME: NetConnection::sendPingPacket

void __thiscall NetConnection::sendPingPacket(void) {
  // Get the global packet sender (likely a singleton)
  PacketSender* sender = GetPacketSender(); // FUN_009c8f80

  // Build a ping packet header: type=2 (PING), size=0x10, flags=0
  struct PingPacketHeader {
    int type;   // +0x00
    int size;   // +0x04
    int flags;  // +0x08
  } header;

  header.type = 2;
  header.size = 0x10;
  header.flags = 0;

  // Call virtual sendPacket(this, &header) on the sender
  sender->sendPacket(this, &header);
}