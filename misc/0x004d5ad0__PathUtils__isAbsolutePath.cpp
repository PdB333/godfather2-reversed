// FUNC_NAME: PathUtils::isAbsolutePath
// Function at 0x004d5ad0: checks if a string (given as {char* data, int length} struct) represents an absolute path (either DOS like C:\ or UNC like \\server\share)
struct PathString {
    char* data;      // +0x00 pointer to string data
    int length;      // +0x04 length of string (not including null terminator)
};

// __fastcall: param_1 (ECX) is pointer to PathString struct
int __fastcall isAbsolutePath(PathString* path) {
    char c1, c2, c3;
    char* str;
    
    // Need at least 3 characters to be absolute
    if (path->length <= 2) {
        return 0;
    }
    
    str = path->data;
    
    // Convert first three characters to uppercase (if they are lowercase letters)
    c1 = *str;
    if ((unsigned int)(c1 - 'a') < 0x1a) {
        c1 = c1 - 0x20; // to uppercase
    }
    
    c2 = str[1];
    if ((unsigned int)(c2 - 'a') < 0x1a) {
        c2 = c2 - 0x20;
    }
    
    c3 = str[2];
    if ((unsigned int)(c3 - 'a') < 0x1a) {
        c3 = c3 - 0x20;
    }
    
    // Check for UNC path: \\server\share... (pattern \\[A-Z]...)
    if (c1 == '\\') {
        // Must have second backslash, third char a letter, and another backslash somewhere after
        if ((c2 == '\\') && ((unsigned char)(c3 + 0xbf) < 0x1a)) { // c3 is uppercase letter after subtraction
            // Look for another backslash starting from position 2 (skip initial \\)
            if (_strstr(str + 2, "\\") != NULL) {
                return 1;
            }
        }
    } else {
        // Check for DOS absolute path: drive letter + colon + backslash (e.g., C:\)
        if ((c1 > '@') && (c1 < '[') && (c2 == ':') && (c3 == '\\')) {
            return 1;
        }
    }
    
    return 0;
}