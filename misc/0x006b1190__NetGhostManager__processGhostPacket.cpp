// FUNC_NAME: NetGhostManager::processGhostPacket
unsigned int NetGhostManager::processGhostPacket(unsigned int param_1, unsigned short* packetBuffer) {
    // packetBuffer[0] is packet type (must be between 5 and 7 inclusive)
    // packetBuffer[1] is number of ghost records in this packet
    // Each record starts at offset packetBuffer+10 (20 bytes), variable length

    if ((packetBuffer[0] <= 4) || (packetBuffer[0] >= 8)) {
        return 1; // unknown packet type, skip
    }
    unsigned char savedLock = FUN_0084ab30(0); // enter critical section
    unsigned int recordIndex = 0;
    unsigned short* currentRecord = packetBuffer + 10;
    while (recordIndex < packetBuffer[1]) {
        unsigned int ghostId = FUN_006b18e0(currentRecord); // read ghost ID from record header
        int isLocalGhost = FUN_006b0ee0(ghostId); // check if ghost is local
        int recordSize;
        if (isLocalGhost == 0) {
            // remote ghost: process creation/update (type independent)
            recordSize = FUN_006b2340(currentRecord);
        } else {
            // local ghost: process state update based on packet type
            recordSize = FUN_006b6a90(currentRecord, packetBuffer[0]);
        }
        currentRecord = (unsigned short*)((int)currentRecord + recordSize);
        ++recordIndex;
    }
    FUN_0084ab30(savedLock); // leave critical section
    return 1;
}