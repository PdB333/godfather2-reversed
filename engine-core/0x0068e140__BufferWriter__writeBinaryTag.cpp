// FUNC_NAME: BufferWriter::writeBinaryTag

// Reconstructed C++ from Ghidra decompile of 0x0068e140
// Purpose: Writes a "[b=...]" tagged binary data segment into a growing buffer.
// param_1 (this): BufferWriter with fields: char* buffer (+0x00), int offset (+0x04), int capacity (+0x08)
// param_2: Source string descriptor: int startOffset (+0x00), int unused? (+0x04), char* dataBase (+0x08), int length (+0x0C)

#include <cstring> // for _strncpy_s

struct BufferWriter {
    char* buffer;   // +0x00
    int offset;     // +0x04
    int capacity;   // +0x08
};

struct StringRef {
    int startOffset;  // +0x00
    int reserved;     // +0x04
    char* dataBase;   // +0x08
    int length;       // +0x0C
};

void __thiscall BufferWriter::writeBinaryTag(BufferWriter* this, const StringRef* src) {
    // Write the opening tag "[b="
    _strncpy_s(this->buffer + this->offset, this->capacity - this->offset, "[b=", 3);
    this->offset += 3;

    // Write the binary data from source string
    size_t dataLen = src->length;
    _strncpy_s(this->buffer + this->offset, this->capacity - this->offset, src->dataBase + src->startOffset, dataLen);
    this->offset += dataLen;

    // Write the closing bracket
    _strncpy_s(this->buffer + this->offset, this->capacity - this->offset, "]", 1);
    this->offset += 1;
}