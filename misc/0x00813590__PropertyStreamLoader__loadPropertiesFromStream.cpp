// FUNC_NAME: PropertyStreamLoader::loadPropertiesFromStream

// Function at 0x00813590
// Reads a binary stream of tokens (types 0,1,2) to populate three properties at offsets +0x50, +0x58, +0x60.
// The stream is initialized with a magic value 0x51f146f4.

#include <cstdint>

// Forward declarations of stream utility functions (addresses from Ghidra)
void streamInit(void* stream);                                          // 0x0046c710
void streamSetFilter(void* stream, uint32_t filter);                    // 0x0043aff0
bool streamIsEnd(const void* stream);                                   // 0x0043b120
int streamReadTokenType(void* stream);                                  // 0x0043ab70
uint32_t streamReadTokenValue(void* stream);                            // 0x0043ab90
int streamAdvanceToken(void* stream);                                   // 0x0043b210  (returns pointer to token data)
void streamNextToken(void* stream);                                     // 0x0043b1a0

// Setters for the three properties (addresses 0x004089b0 and 0x00408980)
void setPropertyA(int* ptr, uint32_t value);  // sets at (this + 0x50)
void setPropertyB(int* ptr, uint32_t value);  // sets at (this + 0x58)

class PropertyStreamLoader {
public:
    // Offsets for properties (relative to 'this')
    uint32_t m_propertyA;      // +0x50
    uint32_t m_propertyB;      // +0x58
    uint32_t m_propertyC;      // +0x60

    void loadPropertiesFromStream(void* stream) {
        streamInit(stream);
        streamSetFilter(stream, 0x51f146f4);

        while (!streamIsEnd(stream)) {
            streamAdvanceToken(stream);  // read next token
            int tokenType = streamReadTokenType(stream);

            if (tokenType == 0) {
                streamAdvanceToken(stream);
                uint32_t value = streamReadTokenValue(stream);
                setPropertyA(&m_propertyA, value);        // sets this+0x50
            }
            else if (tokenType == 1) {
                streamAdvanceToken(stream);
                uint32_t value = streamReadTokenValue(stream);
                setPropertyB(&m_propertyB, value);        // sets this+0x58
            }
            else if (tokenType == 2) {
                int tokenDataPtr = streamAdvanceToken(stream);  // returns pointer to token data
                m_propertyC = *(uint32_t*)(tokenDataPtr + 8);    // reads from offset 8 of token
            }
            streamNextToken(stream);
        }
    }
};