// FUNC_NAME: BufferedFileReader::readChunk
// Address: 0x00629010
// Role: Reads up to 0x200 bytes from the associated file into the internal buffer.
// Returns a pointer to the buffer on success, or NULL on EOF/error.
// Output parameter *outBytesRead receives the number of bytes actually read.

char* __thiscall BufferedFileReader::readChunk(int* outBytesRead)
{
    // Check if we are at end of file.
    if (feof(this->file))
    {
        *outBytesRead = 0;
        return 0;
    }

    // Read up to 0x200 bytes into internal buffer (offset +0x04 from this).
    int bytesRead = fread(this->buffer, 1, 0x200, this->file);
    *outBytesRead = bytesRead;
    return (bytesRead != 0) ? this->buffer : 0;
}

// Expected structure layout (x86, 4-byte alignment):
// +0x00: FILE* file
// +0x04: char buffer[0x200]   // internal read buffer
// Total size: 0x204 bytes