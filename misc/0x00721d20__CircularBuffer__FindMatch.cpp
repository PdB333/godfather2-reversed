// FUNC_NAME: CircularBuffer::FindMatch
bool __thiscall CircularBuffer::FindMatch(int* this, int targetId, uint requiredFlags)
{
    int currentIndex = this[2];       // +0x08: current position in circular buffer
    int endIndex = this[1];           // +0x04: end index (exclusive)
    int capacity = this[0];           // +0x00: buffer capacity
    Entry* buffer = (Entry*)this[3];  // +0x0C: pointer to entry array (each 0x24 bytes)

    while (currentIndex != endIndex)
    {
        Entry* entry = &buffer[currentIndex];
        int storedId = entry->id;              // +0x00: stored ID (0 if slot empty)
        int actualId;
        if (storedId == 0)
            actualId = 0;
        else
            actualId = storedId - 0x48;        // subtract base offset to get real ID

        if (actualId == targetId && (entry->flags & requiredFlags) == requiredFlags)
            return true;                       // match found

        currentIndex++;
        if (currentIndex >= capacity)
            currentIndex = 0;                  // wrap around
    }
    return false;                              // no match
}