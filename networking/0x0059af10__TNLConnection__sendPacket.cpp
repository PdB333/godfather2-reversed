// FUNC_NAME: TNLConnection::sendPacket
void __fastcall TNLConnection::sendPacket(int this)
{
    int packetBuffer;
    int connection;
    int dataSize;
    short sizeShort;
    undefined4 unaff_EBP;
    undefined4 unaff_EDI;
    
    // Check if there's a pending reliable packet to send (+0x1c0 = mReliablePacket)
    if (*(int *)(this + 0x1c0) != 0) {
        // Get the packet buffer (+0x08 = mPacketBuffer)
        packetBuffer = *(int *)(this + 8);
        
        // Validate buffer capacity: buffer size at +0x02 must equal dataSize * 0x20 + 8
        if ((uint)*(ushort *)(packetBuffer + 2) != *(int *)(packetBuffer + 4) * 0x20 + 8U) {
            // Assertion failure
            (**(code **)(*DAT_01205590 + 4))();
        }
        
        // Call virtual function at vtable+0x34 on the reliable packet object
        // This is likely buildReliablePacket(1, 1, 0)
        (**(code **)(**(int **)(this + 0x1c0) + 0x34))(1, 1, 0);
        
        // Get data size from packet buffer (+0x04)
        dataSize = *(int *)(packetBuffer + 4);
        connection = *(int *)(this + 0x1c0);
        
        // Validate data size fits in 16 bits
        if (0xffff < dataSize) {
            (**(code **)(*DAT_01205590 + 4))();
        }
        
        sizeShort = (short)dataSize;
        if (sizeShort != 0) {
            // Set up packet header fields:
            // +0x4C = sequence number (0)
            // +0x50 = packet type (1 = reliable)
            // +0x52 = data size
            // +0x58 = pointer to packet data (buffer + 8)
            // +0x54 = flags (0)
            *(undefined4 *)(connection + 0x4c) = 0;
            *(undefined2 *)(connection + 0x50) = 1;
            *(short *)(connection + 0x52) = sizeShort;
            *(int *)(connection + 0x58) = packetBuffer + 8;
            *(undefined2 *)(connection + 0x54) = 0;
        }
        
        // Set flag bit 0x10 (has reliable data)
        *(uint *)(connection + 4) = *(uint *)(connection + 4) | 0x10;
        
        // Second packet segment (likely for ACK list)
        dataSize = *(int *)(packetBuffer + 4);
        connection = *(int *)(this + 0x1c0);
        if (0xffff < dataSize) {
            (**(code **)(*DAT_01205590 + 4))();
        }
        sizeShort = (short)dataSize;
        if (sizeShort != 0) {
            // +0x5C = sequence number (0)
            // +0x60 = packet type (1)
            // +0x62 = data size
            // +0x68 = EBP register value (likely ACK mask)
            // +0x64 = flags (0)
            *(undefined4 *)(connection + 0x5c) = 0;
            *(undefined2 *)(connection + 0x60) = 1;
            *(short *)(connection + 0x62) = sizeShort;
            *(undefined4 *)(connection + 0x68) = unaff_EBP;
            *(undefined2 *)(connection + 100) = 0;
        }
        
        // Set flag bit 0x20 (has ACK data)
        *(uint *)(connection + 4) = *(uint *)(connection + 4) | 0x20;
        
        // Third packet segment (likely for additional data)
        dataSize = *(int *)(packetBuffer + 4);
        connection = *(int *)(this + 0x1c0);
        if (0xffff < dataSize) {
            (**(code **)(*DAT_01205590 + 4))();
        }
        sizeShort = (short)dataSize;
        if (sizeShort != 0) {
            // +0x6C = sequence number (0)
            // +0x70 = packet type (1)
            // +0x72 = data size
            // +0x78 = EDI register value (likely additional data)
            // +0x74 = flags (1)
            *(undefined4 *)(connection + 0x6c) = 0;
            *(undefined2 *)(connection + 0x70) = 1;
            *(short *)(connection + 0x72) = sizeShort;
            *(undefined4 *)(connection + 0x78) = unaff_EDI;
            *(undefined2 *)(connection + 0x74) = 1;
        }
        
        // Set flag bit 0x40 (has additional data)
        *(uint *)(connection + 4) = *(uint *)(connection + 4) | 0x40;
    }
}