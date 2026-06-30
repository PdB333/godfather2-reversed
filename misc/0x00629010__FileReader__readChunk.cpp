// FUNC_NAME: FileReader::readChunk
// Address: 0x00629010
// Role: Reads up to 0x200 bytes from the file into the internal buffer.
// Returns pointer to buffer on success, nullptr on EOF or read failure.
// The number of bytes actually read is stored in outBytesRead.

#include <cstdio>

class FileReader {
public:
    FILE* file;       // +0x00
    char buffer[0x200]; // +0x04

    // __thiscall
    char* readChunk(int* outBytesRead) {
        if (feof(this->file)) {
            return nullptr;
        }

        int bytesRead = fread(this->buffer, 1, 0x200, this->file);
        *outBytesRead = bytesRead;

        // Return buffer address if any bytes were read, else nullptr
        return (bytesRead != 0) ? this->buffer : nullptr;
    }
};