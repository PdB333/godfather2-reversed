// FUNC_NAME: MessageManager::addMessage
int __thiscall MessageManager::addMessage(int this, short id1, short id2) {
    short *pUnicodeDest;
    char *pAsciiDest;
    int newBuffer;
    short *pUnicodeSrc;
    char *pAsciiSrc;
    uint charIndex;
    int maxLen;

    // If there are no existing entries, allocate initial buffer; otherwise reallocate (grow by one entry)
    if (*(ushort *)(this + 8) == 0) {
        newBuffer = allocateInitial();
    } else {
        // Reallocate to hold one more entry (size = count * 0xC4)
        newBuffer = reallocate(*(int *)(this + 0xc), 
                               (*(ushort *)(this + 8) + 1) * 0xC4 - 0xC4);
    }
    *(int *)(this + 0xc) = newBuffer;  // store new buffer pointer

    if (newBuffer == 0) {
        // Allocation failure: return error code (0x271e or 0x271e + -6)
        return (-(uint)(*(short *)(this + 8) != 0) & 0xfffffffa) + 0x271e;
    }

    // Write the two shorts (IDs) into the new entry at the current index
    *(short *)((uint)*(ushort *)(this + 8) * 0xC4 + newBuffer) = id1;               // +0x00
    *(short *)((uint)*(ushort *)(this + 8) * 0xC4 + 2 + *(int *)(this + 0xc)) = id2; // +0x02

    // Calculate pointer to the entry's ASCII string (offset +0x04)
    int entryBase = (uint)*(ushort *)(this + 8) * 0xC4 + *(int *)(this + 0xc);
    pUnicodeDest = (short *)(entryBase + 0x44);  // unicode starts at +0x44
    pAsciiDest = (char *)(entryBase + 4);        // ascii starts at +0x04

    // Copy two shorts from some global context (the "current" message text data)
    // Offsets 0x1e28/0x1e2a are copied to a derived object via global pointer at in_EAX+0x180
    *(short *)(*(int *)(in_EAX + 0x180) + 0x60) = *(short *)(this + 0x1e28);
    *(short *)(*(int *)(in_EAX + 0x180) + 0x62) = *(short *)(this + 0x1e2a);

    // Notify that a new entry is being added (e.g., increment something, update UI)
    FUN_00674e10();  // likely onEntryAdded()

    // Copy ASCII string from global context (in_EAX+0x50) into the entry's ASCII buffer (max 0x40 bytes)
    int srcAscii = *(int *)(in_EAX + 0x50);
    short *srcUnicode = *(short **)(in_EAX + 0x54);
    if (srcAscii == 0) {
        *pAsciiDest = '\0';
    } else {
        maxLen = 0x40;  // 64 bytes
        pAsciiSrc = (char *)srcAscii;
        do {
            if (pAsciiSrc[(int)pAsciiDest - (int)pAsciiSrc] == '\0') break;
            *pAsciiDest = pAsciiSrc[(int)pAsciiDest - (int)pAsciiSrc];
            pAsciiDest++;
            maxLen--;
        } while (maxLen != 0);
        *pAsciiDest = '\0';
    }

    // Copy Unicode (UTF-16) string from global context (in_EAX+0x54) into the entry's unicode buffer (max 0x40 shorts)
    if (srcUnicode == (short *)0x0) {
        *pUnicodeDest = 0;
    } else {
        charIndex = 0;
        if (*srcUnicode != 0) {
            do {
                if (0x7f < charIndex) break;  // max 128 bytes (64 shorts)
                *(short *)((int)pUnicodeDest - (int)srcUnicode + (int)srcUnicode) = *srcUnicode;
                srcUnicode++;
                charIndex++;
            } while (*srcUnicode != 0);
        }
        pUnicodeDest[charIndex] = 0;  // null-terminate
    }

    // If both strings are empty, generate a fallback string from the entry index
    if ((*pAsciiDest == '\0') && (*pUnicodeDest == 0)) {
        _sprintf(pAsciiDest, "%d", (uint)*(ushort *)(this + 8));
    }

    // Increment entry count
    *(short *)(this + 8) = *(short *)(this + 8) + 1;
    return 0;
}