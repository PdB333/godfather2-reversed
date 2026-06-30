// FUNC_NAME: ConfigReader::buildMergedString
// Function address: 0x0068fc60
// Role: Builds a string by concatenating internal preloaded lines and user-input lines from a stream.
// Uses a global flag (DAT_011299d0) to check if reader is available.
// Parameters: this (ConfigReader*), outBuffer (char*), outBufferSize (size_t)
// Returns: true if any data was written, false otherwise.

#include <cstring>
#include <rsize_t> // custom type for safe string operations (from EARS engine)

// Forward declarations of internal engine functions (from same module)
void beginReading(ConfigReader* this);                    // 0x0068e1b0
bool hasMoreLines(ConfigReader* this);                    // 0x0068e210
bool readLine(/* unknown */, size_t, char**);             // 0x0068f910
void skipLine(/* unknown */);                             // 0x0068e140

extern bool g_bReaderAvailable; // DAT_011299d0

class ConfigReader {
public:
    // Offsets are based on debug analysis (assumed from usage in this function)
    char* m_pInternalBuffer;   // +0x810? – points to current internal line source
    size_t m_internalLineLen;  // +0x808? – length of current internal line
    // Additional members are likely present but not used directly here

    bool buildMergedString(char* outBuffer, size_t outBufferSize);
};

bool ConfigReader::buildMergedString(char* outBuffer, size_t outBufferSize) {
    if (!g_bReaderAvailable) {
        return false;
    }

    beginReading(this);

    int totalWritten = 0;
    outBuffer[0] = '\0';
    memset(outBuffer, 0, outBufferSize);

    bool dataWritten = false;

    if (hasMoreLines(this)) {
        dataWritten = true;
        do {
            // Copy current internal line into output buffer
            size_t internalLen = m_internalLineLen; // actually local_804, but likely member
            strncpy_s(outBuffer + totalWritten, outBufferSize - totalWritten, 
                      static_cast<char*>(m_pInternalBuffer) + internalOffset, // (local_810+local_808) interpreted as m_pInternalBuffer + m_internalOffset
                      internalLen);
            totalWritten += internalLen;

            // Prepare to read an external line
            char lineBuffer[2048]; // local_800
            char* linePtr = lineBuffer; // local_834
            size_t lineLength = 0; // local_830
            size_t maxLineSize = 0x800; // local_82c
            lineBuffer[0] = '\0';

            if (readLine(/* internal buffer? */, 0, &linePtr)) {
                // Append the external line
                lineLength = /* returned length */; // local_830 is set by readLine? We use it.
                strncpy_s(outBuffer + totalWritten, outBufferSize - totalWritten, 
                          linePtr, lineLength);
                totalWritten += lineLength;
            } else {
                // Skip or clean up after failed read
                skipLine(/* internal buffer? */);
            }

        } while (hasMoreLines(this));

        // After loop, copy the final internal line again (seems odd, but preserved from original)
        size_t finalInternalLen = m_internalLineLen;
        strncpy_s(outBuffer + totalWritten, outBufferSize - totalWritten, 
                  static_cast<char*>(m_pInternalBuffer) + internalOffset, 
                  finalInternalLen);
    }

    return dataWritten;
}