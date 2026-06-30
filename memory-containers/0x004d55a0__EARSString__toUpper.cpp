// FUNC_NAME: EARSString::toUpper
// Address: 0x004d55a0
// Role: Converts all ASCII lowercase letters in a string buffer to uppercase in-place.
// The string object is expected to have a pointer to the character data at +0x00 and a length at +0x04.

class EARSString {
public:
    char* strPtr;   // +0x00 pointer to string data
    int   length;   // +0x04 character count

    void __thiscall toUpper(void) {
        uint i = 0;
        if (this->length != 0) {
            do {
                char* pc = this->strPtr + i;
                char ch = *pc;
                // Check if character is lowercase 'a'..'z' (0x61..0x7A)
                if ((uint)(ch - 0x61) < 0x1A) {
                    ch = ch - 0x20; // Convert to uppercase
                }
                *pc = ch;
                i++;
            } while (i < (uint)this->length);
        }
    }
};