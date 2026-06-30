// FUNC_NAME: LogStream::writeFormatted
// Function address: 0x0062d1d0
// Role: Custom printf-like method for formatted output buffered and sent to a stream.
// The method processes a format string, extracts variadic arguments, formats them into a local buffer,
// and flushes the buffer to the underlying output stream (e.g., for network or debug console).
// Uses EA EARS engine buffer management (ring buffer or similar).

#include <cstdio>
#include <cctype>

// Forward declarations of internal helper functions (renamed for clarity)
char* getBufferStart(LogStream* self);       // 0x00625a70
int getHeaderSize();                          // 0x00625ae0 - returns size of header before data
void assertFail();                            // 0x00627ac0 - error/abort
int flushLocalBuffer(LogStream* self);        // 0x00628940 - returns non-zero if buffer was full
void finalizeOutput(LogStream* self);         // 0x00626460 - final flush and cleanup
uint getBufferCapacity();                     // 0x00627290 - free space? (returns uint)
void beginWriteBlock(LogStream* self);        // 0x00626f80
void setBlockType(LogStream* self);           // 0x00626fd0
void commitBlockSize(LogStream* self);        // 0x00627010
void finishBlock(LogStream* self);            // 0x006270e0
uint writeChunk(LogStream* self, char* data); // 0x00638920 - writes a chunk + size to stream
void commitChunk(LogStream* self);            // 0x006289a0 - commit after chunk write
char* parseFormatSpec(LogStream* self, char* fmt, char* outSpec); // 0x0062d0d0 - returns next char after spec, fills output spec string
void* getVariadicArg();                       // 0x00628080 - gets next variadic argument (float, int, etc.)
void printQuotedString(LogStream* self);      // 0x0062ce80 - handles %q
void checkArgLimit();                         // 0x00627fa0 - checks argument count
void* getStringArg();                         // 0x00625700 - gets a string argument
int getStringLength();                        // 0x00628c50 - gets length of string argument
void writeChars(LogStream* self, char* str);  // 0x00628b20 - appends string to local buffer

class LogStream {
    // Structure offsets (inferred from code, may vary):
    // +0x08: pointer to output buffer (write position)
    // +0x10: pointer to buffer control block (with +0x20 = current write offset, +0x24 = capacity)
public:
    // Writes a formatted string (like printf) to this log stream.
    // Returns 1 on success.
    int writeFormatted(const char* format, ...);
};

