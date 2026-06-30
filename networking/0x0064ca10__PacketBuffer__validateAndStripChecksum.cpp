// FUNC_NAME: PacketBuffer::validateAndStripChecksum
// Address: 0x0064ca10
// Checks if last 5 bytes of buffer (from offset) match a computed hash, then truncates the buffer by 5 bytes if valid.
// Uses SHA1-like hashing (functions at 0x0065a7f0, 0x006595c0, 0x00659640, 0x00659730).

bool PacketBuffer::validateAndStripChecksum(BufferDescriptor* buf, uint startOffset, uint seed) {
    uint bufSize = buf->m_size;          // +0x10
    uint8* bufData = buf->m_data;        // +0x0c
    bool isAllocated = buf->m_allocated; // +0x14

    // Need at least 5 bytes beyond startOffset for the checksum
    if (bufSize < startOffset + 5) {
        return false;
    }

    // Copy or process data? (likely seeds the hash context with the seed)
    FUN_0065a7f0(seed, bufData + startOffset, bufData + startOffset, bufSize - startOffset);

    // Initialize hash context (SHA1-like)
    uint8 hashCtx[244];
    FUN_006595c0(hashCtx + 0x20); // context offset 0x20

    uint newSize = bufSize - 5; // size after removing checksum
    // Feed entire actual data (excluding the last 5 checksum bytes) into hash
    FUN_00659640(hashCtx + 0x20, bufData, newSize);
    // Finalize hash – result stored in hashCtx[0..19] (20 bytes)
    FUN_00659730(hashCtx + 0x20, hashCtx);

    // Compare last 5 bytes of buffer with first 5 bytes of hash
    uint8* expected = (uint8*)(bufData + bufSize - 5); // last 5 bytes
    uint8* computed = hashCtx;                         // first 5 bytes of computed hash
    uint remaining = 5;
    int cmp = 0;
    // Compare 4-byte chunks first, then remainder
    while (remaining > 3) {
        if (*(uint32*)expected != *(uint32*)computed) {
            goto compare_bytewise;
        }
        expected += 4;
        computed += 4;
        remaining -= 4;
    }
    if (remaining == 0) {
        cmp = 0;
        goto done;
    }

compare_bytewise:
    cmp = (int)*expected - (int)*computed;
    if (cmp == 0) {
        if (remaining == 1) goto done;
        cmp = (int)*(expected+1) - (int)*(computed+1);
        if (cmp == 0) {
            if (remaining == 2) goto done;
            cmp = (int)*(expected+2) - (int)*(computed+2);
            if (cmp == 0) {
                if (remaining == 3) goto done;
                cmp = (int)*(expected+3) - (int)*(computed+3);
                if (cmp == 0) goto done;
            }
        }
    }
    // Convert to sign: 1 if positive, -1 if negative
    if (cmp > 0) cmp = 1;
    else if (cmp < 0) cmp = -1;

done:
    bool match = (cmp == 0);
    if (match) {
        if (newSize <= buf->m_size) {
            buf->m_size = newSize;
            return true;
        }
        // If buffer was allocated and needs to shrink, re-allocate
        if (isAllocated) {
            buf->m_size = newSize;
            buf->m_data = (uint8*)_realloc(buf->m_data, newSize);
        }
    }
    return match;
}