// FUNC_NAME: RingBuffer::removeByKey
uint __thiscall RingBuffer::removeByKey(int *pThis, int *pKey) {
    int iFound;
    int iCapacity;
    uint result;
    int iCount;
    int iReadStart;
    int iCurrent;
    int iTemp;
    int *pBuffer;
    int iKey;

    // Preserve low byte from EAX? Actually result initial is high part of EAX.
    result = in_EAX & 0xffffff00;

    iCount = pThis[3];          // +0x0C: number of elements
    if (iCount != 0) {
        iReadStart = pThis[1];  // +0x04: read start index (oldest element)
        iCapacity = pThis[2];   // +0x08: capacity (max elements)

        // Start at the newest element index
        iCurrent = iReadStart + iCount - 1;
        if (iCurrent >= iCapacity) {
            iCurrent -= iCapacity;
        }

        pBuffer = (int *)pThis[0];  // +0x00: pointer to buffer of 8-byte entries

        iKey = *pKey;
        iFound = pBuffer[iCurrent * 2];  // Compare first int of entry (key field)
        while (iFound != iKey) {
            if (iCurrent == iCapacity) {
                return result;  // Not found, return failure
            }
            iCurrent--;
            if (iCurrent < 0) {
                iCurrent += iCapacity;  // Wrap around
            }
            iFound = pBuffer[iCurrent * 2];
        }

        // Found at iCurrent. Remove by shifting all entries after it forward.
        if (iCurrent != iCapacity) {
            do {
                iTemp = iCurrent - 1;
                if (iTemp < 0) {
                    iTemp += iCapacity;
                }
                // Copy entry from iTemp to iCurrent
                pBuffer[iCurrent * 2] = pBuffer[iTemp * 2];
                pBuffer[iCurrent * 2 + 1] = pBuffer[iTemp * 2 + 1];
                iCurrent = iTemp;
            } while (iTemp != iReadStart);
        }

        // Advance read start (since we removed the oldest entry)
        iReadStart = pThis[1] + 1;      // +0x04 increment
        if (iReadStart >= iCapacity) {
            iReadStart -= iCapacity;
        }
        pThis[1] = iReadStart;

        // Decrease count
        pThis[3]--;  // +0x0C

        // Return success with the index of the removed element packed
        result = (iCurrent << 8) | 0x1;
    }
    return result;
}