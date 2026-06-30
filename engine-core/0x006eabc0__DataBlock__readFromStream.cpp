// FUNC_NAME: DataBlock::readFromStream
// Function at 0x006eabc0, reads a property block from a stream using a simple token-based format.
// Fields at offsets: +0x50 (string), +0x58 (string), +0x60 (float), +0x68 (int, multiplied by 1000), +0x70 (int), +0x74 (int)

#include <cstdint>

class DataBlock {
public:
    void readFromStream(void* stream);

private:
    void openStream(void* stream);              // FUN_0043b540
    void setStreamKey(void* stream, uint32_t key); // FUN_0043aff0
    bool isStreamEnd(void* stream);             // FUN_0043b120
    void* readNextToken(void* stream);          // FUN_0043b210, returns pointer to token data
    uint32_t getTokenType(void* stream);        // FUN_0043ab70
    const char* getTokenString(void* stream);   // FUN_0043ab90, returns string from current token
    void setStringField(uint32_t offset, const char* str); // FUN_004089b0
    void setFloatField(uint32_t offset, const char* str);  // FUN_00408240, parses float from string

    // Fields
    char fieldName1[64];    // +0x50
    char fieldName2[64];    // +0x58
    float fieldFloat;       // +0x60
    int fieldScaledInt;     // +0x68
    int fieldInt1;          // +0x70
    int fieldInt2;          // +0x74
};

void DataBlock::readFromStream(void* stream) {
    openStream(stream);
    setStreamKey(stream, 0x7444f437); // Magic key for this format

    while (!isStreamEnd(stream)) {
        readNextToken(stream);
        uint32_t tokenType = getTokenType(stream);

        switch (tokenType) {
            case 0: {
                readNextToken(stream);
                const char* str = getTokenString(stream);
                setStringField(reinterpret_cast<uint32_t>(&fieldName1) - reinterpret_cast<uint32_t>(this), str);
                break;
            }
            case 1: {
                readNextToken(stream);
                const char* str = getTokenString(stream);
                setStringField(reinterpret_cast<uint32_t>(&fieldName2) - reinterpret_cast<uint32_t>(this), str);
                break;
            }
            case 2: {
                void* token = readNextToken(stream);
                fieldInt1 = *reinterpret_cast<int*>(static_cast<char*>(token) + 8);
                break;
            }
            case 3: {
                void* token = readNextToken(stream);
                fieldInt2 = *reinterpret_cast<int*>(static_cast<char*>(token) + 8);
                break;
            }
            case 4: {
                void* token = readNextToken(stream);
                fieldScaledInt = *reinterpret_cast<int*>(static_cast<char*>(token) + 8) * 1000;
                break;
            }
            case 5: {
                readNextToken(stream);
                const char* str = getTokenString(stream);
                setFloatField(reinterpret_cast<uint32_t>(&fieldFloat) - reinterpret_cast<uint32_t>(this), str);
                break;
            }
            default:
                break;
        }
        // Advance stream state (FUN_0043b1a0)
        // This likely finalizes the token processing.
        // The implementation is omitted as it's not shown in decompilation.
    }
}