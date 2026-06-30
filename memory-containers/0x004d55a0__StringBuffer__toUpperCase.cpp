// FUNC_NAME: StringBuffer::toUpperCase

// Represents a simple string buffer with pointer and length
struct StringBuffer {
    char* buffer; // +0x00
    int length;   // +0x04 (number of characters in buffer)
};

// Converts all lowercase ASCII letters (a-z) to uppercase in-place
void __thiscall StringBuffer::toUpperCase(StringBuffer* this) {
    unsigned int i = 0;

    if (this->length != 0) {
        do {
            char* pChar = this->buffer + i;
            char c = *pChar;

            // Check if character is lowercase (between 'a' and 'z')
            if ((unsigned int)(c - 0x61) < 0x1a) {
                c = c - 0x20; // Convert to uppercase by subtracting 0x20
            }

            *pChar = c;
            i++;
        } while (i < (unsigned int)this->length);
    }
}