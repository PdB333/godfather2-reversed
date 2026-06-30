// Xbox PDB: EA::String::Utf8::ToUcs4
// FUNC_NAME: StreamReader::readUtf8Char
// Address: 0x005b8d10
// Role: Reads a single UTF-8 encoded character from a byte stream and advances the internal pointer.
// The class holds a byte pointer (m_pBufferPos) that is updated after reading.
// Returns the decoded Unicode code point (uint). On error, calls handleUtf8Error and returns 0.

#include <cstdint>

// Forward declaration of error handler
void handleUtf8Error();

class StreamReader {
public:
    // +0x00: pointer to current position in byte stream
    uint8_t* m_pBufferPos;

    // Decodes the next UTF-8 character from the stream.
    // Advances m_pBufferPos past the consumed bytes.
    // Returns the Unicode code point (0-0x10FFFF) or 0 on invalid sequence.
    uint32_t readUtf8Char() {
        uint8_t* p = m_pBufferPos;
        uint8_t firstByte = *p;

        // 1-byte sequence: 0xxxxxxx
        if (firstByte < 0x80) {
            m_pBufferPos = p + 1;
            return firstByte;
        }

        // 2-byte sequence: 110xxxxx 10xxxxxx
        if ((firstByte & 0xE0) == 0xC0) {
            // Check if second byte exists (non-null – note: a null byte would be a valid terminator, but we treat it as error)
            if (p[1] == 0) {
                // Incomplete sequence, advance by 1 and return 0
                m_pBufferPos = p + 1;
                return 0;
            }
            // Validate continuation byte
            if ((p[1] & 0xC0) != 0x80) {
                handleUtf8Error();
            }
            m_pBufferPos = p + 2;
            return (p[1] & 0x3F) | ((firstByte & 0x1F) << 6);
        }

        // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
        if ((firstByte & 0xF0) == 0xE0) {
            // Check if second byte exists
            if (p[1] == 0) {
                m_pBufferPos = p + 1;
                return 0;
            }
            // Check if third byte exists
            if (p[2] == 0) {
                m_pBufferPos = p + 2;
                return 0;
            }
            // Validate continuation bytes
            if ((p[1] & 0xC0) != 0x80) {
                handleUtf8Error();
            }
            if ((p[2] & 0xC0) != 0x80) {
                handleUtf8Error();
            }
            m_pBufferPos = p + 3;
            uint32_t code = ((firstByte & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
            return code;
        }

        // 4-byte sequences (0xF0-0xF7) and other invalid lead bytes
        // Not implemented – treat as error
        handleUtf8Error();
        return 0;
    }

private:
    // Declared to avoid linking issues; actual error handler defined elsewhere (0x0059bf00)
    friend void handleUtf8Error();
};