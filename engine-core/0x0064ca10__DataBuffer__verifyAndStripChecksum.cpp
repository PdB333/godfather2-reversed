// FUNC_NAME: DataBuffer::verifyAndStripChecksum

bool __thiscall DataBuffer::verifyAndStripChecksum(int this, DataBuffer* buffer, uint checksumOffset)
{
    uint dataSize = *(uint*)(buffer + 0x10);
    byte* dataPtr = *(byte**)(buffer + 0x0C);

    // Need at least 5 bytes for the checksum
    if (dataSize < checksumOffset + 5) {
        return false;
    }

    // Copy input into the buffer? (param_3 usage unclear)
    // FUN_0065a7f0(checksumOffset, dataPtr + checksumOffset, dataPtr + checksumOffset, dataSize - checksumOffset);
    // Presumably initializes or copies some context

    // Initialize hash state
    uint hashState[61]; // local_f4 is 244 bytes, assume a hash context structure
    FUN_006595c0(&hashState[8]); // init

    // Feed data to hash (excluding last 5 bytes)
    uint newSize = dataSize - 5;
    FUN_00659640(&hashState[8], dataPtr, newSize);

    // Finalize hash, store result in hashState[0..4] (5 bytes)
    FUN_00659730(&hashState[8], hashState);

    // Compare computed hash with stored hash (last 5 bytes of data)
    byte* storedHash = dataPtr + newSize; // = dataPtr + dataSize - 5
    int cmpResult = memcmp(hashState, storedHash, 5);

    bool hashMatch = (cmpResult == 0);

    if (hashMatch) {
        // If hash matches, optionally truncate the buffer (remove the hash)
        if (newSize <= *(uint*)(buffer + 0x10)) {
            *(uint*)(buffer + 0x10) = newSize;
        } else {
            // Only reallocate if the flag allows it
            if (*(char*)(buffer + 0x14) != '\0') {
                *(uint*)(buffer + 0x10) = newSize;
                void* newBuffer = _realloc(*(void**)(buffer + 0x0C), newSize);
                *(void**)(buffer + 0x0C) = newBuffer;
            }
        }
    }

    return hashMatch;
}