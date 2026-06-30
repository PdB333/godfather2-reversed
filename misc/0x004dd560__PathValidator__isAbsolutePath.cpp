// FUNC_NAME: PathValidator::isAbsolutePath
bool __thiscall PathValidator::isAbsolutePath(void) {
    ushort *pathChars;
    ushort firstChar, secondChar, thirdChar;
    
    // Check if string length > 2 (minimum for absolute path: "C:\" is 3, UNC "\\a\" is 4? Actually UNC requires at least 4: \\server\share so length > 2)
    if (this->length <= 2) {
        return false;
    }
    
    pathChars = this->path;  // +0x00: wchar_t* path
    firstChar = pathChars[0];
    secondChar = pathChars[1];
    thirdChar = pathChars[2];
    
    // Convert first three characters to uppercase if they are lowercase letters
    if (firstChar - 0x61 < 0x1a) {
        firstChar -= 0x20;
    }
    if (secondChar - 0x61 < 0x1a) {
        secondChar -= 0x20;
    }
    if (thirdChar - 0x61 < 0x1a) {
        thirdChar -= 0x20;
    }
    
    // Check for UNC path: "\\" followed by a letter (server name)
    if (firstChar == 0x5c) {  // backslash
        if ((secondChar == 0x5c) && (thirdChar >= 0x41 && thirdChar <= 0x5a) &&
            // Validate the rest of the path as a valid share name
            FUN_00b9fa49(pathChars + 2, &DAT_00e36ef4) != 0) {
            return true;
        }
    }
    // Check for drive letter path: "X:\"
    else if ((firstChar >= 0x41 && firstChar <= 0x5a) &&  // letter
             (secondChar == 0x3a) &&                       // colon
             (thirdChar == 0x5c)) {                        // backslash
        return true;
    }
    
    return false;
}