// FUNC_NAME: StringUtils::findDotAfterLastPathSeparator
void __fastcall findDotAfterLastPathSeparator(int unusedParam, StringRef* strRef) {
    // strRef->data: pointer to string start (param_2[0])
    // strRef->length: length of string (param_2[1])
    char* currentChar = (char*)strRef->data;
    char* dotPosition = nullptr;

    if (currentChar != nullptr) {
        char* endPtr = currentChar + strRef->length;
        while (currentChar < endPtr) {
            if (dotPosition == nullptr) {
                // No dot found yet – look for the first '.'
                if (*currentChar == '.') {
                    dotPosition = currentChar;
                }
            } else {
                // A dot was previously found – if we encounter a path separator,
                // the dot is not in the final filename, so reset.
                if ((*currentChar == '/') || (*currentChar == '\\')) {
                    dotPosition = nullptr;
                }
            }
            ++currentChar;
        }
    }
    // Note: dotPosition is set to the first '.' after the last path separator,
    //       but this function returns void. The caller may rely on dotPosition
    //       being stored somewhere (e.g., via a register) or the function is
    //       incomplete in this analysis.
}