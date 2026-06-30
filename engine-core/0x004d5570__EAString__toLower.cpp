// FUNC_NAME: EAString::toLower
void __fastcall EAString::toLower(EAString* this) {
    uint index = 0;
    // this->buffer points to character array (+0x00), this->length is byte count (+0x04)
    if (this->length != 0) {
        do {
            char* currentChar = this->buffer + index;
            char ch = *currentChar;
            // Convert uppercase ASCII letters (0x41-0x5A) to lowercase by adding 0x20
            if ((ch - 0x41U) < 0x1A) {
                ch += 0x20;
            }
            *currentChar = ch;
            index++;
        } while (index < this->length);
    }
}