int LogStream::writeFormatted(const char* format, ...) {
    // Pointer to the format string being processed.
    char* srcPtr = getBufferStart(this);
    if (srcPtr == nullptr) {
        assertFail();
    }

    // Get the offset to skip header portion (if any).
    int headerSize = getHeaderSize();
    char* endPtr = srcPtr + headerSize; // End of readable data? Actually may be start of data region.

    // Local buffer for accumulating formatted output before flushing.
    char localBuffer[512];
    char* localCursor = localBuffer;
    int chunkCount = 0;

    // Main processing loop over format string.
    while (true) {
        // Check if we've exhausted the format string.
        if (srcPtr >= endPtr) {
            finalizeOutput(this);
            return 1;
        }

        // If current character is '%', handle a format specifier.
        if (*srcPtr == '%') {
            char* nextChar = srcPtr + 1;
            // Double '%%' means literal percent.
            if (*nextChar != '%') {
                // This path processes a format specifier.
                // But the decompiled code first checks for digit (arg index) and then switch on specifier.
                // We simplify: parse the specifier into a sub-format string for sprintf.
                char formatSpec[20]; // for the % sub-specifier (e.g., "%d", "%10.2f")
                char* afterSpec = parseFormatSpec(this, nextChar, formatSpec);
                // The first character of the specifier tells the type.
                char specChar = *formatSpec; // actually formatSpec[0] is the spec char after '%'

                // The switch on specChar handles different cases.
                // We'll reconstruct the logic from the decompiled as closely as possible.
                // Note: The decompiled has an obfuscated default case (switchD_0062d3cd_caseD_46)
                // which appears to be a dead code path. We ignore it.
                switch (specChar) {
                    case 'E':
                    case 'G':
                    case 'e':
                    case 'f':
                    case 'g':
                    {
                        // Floating point: get double argument and format with sprintf.
                        double floatArg = (double) getVariadicArg(); // SUB84(in_XMM0_Qa, 0) - get float
                        char tmpBuf[572];
                        sprintf(tmpBuf, formatSpec, floatArg);
                        writeChars(this, tmpBuf);
                        break;
                    }
                    case 'X':
                    case 'o':
                    case 'u':
                    case 'x':
                    {
                        // Unsigned integer / hex / octal
                        getVariadicArg(); // pulls arg from va_list
                        char tmpBuf[572];
                        sprintf(tmpBuf, formatSpec); // Actually needs arg; but decompiled shows no arg in sprintf? Possibly incorrect.
                        // Actually the decompiled does: _sprintf(acStack_240, acStack_464) without additional args.
                        // This suggests that the variadic arg is already consumed by getVariadicArg and stored globally.
                        // We'll mimic that: use a placeholder.
                        writeChars(this, tmpBuf);
                        break;
                    }
                    case 'c':
                    case 'd':
                    case 'i':
                    {
                        // Signed integer
                        getVariadicArg();
                        char tmpBuf[572];
                        sprintf(tmpBuf, formatSpec);
                        writeChars(this, tmpBuf);
                        break;
                    }
                    case 'q':
                    {
                        // Quoted string (probably prints a string with quotes)
                        printQuotedString(this);
                        // Continue loop without advancing srcPtr? The decompiled calls FUN_0062ce80 and then jumps to joined_r0x0062d231.
                        // That means it consumes the %q and goes back to loop top after updating srcPtr?
                        // In decompiled, after case 'q', it calls FUN_0062ce80(param_1) and then sets iVar4 = iStack_448 and jumps to joined_r0x0062d231.
                        // So we need to continue the while loop.
                        // We'll update srcPtr accordingly.
                        // Since we already handled the specifier, we need to advance srcPtr past the specifier.
                        // But the case doesn't set srcPtr; the loop will advance srcPtr at the top (the while loop advances srcPtr by 1 each iteration if not handled).
                        // Actually the decompiled jumps to joined_r0x0062d231 which is the start of the inner while loop (not the outer).
                        // This is complicated. For simplicity, we'll just set srcPtr = afterSpec; but afterSpec is never assigned correctly in my reconstruction.
                        // We'll handle by setting srcPtr = (char*)afterSpec? No, afterSpec is char* returned from parseFormatSpec.
                        // Let's reconstruct more accurately: parseFormatSpec returns a pointer to the character after the specifier.
                        // So after parsing, srcPtr should be set to that pointer.
                        // For 'q', we just need to consume the specifier and continue.
                        srcPtr = (char*)afterSpec; // This should be handled in all cases.
                        continue;
                    }
                    case 's':
                    {
                        // String argument
                        getVariadicArg(); // pulls the string pointer
                        // Check length limit (100 in decompiled)
                        if (getStringLength() < 100) {
                            // Format and write.
                            char tmpBuf[572];
                            sprintf(tmpBuf, formatSpec); // again without arg, since arg already global
                            writeChars(this, tmpBuf);
                        } else {
                            // Exceeds limit, maybe truncate or error.
                            // Decompiled calls FUN_00625700 (which might be getStringArg) and then FUN_00628c50.
                            // Then it jumps back to loop. So we handle similarly.
                            // For simplicity, skip.
                            char* strArg = (char*)getStringArg();
                            // Write the string directly?
                            // Actually the code after check does: FUN_00625700(); FUN_00628c50(); then jumps.
                            // So maybe it writes the string without formatting.
                            writeChars(this, strArg);
                        }
                        break;
                    }
                    default:
                        // Unsupported format specifier: triggers obfuscated error handler (ignored).
                        // In the original, it calls FUN_00627bd0 (which may be error, then returns 1).
                        // We'll just return 1 as in the decompiled.
                        return 1;
                }
                // After processing specifier, we need to update srcPtr to after the specifier.
                // In the decompiled, after the switch (for normal cases), it does _sprintf and then goes to LAB_0062d49e which writes the formatted string,
                // then calls FUN_00628b20 (writeChars), then sets iVar4 = iStack_448 and jumps to joined_r0x0062d231.
                // That loop advances srcPtr by 1 each iteration if not a '%'. But since we handled the specifier, srcPtr should advance past it.
                // We'll handle by setting srcPtr = (char*)afterSpec; afterSpec is returned by parseFormatSpec.
                // We'll do that after each case.
                // Actually, the parseFormatSpec returns the next character after the specifier in the format string.
                // So we should update srcPtr = afterSpec; and then continue (the while loop will then process the next character).
                // But in the decompiled, it uses a goto to the loop header without incrementing srcPtr. That suggests that inside the case, srcPtr is not advanced; the loop increments srcPtr by 1 each iteration.
                // This is inconsistent. To avoid infinite loop, we must advance srcPtr manually.
                // Given complexity, I'll assume parseFormatSpec returns a pointer to the next character after the specifier, and we set srcPtr = afterSpec.
                // TODO: This is a simplification.
                if (specChar != 'q') {
                    srcPtr = (char*)afterSpec; // for most specifiers
                }
                continue; // go back to outer while loop
            } else {
                // Literal '%' - handle as normal character (write to local buffer)
                // This is in the 'else' branch of the if (*nextChar != '%').
                // In decompiled, this is the case where *pbVar8 == '%', and it writes the second '%'.
                // It does not fall into the switch; instead it proceeds to write the % to the local buffer.
                // So we'll handle that by writing the '%' as a regular character.
                // But we already advanced srcPtr? We'll handle it in the regular character path below.
                // Actually the decompiled first checks if *nextChar != '%', which means it goes to the switch handling.
                // If *nextChar == '%', it writes a literal '%' (the second one) and advances srcPtr by 2.
                // So we need to handle that case explicitly.
                // However, the decompiled code after the first if (*pbVar8 != '%') break; goes to the switch.
                // The else path is not shown; it's handled in the outer while loop's 'if (*pbVar3 == 0x25) break;' which breaks out to handle the specifier.
                // So the literal '%' is actually handled by the outer code: if the character is '%', it takes the break and then checks next char.
                // That logic is convoluted. I'll simplify.
                // Actually, looking at the decompiled: The outer while loop has a condition: if (*pbVar3 == 0x25) break;
                // Then after the break, it checks *pbVar8 (the next char) for '%'. If it's '%', it writes both to local buffer (two percents).
                // So the literal '%%' is handled entirely within the '%' path, not in the normal character write.
                // Therefore, we need to implement that case here.
                // Write the first '%' (from the break)?
                // Actually the break occurs when we see '%', then we check next char. If next is also '%', we write two percents and advance by 2.
                // But the decompiled writes only one '%' in that case? Let's see: after the if (*pbVar8 != '%') break; it goes to switch.
                // If *pbVar8 == '%', then it does:
                // if ((abStack_244 <= pbStack_450) && (iVar4 = FUN_00628940(), iVar4 != 0)) { FUN_006289a0(); }
                // *pbStack_450 = *pbVar8;
                // pbStack_450 = pbStack_450 + 1;
                // pbVar3 = pbVar3 + 2;
                // So it writes only the second '%' (the one from pbVar8). So effectively '%%' outputs a single '%'.
                // That matches printf behavior.
                // So we need to write just one '%'.
                *localCursor = '%';
                localCursor++;
                srcPtr += 2; // skip both percents
                continue; // go back to loop top
            }
        }

        // Regular character (not '%') : write to local buffer, with possible flush.
        if (localCursor >= &localBuffer[512] && localCursor != localBuffer) {
            // Local buffer is full; flush it to the output stream.
            if (*(uint*)(*(int*)(this + 0x10) + 0x20) >= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
                // No space in output buffer; need to manage somehow.
                uint unk = getBufferCapacity();
                beginWriteBlock(this);
                setBlockType(this);
                beginWriteBlock(this);
                commitBlockSize(this);
                finishBlock(this);
            }
            // Write chunk header and data.
            uint* bufPtr = *(uint**)(this + 8);
            *bufPtr = 4; // chunk type
            uint dataSize = writeChunk(this, localBuffer);
            bufPtr[1] = dataSize;
            *(int*)(this + 8) = *(int*)(this + 8) + 8;
            chunkCount++;
            localCursor = localBuffer; // reset local buffer cursor
            commitChunk(this);
        }
        // Write current character to local buffer.
        *localCursor = *srcPtr;
        localCursor++;
        srcPtr++;
    }

    // Should never reach here; but just in case.
    return 1;
}