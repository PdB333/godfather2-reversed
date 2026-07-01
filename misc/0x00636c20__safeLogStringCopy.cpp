// FUNC_NAME: safeLogStringCopy
void safeLogStringCopy(char* dst, const char* src, size_t maxLen)
{
    char c;
    size_t count;
    char *pSrc, *pDst, *pTemp;
    uint loopCount, remainder;

    // If source starts with '=', just copy the rest directly
    if (*src == '=') {
        _strncpy(dst, src + 1, maxLen);
        dst[maxLen - 1] = '\0';
        return;
    }

    // If source starts with '@', treat as a tag and copy after '@' with truncation
    if (*src == '@') {
        pSrc = src + 1;
        // Find end of source string
        pTemp = pSrc;
        while (*pTemp != '\0') pTemp++;
        // Clear destination
        *dst = '\0';
        pDst = dst + 1; // Will be used later? Actually we start from pSrc
        // Check if the tag content fits within maxLen-8 (reserve for ellipsis)
        if ((int)(maxLen - 8) < (int)(pTemp - (src + 2))) {
            // Truncate: move start pointer forward to fit
            pSrc = pSrc + ((pTemp - (src + 2)) - (maxLen - 8));
            // Append ellipsis marker (0x00e42294 = "..." as 4 bytes)
            pTemp = dst;
            while (*pTemp != '\0') pTemp++;
            *(uint*)pTemp = DAT_00e42294;
            pDst = pSrc;
        }
        // Copy the remaining source string (pSrc) into dst, appending
        pTemp = pSrc;
        while (*pTemp != '\0') pTemp++;
        pDst = dst;
        while (*pDst != '\0') pDst++;
        // 4-byte aligned copy for speed
        loopCount = (uint)(pTemp - pSrc) >> 2;
        for (; loopCount != 0; loopCount--) {
            *(uint*)pDst = *(uint*)pSrc;
            pSrc += 4;
            pDst += 4;
        }
        // Remaining bytes
        remainder = (pTemp - pSrc) & 3;
        for (; remainder != 0; remainder--) {
            *pDst = *pSrc;
            pSrc++;
            pDst++;
        }
        return;
    }

    // Otherwise, prepend a static prefix (e.g., "string: " with two extra chars at offset 8)
    count = _strcspn(src, "\n");
    // Write the first 8 bytes of prefix from static string at 0x00e42298
    *(uint64*)dst = s__string___00e42298._0_8_;
    if ((int)(maxLen - 0x11) < (int)count) {
        count = maxLen - 0x11;
    }
    // Write next 2 bytes of prefix
    *(uint16*)(dst + 8) = s__string___00e42298._8_2_;
    // If the source ends at newline, copy full source; else truncate and add ellipsis
    if (src[count] == '\0') {
        // Source ends at newline, copy entire string (length already capped)
        pSrc = src;
        while (*pSrc != '\0') pSrc++;
        loopCount = (int)(pSrc - src);
        pDst = dst;
        while (*pDst != '\0') pDst++;
        // 4-byte aligned copy
        loopCount = loopCount >> 2;
        for (; loopCount != 0; loopCount--) {
            *(uint*)pDst = *(uint*)src;
            src += 4;
            pDst += 4;
        }
        remainder = (int)(pSrc - src) & 3;
        for (; remainder != 0; remainder--) {
            *pDst = *src;
            src++;
            pDst++;
        }
    } else {
        // Source longer than allowed, copy truncated part
        _strncat(dst, src, count);
        pDst = dst;
        while (*pDst != '\0') pDst++;
        // Append ellipsis (4 bytes at 0x00e42294)
        *(uint*)pDst = DAT_00e42294;
    }
    // Always add the final three-character ellipsis terminator (0x00e422a4, 0x00e422a6)
    pDst = dst;
    while (*pDst != '\0') pDst++;
    *(uint16*)(pDst + 1) = DAT_00e422a4;    // two bytes at offset +1
    pDst[3] = DAT_00e422a6;                 // one byte at offset +3
    return;
}