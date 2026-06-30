// FUNC_NAME: NetSession::processEventList
// Function at 0x00628260: Write a sequence of event headers into a packet buffer, with rollback capability.
// The buffer pointer is at this+8, a stream state at this+0x10 (capacity/limit fields at +0x20/+0x24),
// and a secondary buffer at this+0x40.
// The event list (passed in EAX) is an array of 8-byte entries (type, data?) terminated by zero type.
void NetSession::processEventList(int finalizeFlag)
{
    int* eventList;   // in_EAX - pointer to array of event descriptors (set by caller)

    // Initial block: if finalizeFlag is nonzero, write a header and possibly rollback
    if (finalizeFlag != 0) {
        saveWriteState();
        int* header = getNextHeader();          // returns pointer to two ints (header template)
        int* writePtr = *(int**)(this + 8);     // current write position in buffer
        writePtr[-2] = header[0];                // copy header to buffer, moving back 8 bytes
        writePtr[-1] = header[1];
        int* newPtr = writePtr - 2;              // new buffer position after header

        if ((newPtr != nullptr) && (*newPtr == 0)) {
            *(int**)(this + 8) = newPtr;         // rollback if header indicates abort
            // Check buffer capacity: if current size <= limit, flush
            uint32_t* streamState = *(uint32_t**)(this + 0x10);
            if (streamState[0x20/4] <= streamState[0x24/4]) {
                flushBuffer();
            }

            int* bufPtr = *(int**)(this + 8);
            *bufPtr = 5;                         // event type = 5
            bufPtr[1] = getTimestamp(0, 0);      // timestamp
            *(int**)(this + 8) = bufPtr + 2;      // advance pointer

            saveWriteState();
            int* curBuf = *(int**)(this + 8);
            // Duplicate the just-written header (type5 + timestamp)
            *curBuf = curBuf[-4];
            curBuf[1] = curBuf[-3];
            *(int**)(this + 8) = curBuf + 2;

            // Validate/overwrite a region: from previous header start to current position
            moveAndRestore(
                this + 0x40,
                *(int*)(this + 8) - 0x10,
                *(int*)(this + 8) - 8
            );
            *(int**)(this + 8) = *(int**)(this + 8) - 0x10;
        }
        endWriteState();
    }

    // Process the event list: for each entry (type, data), rollback last 16 bytes of buffer
    int eventType;
    while ((eventType = *eventList) != 0) {
        saveWriteState();
        restoreWriteState();   // pair of push/pop (possibly leaving state unchanged)
        int* writePos = *(int**)(this + 8);
        // Revalidate/rollback the region from writePos-0x18 to writePos-8
        validateChunk(
            writePos - 6,
            writePos - 4,
            writePos - 2
        );
        *(int**)(this + 8) = writePos - 4;    // move buffer pointer back by 16 bytes (4 ints)
        eventList += 2;                        // advance to next event descriptor
    }

    // Trivial self-assignment (artifact)
    *(int**)(this + 8) = *(int**)(this + 8);
}