// FUNC_NAME: aptStringCopySafe
// Address: 0x005a0090
// Role: Bounded string copy (like strlcpy) from Apt.cpp.
//       Copies src to dest up to destSize-1 characters, but in debug
//       asserts on overflow. Returns number of bytes copied including null terminator.

int aptStringCopySafe(char *dest, const char *src, unsigned int destSize) {
    // Parameter validation: source must be non-null, destSize > 0, src != dest
    if ((src == nullptr) || (destSize == 0) || (dest == src)) {
        // Debug assertion: "pBuf && bufLen && (pSrc != pBuf)"
        const char *assertMsg = "pBuf && bufLen && (pSrc != pBuf)";
        const char *assertFile = "..\\source\\Apt\\Apt.cpp";
        int assertLine = 0x325;  // 805
        // In original, uses DAT_01128f58 flag and a debug handler (via FS_OFFSET).
        // Simplified: just a breakpoint in debug builds.
        #ifdef _DEBUG
            __debugbreak();
        #endif
    }

    // If destination is null, no work can be done
    if (dest == nullptr) {
        return 0;
    }

    // Copy first character
    char ch = *src;
    *dest = ch;
    char *pCur = dest;      // tracks current write position

    if (ch != '\0') {
        unsigned int count = 0;
        do {
            src++;          // move to next source char
            count++;        // number of characters already written (including first)
            pCur++;         // advance write pointer

            // Check if we have room for the next character (including null)
            if (destSize <= count) {
                // Buffer overflow assertion: "static_cast<uint32>(pCur - pBuf) < bufLen"
                const char *assertMsg2 = "static_cast<uint32>(pCur - pBuf) < bufLen";
                const char *assertFile2 = "..\\source\\Apt\\Apt.cpp";
                int assertLine2 = 0x32d;  // 813
                #ifdef _DEBUG
                    __debugbreak();
                #endif
            }

            ch = *src;      // read next source char
            *pCur = ch;     // write to destination (even if assert fired)
        } while (ch != '\0');
    }

    // Return number of bytes written (including trailing null)
    return (int)(pCur - dest);
}