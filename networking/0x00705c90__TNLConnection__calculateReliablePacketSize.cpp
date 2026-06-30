// FUNC_NAME: TNLConnection::calculateReliablePacketSize
int __thiscall TNLConnection::calculateReliablePacketSize(void)
{
    uint numProcessed = 0;
    int* entryPtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x18);
    int offset = 8;

    // Process 11 entries (e.g., reliable event descriptors or ghost updates)
    do {
        int currentOffset = offset + 4; // Base increment for this entry

        // Check if the entry is active and valid: type != 0, type != 0x48 (possibly a sentinel/empty), and size > 0
        if ((*entryPtr != 0) && (*entryPtr != 0x48) && (entryPtr[2] != 0))
        {
            currentOffset = offset + 0x24; // Additional payload size for active entry
            if (numProcessed < 5)
            {
                currentOffset = offset + 0x2C; // Even larger payload for first 5 entries
            }
        }
        // If entry is not active, use minimal increment (offset+4)

        numProcessed++;
        entryPtr += 5; // Each entry is 5 ints (20 bytes)
        offset = currentOffset; // Accumulate total offset

    } while (numProcessed < 11);

    offset += 4; // Final alignment/padding

    // If optional extra data is present, add its size
    if (*reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(this) + 0x144) != 0)
    {
        offset += *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x13C);
    }

    return offset + 4; // Total payload size (including trailing overshoot? possibly header)
}