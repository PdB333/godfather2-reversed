// FUNC_NAME: NetSession::sendReliablePacket

void __fastcall NetSession::sendReliablePacket(NetSession* this) {
    NetConnection* connection;
    NetPacket* packet;
    
    // Get the current connection from the session (offset +0x2098)
    connection = *(NetConnection**)((int)this + 0x2098);
    
    // Allocate a new reliable packet (FUN_00acd310 is packet allocator)
    packet = NetPacket::allocate(0, 0);
    
    // Call virtual method at vtable+0x28 (likely sendReliable) on the connection
    // The first argument is 0 (perhaps a send flag or sequence number)
    (connection->vtable->sendReliable)(0, packet);
    
    // Flush the send buffer to push the packet out
    NetConnection::flushSend();
}