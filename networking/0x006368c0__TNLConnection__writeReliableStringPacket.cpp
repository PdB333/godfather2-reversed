// FUNC_NAME: TNLConnection::writeReliableStringPacket
void __fastcall TNLConnection::writeReliableStringPacket(TNLConnection* this, char* str) {
    int* pWritePos = *(int**)((int)this + 8); // +0x8: current write pointer in packet buffer
    *pWritePos = 4; // Packet type: reliable data with string
    // Scan string to end (strlen inlined, result unused here because string is written elsewhere?)
    char c;
    do {
        c = *str;
        str++;
    } while (c != '\0');
    int seqOrHash = FUN_00638920(); // Possibly get next sequence number or hash
    pWritePos[1] = seqOrHash; // 4-byte value after type
    // Check if buffer has space for 8+1 = 9 bytes (8 header + null terminator)
    int currentPos = *(int*)((int)this + 8);
    int bufferEnd = *(int*)((int)this + 0x18); // +0x18: end of buffer
    if (bufferEnd - currentPos < 9) {
        FUN_00635c70(); // Flush buffer or enlarge
    }
    *(int*)((int)this + 8) = currentPos + 8; // Advance write pointer by 8 bytes
}