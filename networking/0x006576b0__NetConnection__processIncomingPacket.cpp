// FUNC_NAME: NetConnection::processIncomingPacket
void __thiscall NetConnection::processIncomingPacket(void* thisConn, int context, PacketStream* packet)
{
    int packetState = packet->state; // +0x6d (offset 0x1b4) – packet type/state
    if (packetState == 1 || packetState == 4) {
        // Type 1=connection request, 4=acknowledgement – call virtual read handler
        (**(code (__thiscall ***)(void*))(*packet + 0xc))(thisConn); // vtable+0xc: readPacket
        NetSendReliablePacket(); // FUN_006550d0 – send ack
    }
    else if (packetState == 7) {
        // Type 7=reliable data – transition to type 8, call virtual write handler
        auto writeFunc = (code (__thiscall *)(void*))(*packet + 0x10); // vtable+0x10: writePacket
        packet->state = 8; // +0x6d
        writeFunc(thisConn);
        if (packet->someFlag == 0) { // +0x49 (offset 0x124)
            netInitBuffer(); // FUN_0064f2d0
            memcpy(8, &stackBuf, ...); // FUN_0064b810(8, &stackBuf) – copy 8 bytes
            memcpy(0x40, (uchar*)packet + 0x133); // FUN_0064b810 – copy 64 bytes from packet+0x133
            memcpy(0x40, (uchar*)packet + 0x13b); // FUN_0064b810 – copy another 64 bytes from packet+0x13b
            computeChecksum(in_EAX, 0xff); // FUN_0064c760 – in_EAX likely packet->checksum or thisConn
            if (*(uchar*)((int)packet + 0x131) != '\0') { // null-terminated string flag at +0x131
                // Copy string from packet to local buffer (644 bytes) and process
                char* strBuf = (char*)((__int64)&stackBuf + 0x288); // local buffer
                strncpy(strBuf, packet->string, ...); // FUN_0065a5e0 – copy string
                decryptBuffer((stackBufSize + 7U) >> 3, strBuf); // FUN_0064c980 – decrypt/process
                finalizeDecryption(); // FUN_00656aa0
            }
            // Parse packet payload into context structure
            parsePacketData(context + 0x5c, (int*)packet + 0x40); // FUN_0064cb60 – context handles packet
            sendUnreliable(); // FUN_0064b440 – send response
        }
        // Send unreliable packet (part of normal flow)
        netSendUnreliable(context, packet); // FUN_006552f0
    }
}