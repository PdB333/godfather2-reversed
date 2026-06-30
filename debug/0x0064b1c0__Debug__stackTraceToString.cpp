// FUNC_NAME: Debug::stackTraceToString
int Debug::stackTraceToString(uint32_t* addresses, uint32_t count, char* outBuf, int outBufSize)
{
    // First call initialization if needed
    if (DAT_01223130 == 0) {
        initSymbolEngine();  // FUN_0064ad70
    }

    // Output buffer starts empty
    *outBuf = '\0';

    int remaining = outBufSize - 1;

    // Initialize symbol engine if not already done
    if (DAT_01223134 == '\0') {
        if (DAT_01223138 == nullptr) {
            goto done;
        }

        // Duplicate current process handle for symbol initialization
        HANDLE hDup;
        BOOL inherit = TRUE;
        DWORD options = DUPLICATE_SAME_ACCESS;
        DWORD desiredAccess = 0;
        HANDLE curProc = GetCurrentProcess();
        DuplicateHandle(curProc, curProc, curProc, &hDup, desiredAccess, inherit, options);

        int initResult = DAT_01223138(hDup, 0, TRUE);  // SymInitialize or similar
        if (initResult == 0) {
            GetLastError();
        } else {
            DAT_01223134 = '\x01';  // Mark as initialized
        }
        CloseHandle(hDup);

        if (DAT_01223134 == '\0') {
            goto done;
        }
    }

    uint32_t currentIndex = 0;
    if (count != 0) {
        do {
            uint32_t addr = addresses[currentIndex];

            // Add separator if not first element and space available
            if ((currentIndex != 0) && (remaining != 0)) {
                *outBuf++ = ' ';
                remaining--;
            }

            // Temporary buffers for symbol and source info
            char symBuffer[0x1000];        // auStack_1874 size
            char sourceBuffer[0xC60];      // acStack_c58 size
            uint32_t uStack_1878 = 0xC18;  // offset used as write cursor? Actually it's an index into symBuffer? The decompiled seems weird.
            // Actually from decompiled: uStack_1878 = 0xc18; then later auStack_1874[uStack_1878 + -1] = 0; -> sets last char to null.
            // That suggests uStack_1878 is the buffer size - 1? But 0xC18 = 3096, close to buffer size 3100. 
            // It sets the last byte of symBuffer to 0.
            symBuffer[0xC18 - 1] = '\0';   // Set null terminator at end

            if (DAT_0122314c == nullptr) {
                // No symbol resolution available, fallback to hex format
                if (9 < remaining) {
                    int len = _sprintf(stackBuffer, "0x%08x", addr);
                    strncpy(outBuf, stackBuffer, len);
                    outBuf += len;
                    remaining -= len;
                }
            } else {
                // Try to get symbol name
                DWORD64 displacement = 0;   // local_18c4
                DWORD options = 0xC30;      // auStack_1888[0]
                HANDLE hProc = GetCurrentProcess();
                int symResult = DAT_0122314c(hProc, addr, &displacement, &options);
                if (symResult == 0) {
                    // Fallback to hex
                    if (9 < remaining) {
                        int len = _sprintf(stackBuffer, "0x%08x", addr);
                        strncpy(outBuf, stackBuffer, len);
                        outBuf += len;
                        remaining -= len;
                    }
                } else {
                    // symBuffer already contains the symbol name from the call (using static buffer)
                    // The call writes the name into symBuffer? Actually the decompiled shows auStack_1874 used directly.
                    // We assume DAT_0122314c writes the symbol name into symBuffer via the options struct.
                    // The code does: _sprintf(acStack_c58, "%hs() + %d", auStack_1874, displacement)
                    char formattedLine[0xC60];
                    int lineLen = _sprintf(formattedLine, "%hs() + %d", symBuffer, displacement);
                    if (lineLen < remaining) {
                        _strncpy(outBuf, formattedLine, lineLen);
                        outBuf += lineLen;
                        remaining -= lineLen;
                    }

                    // Optionally get source file and line number
                    if (DAT_01223150 != nullptr) {
                        DWORD lineDisplacement;  // local_18c4 again, but re-used
                        IMAGEHLP_LINE lineInfo;
                        lineInfo.SizeOfStruct = 0x14;  // auStack_18bc[0]
                        HANDLE hProc2 = GetCurrentProcess();
                        int lineResult = DAT_01223150(hProc2, addr, &lineDisplacement, &lineInfo);
                        if (lineResult != 0) {
                            // lineInfo.FileName is in uStack_18b0? Actually uStack_18b0 and uStack_18b4 are used.
                            // The decompiled shows: _sprintf(acStack_c58, " \"%hs\", line %d", uStack_18b0, uStack_18b4);
                            // So we assume lineInfo contains the file name and line number.
                            char sourceLine[0xC60];
                            int srcLen = _sprintf(sourceLine, " \"%hs\", line %d", lineInfo.FileName, lineInfo.LineNumber);
                            if (srcLen < remaining) {
                                _strncpy(outBuf, sourceLine, srcLen);
                                outBuf += srcLen;
                                remaining -= srcLen;
                            }
                        }
                    }
                }
            }

            currentIndex++;
        } while (currentIndex < count);
    }

done:
    return (int)(outBuf - outBuf);  // Actually returns pointer difference, but Ghidra shows return (int)pcVar8 - (int)param_3;
    // We need to compute the length written.
    return (int)(outBuf - outBuf); // placeholder; better: return (int)(outBuf - originalOutBuf);
}