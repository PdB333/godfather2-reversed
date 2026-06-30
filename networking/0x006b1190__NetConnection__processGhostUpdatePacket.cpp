// FUNC_NAME: NetConnection::processGhostUpdatePacket
int __thiscall NetConnection::processGhostUpdatePacket(void *this, ushort *packetHeader)
{
    uint recordIndex;
    ushort *recordPtr;
    int totalRecordSize;
    int objectId;
    int lockHandle;

    // Packet header: first ushort is packet type (must be 5,6,7), second is count of records
    if ((*packetHeader > 4) && (*packetHeader < 8)) {
        lockHandle = (int)mutexLock(0); // Acquire critical section (0 indicates default)
        recordIndex = 0;
        recordPtr = packetHeader + 10; // Records start after header (10 ushorts? maybe 20 bytes)
        if (packetHeader[1] != 0) {
            do {
                objectId = readObjectIdFromRecord(recordPtr); // Extracts object ID from the record
                if (doesObjectExist(objectId) == 0) {
                    totalRecordSize = createObjectFromRecord(recordPtr); // Create object if not existing
                }
                else {
                    totalRecordSize = updateObjectFromRecord(recordPtr, *packetHeader); // Update existing, packet type used as flag
                }
                recordIndex = recordIndex + 1;
                recordPtr = (ushort *)((int)recordPtr + totalRecordSize); // Advance by record size
            } while (recordIndex < packetHeader[1]);
        }
        mutexUnlock(lockHandle);
    }
    return 1;
}