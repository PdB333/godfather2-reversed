//FUNC_NAME: Tokenizer::readStringLiteral

#include <cstdint>

// Forward declarations
struct Stream;
struct OutputBuffer;

// Helper functions (assumed to exist)
void* reallocateBuffer(uint32_t oldSize, uint32_t newSize);
void reportError(const char* message, const char* text, int lineNumber);
void incrementLineNumber();
uint32_t createToken(void* context, const char* text, int length);

struct Tokenizer {
    uint32_t currentChar;          // +0x00
    int lineNumber;                // +0x04 (used in error reporting)
    uint8_t pad[8];                // +0x08 to +0x1F? (unknown)
    void* tokenContext;            // +0x20 (offset 8 in uint32_t units)
    Stream* stream;                // +0x24 (offset 9)
    OutputBuffer* outputBuffer;    // +0x28 (offset 10)
};

struct Stream {
    int remaining;                 // +0x00
    uint8_t* currentPtr;           // +0x04
    uint8_t* (*readFunc)(int, void*, int*); // +0x08 (callback)
    void* userData;                // +0x0C (passed as second arg to readFunc)
};

struct OutputBuffer {
    char* buffer;                  // +0x00
    uint32_t capacity;             // +0x04
};

// __thiscall
void Tokenizer::readStringLiteral(uint32_t delimiter, uint32_t* outToken) {
    // Ensure output buffer has at least 32 bytes capacity
    if (outputBuffer->capacity < 5 || outputBuffer->capacity < 0x20) {
        uint32_t newSize = (outputBuffer->capacity < 0x20) ? 0x20 : outputBuffer->capacity;
        outputBuffer->buffer = (char*)reallocateBuffer(outputBuffer->capacity, newSize);
        outputBuffer->capacity = newSize;
    }

    // Store first character (delimiter) into output buffer
    outputBuffer->buffer[0] = (char)currentChar;

    // Read next character from stream
    int remaining = stream->remaining;
    stream->remaining = remaining - 1;
    uint8_t* nextCharPtr;
    if (remaining == 0) {
        // Need to refill buffer
        int bytesRead;
        uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
        if (newData == nullptr || bytesRead == 0) {
            currentChar = 0xFFFFFFFF; // EOF
        } else {
            stream->currentPtr = newData;
            stream->remaining = bytesRead - 1;
            currentChar = *newData;
            stream->currentPtr = newData + 1;
        }
    } else {
        nextCharPtr = stream->currentPtr;
        currentChar = *nextCharPtr;
        stream->currentPtr = nextCharPtr + 1;
    }

    // If currentChar is delimiter, we have an empty string
    if (currentChar == delimiter) {
        outputBuffer->buffer[0] = (char)currentChar;
        // Read next char after delimiter
        remaining = stream->remaining;
        stream->remaining = remaining - 1;
        if (remaining == 0) {
            int bytesRead;
            uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
            if (newData == nullptr || bytesRead == 0) {
                currentChar = 0xFFFFFFFF;
            } else {
                stream->currentPtr = newData;
                stream->remaining = bytesRead - 1;
                currentChar = *newData;
                stream->currentPtr = newData + 1;
            }
        } else {
            nextCharPtr = stream->currentPtr;
            currentChar = *nextCharPtr;
            stream->currentPtr = nextCharPtr + 1;
        }
        // Null-terminate and create token
        outputBuffer->buffer[1] = '\0';
        *outToken = createToken(tokenContext, outputBuffer->buffer + 1, 0);
        return;
    }

    // Main loop: read characters until delimiter
    int writePos = 1; // position in output buffer (after opening delimiter)
    uint32_t local_18 = 0x21; // capacity tracking? (unused in logic)
    uint32_t local_1c = 6;    // capacity tracking? (unused in logic)
    int iVar11 = 1; // writePos copy

    while (currentChar != delimiter) {
        // Ensure output buffer has space (grow if needed)
        if (outputBuffer->capacity < local_1c && outputBuffer->capacity < local_18) {
            uint32_t newCap = (local_18 < 0x20) ? 0x20 : local_18;
            outputBuffer->buffer = (char*)reallocateBuffer(outputBuffer->capacity, newCap);
            outputBuffer->capacity = newCap;
        }

        uint32_t ch = currentChar;

        if (ch == 0xFFFFFFFF) { // EOF
            outputBuffer->buffer[writePos] = '\0';
            reportError("unfinished string", "<eof>", lineNumber);
            goto finish;
        }

        if (ch == '\n') { // newline inside string (error)
            outputBuffer->buffer[writePos] = '\0';
            reportError("unfinished string", outputBuffer->buffer, lineNumber);
            goto finish;
        }

        if (ch != '\\') { // normal character
            outputBuffer->buffer[writePos] = (char)ch;
            writePos++;
            // Read next char
            remaining = stream->remaining;
            stream->remaining = remaining - 1;
            if (remaining == 0) {
                int bytesRead;
                uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
                if (newData == nullptr || bytesRead == 0) {
                    currentChar = 0xFFFFFFFF;
                } else {
                    stream->currentPtr = newData;
                    stream->remaining = bytesRead - 1;
                    currentChar = *newData;
                    stream->currentPtr = newData + 1;
                }
            } else {
                nextCharPtr = stream->currentPtr;
                currentChar = *nextCharPtr;
                stream->currentPtr = nextCharPtr + 1;
            }
            local_1c++;
            local_18++;
            continue;
        }

        // Escape sequence: read next character
        remaining = stream->remaining;
        stream->remaining = remaining - 1;
        uint32_t escapeChar;
        if (remaining == 0) {
            int bytesRead;
            uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
            if (newData == nullptr || bytesRead == 0) {
                escapeChar = 0xFFFFFFFF;
            } else {
                stream->currentPtr = newData;
                stream->remaining = bytesRead - 1;
                escapeChar = *newData;
                stream->currentPtr = newData + 1;
            }
        } else {
            nextCharPtr = stream->currentPtr;
            escapeChar = *nextCharPtr;
            stream->currentPtr = nextCharPtr + 1;
        }
        currentChar = escapeChar;

        switch (escapeChar) {
            case '\n': // newline escape (line continuation)
                outputBuffer->buffer[writePos] = '\n';
                writePos++;
                incrementLineNumber();
                local_1c++;
                local_18++;
                break;

            case 'a': // alert
                outputBuffer->buffer[writePos] = '\a';
                writePos++;
                break;

            case 'b': // backspace
                outputBuffer->buffer[writePos] = '\b';
                writePos++;
                break;

            case 'f': // form feed
                outputBuffer->buffer[writePos] = '\f';
                writePos++;
                break;

            case 'n': // newline
                outputBuffer->buffer[writePos] = '\n';
                writePos++;
                break;

            case 'r': // carriage return
                outputBuffer->buffer[writePos] = '\r';
                writePos++;
                break;

            case 't': // tab
                outputBuffer->buffer[writePos] = '\t';
                writePos++;
                break;

            case 'v': // vertical tab
                outputBuffer->buffer[writePos] = '\v';
                writePos++;
                break;

            case 0xFFFFFFFF: // EOF after backslash
                // fall through to default? Actually the switch has case 0xFFFFFFFF that goes to default
                // But the code jumps to switchD_00639914_caseD_ffffffff which is the end of switch
                // So we treat it as no character written, just continue
                break;

            default: // octal escape or other
                if (isdigit(escapeChar)) {
                    // Parse up to 3 octal digits
                    int octalValue = 0;
                    int digitCount = 0;
                    do {
                        octalValue = octalValue * 10 + (escapeChar - '0');
                        digitCount++;
                        // Read next char
                        remaining = stream->remaining;
                        stream->remaining = remaining - 1;
                        if (remaining == 0) {
                            int bytesRead;
                            uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
                            if (newData == nullptr || bytesRead == 0) {
                                escapeChar = 0xFFFFFFFF;
                            } else {
                                stream->currentPtr = newData;
                                stream->remaining = bytesRead - 1;
                                escapeChar = *newData;
                                stream->currentPtr = newData + 1;
                            }
                        } else {
                            nextCharPtr = stream->currentPtr;
                            escapeChar = *nextCharPtr;
                            stream->currentPtr = nextCharPtr + 1;
                        }
                        currentChar = escapeChar;
                    } while (digitCount < 3 && isdigit(escapeChar));

                    if (octalValue > 0xFF) {
                        outputBuffer->buffer[writePos] = '\0';
                        reportError("escape sequence too large", outputBuffer->buffer, lineNumber);
                        // Then treat as newline error? The code goes to LAB_00639b57 which sets null and reports
                        // Actually after error, it jumps to LAB_00639b57 which sets null and reports again? Let's follow original:
                        // After "escape sequence too large", it goes to LAB_00639b57 which sets null and reports "unfinished string"
                        // So we simulate that:
                        outputBuffer->buffer[writePos] = '\0';
                        reportError("unfinished string", outputBuffer->buffer, lineNumber);
                        goto finish;
                    }
                    outputBuffer->buffer[writePos] = (char)octalValue;
                    writePos++;
                    local_1c++;
                    local_18++;
                } else {
                    // Not a digit, treat as literal character (e.g., \\)
                    outputBuffer->buffer[writePos] = (char)escapeChar;
                    writePos++;
                    // Read next char
                    remaining = stream->remaining;
                    stream->remaining = remaining - 1;
                    if (remaining == 0) {
                        int bytesRead;
                        uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
                        if (newData == nullptr || bytesRead == 0) {
                            currentChar = 0xFFFFFFFF;
                        } else {
                            stream->currentPtr = newData;
                            stream->remaining = bytesRead - 1;
                            currentChar = *newData;
                            stream->currentPtr = newData + 1;
                        }
                    } else {
                        nextCharPtr = stream->currentPtr;
                        currentChar = *nextCharPtr;
                        stream->currentPtr = nextCharPtr + 1;
                    }
                    local_1c++;
                    local_18++;
                }
                break;
        }

        // After processing escape, read next character for next iteration (unless already read)
        // Actually the code reads next char after writing the escape result, except for newline case where it reads after incrementLineNumber
        // But we already handled reading in the default case. For the specific escape characters (a,b,f,n,r,t,v), we need to read next char.
        // The original code reads next char after the switch for those cases.
        // So we do that here:
        if (escapeChar != '\n' && escapeChar != 0xFFFFFFFF && !isdigit(escapeChar)) {
            // Read next char
            remaining = stream->remaining;
            stream->remaining = remaining - 1;
            if (remaining == 0) {
                int bytesRead;
                uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
                if (newData == nullptr || bytesRead == 0) {
                    currentChar = 0xFFFFFFFF;
                } else {
                    stream->currentPtr = newData;
                    stream->remaining = bytesRead - 1;
                    currentChar = *newData;
                    stream->currentPtr = newData + 1;
                }
            } else {
                nextCharPtr = stream->currentPtr;
                currentChar = *nextCharPtr;
                stream->currentPtr = nextCharPtr + 1;
            }
        }
    }

    // Found delimiter
    outputBuffer->buffer[writePos] = (char)currentChar; // store delimiter
    writePos++;
    // Read next char after delimiter
    remaining = stream->remaining;
    stream->remaining = remaining - 1;
    if (remaining == 0) {
        int bytesRead;
        uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
        if (newData == nullptr || bytesRead == 0) {
            currentChar = 0xFFFFFFFF;
        } else {
            stream->currentPtr = newData;
            stream->remaining = bytesRead - 1;
            currentChar = *newData;
            stream->currentPtr = newData + 1;
        }
    } else {
        nextCharPtr = stream->currentPtr;
        currentChar = *nextCharPtr;
        stream->currentPtr = nextCharPtr + 1;
    }
    outputBuffer->buffer[writePos] = '\0'; // null-terminate

    // Create token: the string content is from buffer+1 to writePos-2 (excluding delimiters)
    int stringLength = writePos - 2;
    *outToken = createToken(tokenContext, outputBuffer->buffer + 1, stringLength);
    return;

finish:
    // Read next char after error
    remaining = stream->remaining;
    stream->remaining = remaining - 1;
    if (remaining == 0) {
        int bytesRead;
        uint8_t* newData = stream->readFunc(0, stream->userData, &bytesRead);
        if (newData == nullptr || bytesRead == 0) {
            currentChar = 0xFFFFFFFF;
        } else {
            stream->currentPtr = newData;
            stream->remaining = bytesRead - 1;
            currentChar = *newData;
            stream->currentPtr = newData + 1;
        }
    } else {
        nextCharPtr = stream->currentPtr;
        currentChar = *nextCharPtr;
        stream->currentPtr = nextCharPtr + 1;
    }
    outputBuffer->buffer[writePos] = '\0';
    // Create token with empty string? Original code calls createToken with buffer+1 and length writePos-2? Actually after error, it still creates token.
    // But the original code after LAB_00639b96 sets null and then calls createToken. We'll replicate.
    *outToken = createToken(tokenContext, outputBuffer->buffer + 1, writePos - 2);
}