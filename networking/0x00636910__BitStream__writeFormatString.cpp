// FUNC_NAME: BitStream::writeFormatString
// Function address: 0x00636910
// Role: Writes a formatted string with variable arguments into a BitStream buffer.
// Handles format specifiers: %c, %d, %f, %s, %%.

#include <cstdarg>
#include <cstring>
#include <cmath>

class BitStream {
public:
    // +0x00 unknown
    // +0x04 unknown
    int* pWritePtr;      // +0x08
    int* pBasePtr;       // +0x0C (base of current token region?)
    int* pBufferEnd;     // +0x18
    int* pBufferStart;   // +0x1C
    int capacity;        // +0x20

    void writeStringChunk(const char* str, int length);
    void expandBuffer();
    void finalizeWrite(int numTokens, int totalDataSize);
    // ... other members
};

void BitStream::expandBuffer() {
    // 00635b50 - placeholder
}

void BitStream::finalizeWrite(int arg1, int arg2) {
    // 006343b0 - placeholder
}

// Writes a string token with type=4 and data being the string chunk.
// This function is actually an external helper: FUN_00638920
void BitStream::writeStringChunk(const char* str, int len) {
    // Implementation: sets two slots: type=4, data pointer (or inline string?)
    // This is called via FUN_00638920.
}

// Main formatted write function
int __thiscall BitStream::writeFormatString(const char* format, ...) {
    va_list args;
    va_start(args, format);

    int* writePtr = pWritePtr;
    *writePtr = 4; // type string chunk
    writeStringChunk(format, 0); // write empty string chunk? Actually, it uses DAT_00e2f044 as a string constant
    // The actual code does: *puVar3 = 4; uVar4 = FUN_00638920(param_1,&DAT_00e2f044,0); puVar3[1] = uVar4;
    // So it writes a token with type=4 and data = some constant string? That seems odd. Possibly it's a header.
    // We'll skip the exact detail and focus on the format loop.

    const char* fmt = format;
    int paramStackOffset = 1; // tracks number of tokens written? Actually, local_4 starts at 1 and increments by 2 each loop.
    int totalTokens = 1; // local_4

    // Find first '%'
    const char* pct = strchr(fmt, '%');
    if (pct != nullptr) {
        double* doubleArgPtr = (double*)(&args - 8); // tricky arithmetic: args is a va_list (char* stack pointer)
        // The decompiler shows param_2 = param_2 + -4; and then accesses param_2+4. This is to handle the way args are on stack.
        // We'll simulate by adjusting a variable pointer.
        char* argPtr = (char*)&args; // this approximates the stack pointer

        do {
            // Write the literal string before the '%'
            int literalLen = pct - fmt;
            writePtr = pWritePtr;
            *writePtr = 4; // type string
            writeStringChunk(fmt, literalLen);
            pWritePtr += 2; // advance by 8 bytes? Actually, +8 total for two ints.

            // Ensure space for next token (expand buffer if needed)
            if (pBufferEnd - pWritePtr < 2) {
                // This expansion logic is complex; simplified.
                expandBuffer();
            }

            writePtr = pWritePtr;
            char spec = pct[1];
            switch (spec) {
                case '%': {
                    *writePtr = 4;
                    writeStringChunk("%", 1);
                    pWritePtr += 2;
                    break;
                }
                case 'c': {
                    // Read a char from the argument list
                    char ch = *(char*)(argPtr + 4); // Actually, the code reads from param_2+4, which corresponds to next arg
                    argPtr += 4;
                    char buf[2] = { ch, '\0' };
                    *writePtr = 4;
                    writeStringChunk(buf, 1);
                    pWritePtr += 2;
                    break;
                }
                case 'd': {
                    // Read an int and store as float (type 3)
                    int val = *(int*)(argPtr + 4);
                    argPtr += 4;
                    *writePtr = 3; // type float
                    *(float*)(writePtr + 1) = (float)val;
                    pWritePtr += 2;
                    break;
                }
                case 'f': {
                    // Read a double and store as float
                    double dval = *(double*)(argPtr + 4);
                    argPtr += 8;
                    *writePtr = 3;
                    *(float*)(writePtr + 1) = (float)dval;
                    pWritePtr += 2;
                    break;
                }
                case 's': {
                    // String argument - just calls FUN_006368c0 (probably writes the string verbatim)
                    // This case is incomplete in the decompiled; it calls FUN_006368c0() and then falls through to default.
                    // Skipping detailed handling.
                    // In real code, it would write the string.
                    break;
                }
                default:
                    // Unknown specifier; fall through to next iteration? Actually, the code goes to switchD_00636a17_caseD_26 which just loops.
                    break;
            }

            // After each token, check buffer space and advance pWritePtr
            if (pBufferEnd - pWritePtr < 0) { // overflow condition
                // call FUN_00635c70() - possibly error handler
            }
            pWritePtr += 2;

            // Update fmt to after the specifier
            fmt = pct + 2;
            pct = strchr(fmt, '%');
            totalTokens += 2; // increments per format spec? Actually local_4 += 2 each loop.
        } while (pct != nullptr);
        // At this point, fmt points to the remainder after the last '%'
        totalTokens = (int)(pct - fmt) + 1; // Not exactly, but we'll approximate
    }

    // Write the remaining literal string after the last '%'
    writePtr = pWritePtr;
    *writePtr = 4;
    int remainingLen = strlen(fmt);
    writeStringChunk(fmt, remainingLen);
    pWritePtr += 2;

    // Finalize: call FUN_006343b0(param_1, totalTokens + 1, (pWritePtr - pBasePtr) / 8 - 1)
    // This adjusts the write pointer back?
    finalizeWrite(totalTokens + 1, (pWritePtr - pBasePtr) / 8 - 1);
    pWritePtr += totalTokens * -8; // rewind by totalTokens * 8 bytes? (local_4 * -8)

    // Return value: *(*(pWritePtr - 4) + 0x10) ??? Likely returns a status or size.
    return *(int*)(*((int*)pWritePtr - 1) + 0x10);
}