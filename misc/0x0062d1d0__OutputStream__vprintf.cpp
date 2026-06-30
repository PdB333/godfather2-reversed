// FUNC_NAME: OutputStream::vprintf
// Address: 0x0062d1d0
// Role: Custom printf-like function for EA EARS engine output stream.
// Writes formatted output to an internal buffer, flushing packets when full.

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cctype>

// Forward declarations for helper functions (renamed from Ghidra)
char* parseFormatSpecifier(OutputStream* this, const char* fmt, char* outSpec);
void pushVariadicArgument(); // retrieves next variadic argument
void writeBuffer(OutputStream* this, const uint8_t* data);
void flushLocalBuffer(OutputStream* this);
void resetLocalBuffer();
void handleQuotedString(OutputStream* this);
void handleStringSpec(OutputStream* this);
void formatError();
void finalizeWrite(OutputStream* this);
uint8_t* getBufferStart(OutputStream* this);
int32_t getWriteOffset(OutputStream* this);
void beginPacket(OutputStream* this);
void endPacket(OutputStream* this);
void pushPacketState();
void popPacketState();
void setPacketArgument(int32_t);
void appendStringToLocalBuffer(const char* str);

// Structure offset comments (based on usage):
// +0x08: pointer to output packet buffer (uint32_t*)
// +0x10: pointer to some control structure with:
//   +0x20: current write position (size)
//   +0x24: buffer capacity (size)
// The function uses a local 512-byte buffer to accumulate output.

int32_t OutputStream::vprintf(const char* format, ...) {
    uint8_t* writePtr = getBufferStart(this);
    if (writePtr == nullptr) {
        formatError(); // +0x10? fatal
    }

    int32_t offset = getWriteOffset(this);
    uint8_t* endPtr = writePtr + offset;

    uint8_t localBuffer[512];
    uint8_t* localBufferPtr = localBuffer;
    int32_t packetCount = 0; // number of packets flushed

    while (true) {
        // If we've reached the end of the source buffer, flush and finalize
        if (writePtr >= endPtr) {
            flushLocalBuffer(this);
            finalizeWrite(this);
            return 1;
        }

        if (*writePtr == '%') {
            // Process format specifier
            const uint8_t* nextChar = writePtr + 1;
            if (*nextChar == '%') {
                // Handle "%%" (escaped percent)
                if (localBufferPtr >= &localBuffer[512] && localBufferPtr != localBuffer) {
                    // Flush local buffer
                    if (/* buffer full */ true) {
                        pushPacketState();
                        beginPacket(this);
                        pushPacketState(); // nested?
                        setPacketArgument(0);
                        beginPacket(this);
                        // Write packet with type 4
                        uint32_t* packetHeader = *(uint32_t**)((uint8_t*)this + 8);
                        *packetHeader = 4;
                        uint32_t dataSize = writeBuffer(this, localBuffer);
                        packetHeader[1] = dataSize;
                        *(int32_t*)((uint8_t*)this + 8) += 8; // advance packet pointer
                        packetCount++;
                        localBufferPtr = localBuffer;
                        resetLocalBuffer();
                    }
                }
                *localBufferPtr++ = '%';
                writePtr += 2;
                continue;
            }

            // Check if next char is digit and format specifier is valid? (obfuscated error handling omitted)
            // Actually the code has a complex default case that we simplify.

            char formatSpec[2];
            const char* afterSpec = parseFormatSpecifier(this, (const char*)nextChar, formatSpec);

            // afterSpec points to the format character itself (e.g., 'd', 's')
            // pbVar3 gets updated to skip the specifier
            uint8_t* newWritePtr = (uint8_t*)(afterSpec + 1);
            char fmtChar = *afterSpec;

            // Handle each format specifier
            switch (fmtChar) {
                case 'E':
                case 'G':
                case 'e':
                case 'f':
                case 'g': {
                    // Floating point
                    pushVariadicArgument(); // pop double from XMM0
                    double value = /* next double argument */ 0.0;
                    char temp[572];
                    sprintf(temp, formatSpec, value);
                    // Append temp to local buffer
                    for (const char* s = temp; *s; s++) {
                        // Flush if buffer full (simplified)
                        if (localBufferPtr >= &localBuffer[512]) {
                            // flush logic...
                        }
                        *localBufferPtr++ = *s;
                    }
                    break;
                }
                case 'X':
                case 'o':
                case 'u':
                case 'x':
                    // Unsigned integer
                    pushVariadicArgument();
                    // sprintf to local buffer, then append
                    break;
                case 'c':
                case 'd':
                case 'i':
                    // Signed integer
                    pushVariadicArgument();
                    break;
                case 'q':
                    // Custom 'q' specifier (quoted string?)
                    handleQuotedString(this);
                    newWritePtr = (uint8_t*)afterSpec; // restore? Actually afterSpec+1 already done
                    // The goto loop uses newWritePtr to update writePtr
                    writePtr = newWritePtr;
                    continue; // re-enter loop with same writePtr? Actually the original goes to joined_r0x0062d231
                    // We'll handle this by setting writePtr and continuing
                    break;
                case 's':
                    // String
                    pushVariadicArgument();
                    if (/* some length check */ 0 < 100) {
                        // Flush if needed
                        handleStringSpec(this);
                        // Finalize?
                        break;
                    }
                    // else: handle longer strings
                    break;
                default:
                    // Obfuscated error, simplified
                    formatError();
                    return 1;
            }
            // For most specifiers, we sprintf and append to local buffer via appendStringToLocalBuffer
            // Then update writePtr
            writePtr = newWritePtr;
        } else {
            // Normal character: copy to local buffer
            if (localBufferPtr >= &localBuffer[512] && localBufferPtr != localBuffer) {
                // Flush logic (exact same as above for %%)
                // ... (simplified: call flush, reset)
                flushLocalBuffer(this);
                localBufferPtr = localBuffer;
                resetLocalBuffer();
            }
            *localBufferPtr++ = *writePtr;
            writePtr++;
        }
    }
    // Unreachable
    return 1;
}