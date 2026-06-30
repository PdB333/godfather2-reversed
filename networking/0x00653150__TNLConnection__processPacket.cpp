// FUNC_NAME: TNLConnection::processPacket
void __thiscall TNLConnection::processPacket(int* thisPtr, int packetBuf)
{
    double dVar1;
    char cVar2;
    int iVar3;

    // Rate-limit check: if packet time threshold differs from global constant
    if (*(float*)(thisPtr + 0x33) != DAT_00e2b05c) {
        iVar3 = FUN_0065bf40(); // Get current time (e.g., milliseconds)
        dVar1 = (double)iVar3;
        if (iVar3 < 0) {
            dVar1 += _DAT_00e44708; // Wrap around for signed -> unsigned double
        }
        // Compare weighted time against stored threshold
        if (dVar1 * _DAT_00e448a8 < (double)*(float*)(thisPtr + 0x33)) {
            return; // Skip processing if within rate limit
        }
    }

    gbPacketInvalid = '\0'; // Clear global invalid flag
    cVar2 = FUN_00653400(packetBuf); // Validate packet header (size, checksum, type)
    if (cVar2 == '\0') {
        return; // Invalid packet
    }

    // Store current timestamp from session manager into this
    thisPtr[3] = *(int*)(*(int*)(thisPtr + 0x69) + 100); // mSession +0x64 offset

    FUN_00653800(thisPtr); // Process packet header (sequence, ack, etc.)

    // Write sequence number into packet buffer at +0x34
    *(int*)(packetBuf + 0x34) = thisPtr[0x72]; // mRemoteSequence

    // Virtual call to handle packet data (vtable+0x30)
    (*(code**)(*thisPtr + 0x30))(packetBuf);

    // Check if packet indicates an error
    if (*(char*)(packetBuf + 0x1c) != '\0') {
        if (gbPacketInvalid != '\0') goto LAB_00653200;
        FUN_00653080("Invalid Packet."); // Log error
    }

    if (gbPacketInvalid == '\0') {
        gbPacketInvalid = 0;
        return;
    }

LAB_00653200:
    // Handle invalid packet: call disconnect/recover routine
    FUN_006576b0(*(int*)(thisPtr + 0x69), thisPtr); // mSession, connection
    gbPacketInvalid = 0;
    return;
}