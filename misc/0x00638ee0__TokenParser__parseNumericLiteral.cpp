// FUNC_NAME: TokenParser::parseNumericLiteral
// Address: 0x00638ee0
// Role: Parses a numeric literal (integer or floating-point) from an input stream,
// writes the token string into an output buffer, and validates the result.
// Uses an internal context structure (this) stored in EDI.
// Fields:
//   this[0]  : uint32 currentChar (currently read character from input stream)
//   this[1]  : unknown (used in error reporting and validation)
//   this[9]  : InputStream* (points to a structure with count, ptr, and read function)
//   this[10] : OutputBuffer* (points to a structure with buffer ptr and capacity)
// Helper functions:
//   FUN_006279a0 : resizeBuffer(uint oldCapacity, uint newCapacity)
//   FUN_006384e0 : fetchNextChar() – reads next character from InputStream
//   FUN_00638b20 : reportError(const char* msg, const char* token, uint32 context)
//   FUN_00636850 : validateNumberString(const char* str) – returns 0 if malformed

void __thiscall TokenParser::parseNumericLiteral(bool hasLeadingDecimal, uint32 /* unknownParam */)
{
    OutputBuffer* outBuf = *(OutputBuffer**)this[10];
    // Ensure output buffer has at least 0x20 capacity
    if (outBuf->capacity < 5 && outBuf->capacity < 0x20) {
        outBuf->buffer = resizeBuffer(outBuf->capacity, 0x20);
        outBuf->capacity = 0x20;
    }

    // If there was a leading decimal point (e.g., ".5"), write it now
    if (hasLeadingDecimal) {
        *(char*)outBuf->buffer = '.';
    }

    uint32 outPos = hasLeadingDecimal ? 1 : 0;

    // Parse integer part (digits before decimal point)
    if (isdigit(this[0])) {
        uint32 capacityNeeded = outPos + 0x20;
        do {
            // Expand buffer if needed
            if (outBuf->capacity < capacityNeeded - 0x1b && outBuf->capacity < capacityNeeded) {
                uint32 newCapacity = capacityNeeded;
                if (capacityNeeded < 0x20) newCapacity = 0x20;
                outBuf->buffer = resizeBuffer(outBuf->capacity, newCapacity);
                outBuf->capacity = newCapacity;
            }
            *(char*)(outBuf->buffer + outPos) = (char)this[0];
            this[9]->count--;
            if (this[9]->count == 0) {
                uint32 newChar = this[9]->readFunction(0, this[9]->unknown2, &local_temp);
                if (newChar == 0xFFFFFFFF || local_temp == 0) {
                    this[0] = 0xFFFFFFFF;
                } else {
                    this[9]->ptr = (char*)newChar;
                    this[9]->count = local_temp - 1;
                    this[0] = *(byte*)newChar;
                    this[9]->ptr = (char*)(newChar + 1);
                }
            } else {
                byte* streamPtr = *(byte**)(this[9] + 4);
                this[0] = *streamPtr;
                *(byte**)(this[9] + 4) = streamPtr + 1;
            }
            outPos++;
            capacityNeeded++;
        } while (isdigit(this[0]));
    }

    uint32 finalPos = outPos;

    // Decimal point handling
    if (this[0] == '.') {
        *(char*)(outBuf->buffer + outPos) = '.';
        this[9]->count--;
        if (this[9]->count == 0) {
            this[0] = fetchNextChar();
        } else {
            byte* streamPtr = *(byte**)(this[9] + 4);
            this[0] = *streamPtr;
            *(byte**)(this[9] + 4) = streamPtr + 1;
        }
        outPos++;

        // Detect double decimal point (error)
        if (this[0] == '.') {
            *(char*)(outBuf->buffer + outPos) = '.';
            this[9]->count--;
            if (this[9]->count == 0) {
                fetchNextChar();
            } else {
                byte* streamPtr = *(byte**)(this[9] + 4);
                this[0] = *streamPtr;
                *(byte**)(this[9] + 4) = streamPtr + 1;
            }
            outPos++;
            *(char*)(outBuf->buffer + outPos) = '\0';
            reportError("ambiguous syntax (decimal point x string concatenation)",
                        outBuf->buffer, this[1]);
        }
    }

    // Parse fractional part (digits after decimal)
    if (isdigit(this[0])) {
        uint32 capacityNeeded = outPos + 0x20;
        do {
            if (outBuf->capacity < capacityNeeded - 0x1b && outBuf->capacity < capacityNeeded) {
                uint32 newCapacity = capacityNeeded;
                if (capacityNeeded < 0x20) newCapacity = 0x20;
                outBuf->buffer = resizeBuffer(outBuf->capacity, newCapacity);
                outBuf->capacity = newCapacity;
            }
            *(char*)(outBuf->buffer + outPos) = (char)this[0];
            this[9]->count--;
            if (this[9]->count == 0) {
                // read more
                uint32 newChar = this[9]->readFunction(0, this[9]->unknown2, &local_temp);
                if (newChar == 0xFFFFFFFF || local_temp == 0) {
                    this[0] = 0xFFFFFFFF;
                } else {
                    this[9]->ptr = (char*)newChar;
                    this[9]->count = local_temp - 1;
                    this[0] = *(byte*)newChar;
                    this[9]->ptr = (char*)(newChar + 1);
                }
            } else {
                byte* streamPtr = *(byte**)(this[9] + 4);
                this[0] = *streamPtr;
                *(byte**)(this[9] + 4) = streamPtr + 1;
            }
            outPos++;
            capacityNeeded++;
        } while (isdigit(this[0]));
    }

    // Exponent part (optional)
    if (this[0] == 'e' || this[0] == 'E') {
        *(char*)(outBuf->buffer + outPos) = (char)this[0];
        this[9]->count--;
        if (this[9]->count == 0) {
            this[0] = fetchNextChar();
        } else {
            byte* streamPtr = *(byte**)(this[9] + 4);
            this[0] = *streamPtr;
            *(byte**)(this[9] + 4) = streamPtr + 1;
        }
        outPos++;

        // Optional sign
        uint32 signPos = outPos;
        if (this[0] == '+' || this[0] == '-') {
            *(char*)(outBuf->buffer + outPos) = (char)this[0];
            this[9]->count--;
            if (this[9]->count == 0) {
                this[0] = fetchNextChar();
            } else {
                byte* streamPtr = *(byte**)(this[9] + 4);
                this[0] = *streamPtr;
                *(byte**)(this[9] + 4) = streamPtr + 1;
            }
            signPos = outPos + 1;
        }
        outPos = signPos;

        // Parse exponent digits
        if (isdigit(this[0])) {
            uint32 capacityNeeded = outPos + 0x20;
            do {
                if (outBuf->capacity < capacityNeeded - 0x1b && outBuf->capacity < capacityNeeded) {
                    uint32 newCapacity = capacityNeeded;
                    if (capacityNeeded < 0x20) newCapacity = 0x20;
                    outBuf->buffer = resizeBuffer(outBuf->capacity, newCapacity);
                    outBuf->capacity = newCapacity;
                }
                *(char*)(outBuf->buffer + outPos) = (char)this[0];
                this[9]->count--;
                if (this[9]->count == 0) {
                    uint32 newChar = this[9]->readFunction(0, this[9]->unknown2, &local_temp);
                    if (newChar == 0xFFFFFFFF || local_temp == 0) {
                        this[0] = 0xFFFFFFFF;
                    } else {
                        this[9]->ptr = (char*)newChar;
                        this[9]->count = local_temp - 1;
                        this[0] = *(byte*)newChar;
                        this[9]->ptr = (char*)(newChar + 1);
                    }
                } else {
                    byte* streamPtr = *(byte**)(this[9] + 4);
                    this[0] = *streamPtr;
                    *(byte**)(this[9] + 4) = streamPtr + 1;
                }
                outPos++;
                capacityNeeded++;
            } while (isdigit(this[0]));
        }
    }

    // Null-terminate the token string
    *(char*)(outBuf->buffer + outPos) = '\0';

    // Validate the number string
    if (!validateNumberString((const char*)unknownParam)) {
        reportError("malformed number", outBuf->buffer, this[1]);
    }
}