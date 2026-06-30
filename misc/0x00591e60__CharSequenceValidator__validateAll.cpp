// FUNC_NAME: CharSequenceValidator::validateAll
bool __thiscall CharSequenceValidator::validateAll(CharSequenceValidator* this, void* context) {
    char currentChar;
    int index = 0;

    // +0x01: count of characters in the sequence (signed char)
    char count = *(char*)(this + 1);
    if (count > 0) {
        do {
            // +0x08: array of pointers to character data (each 4 bytes)
            char** charPtrArray = *(char***)(this + 8);
            currentChar = **(charPtrArray + index);

            // Characters > '\t' (0x09) are not allowed – only control/whitespace chars are valid.
            // For allowed chars <= '\t' a handler function from a global table is invoked.
            if (('\t' < currentChar) ||
                ((currentChar = ((code*)(&PTR_FUN_0103af90))[(int)currentChar])(context),
                 currentChar == '\0')) {
                return false;
            }
            index++;
        } while (index < count);
    }
    return true;
}