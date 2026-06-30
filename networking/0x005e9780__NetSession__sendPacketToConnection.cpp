// FUNC_NAME: NetSession::sendPacketToConnection
// Address: 0x005e9780
// Role: Attempts to send a reliable packet to a connection. Returns sequence number on success, -1 on failure.
// Checks if the connection's send channel (at +0x484) is valid, then calls a virtual method on the global network session (DAT_01223510) 
// with the packet sequence ID from the connection (+0x1CC).

// Note: param_1 (ECX) is unused in this version; likely passed for calling convention compatibility.
int __fastcall NetSession::sendPacketToConnection(NetSession* this, NetConnection* connection)
{
    int result = -1;
    // +0x484: Pointer to a send channel / packet sender (non-null indicates connection is active)
    if (connection->sendChannel != nullptr) {
        // Call virtual function at offset 0x68 in the global NetSession's vtable
        // This function likely returns a packet sequence number or 0 on success
        result = (*(int (__fastcall**)(int))(*DAT_01223510 + 0x68))(connection->packetSequenceId); // +0x1CC: packet sequence ID to send
    }
    return result;
}