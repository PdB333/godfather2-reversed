// FUNC_NAME: String::isAbsolutePath
// Address: 0x004d5ad0
// Checks if the string represents an absolute path (Windows drive letter or UNC path).

#include <cstring>

class String {
public:
    char* data;  // +0x00
    int length;  // +0x04

    bool isAbsolutePath() const {
        if (length <= 2) {
            return false;
        }

        // Convert first three characters to uppercase for comparison
        char c0 = data[0];
        if (c0 >= 'a' && c0 <= 'z') {
            c0 -= 0x20;  // to uppercase
        }
        char c1 = data[1];
        if (c1 >= 'a' && c1 <= 'z') {
            c1 -= 0x20;
        }
        char c2 = data[2];
        if (c2 >= 'a' && c2 <= 'z') {
            c2 -= 0x20;
        }

        // Check UNC path: \\<letter>\...
        if (c0 == '\\') {
            if (c1 == '\\' && c2 >= 'A' && c2 <= 'Z') {
                // Ensure there is at least one more backslash after the server name
                if (_strstr(data + 2, "\\") != nullptr) {
                    return true;
                }
            }
        }
        // Check drive letter path: <drive>:\...
        else if (c0 >= 'A' && c0 <= 'Z' && c1 == ':' && c2 == '\\') {
            return true;
        }

        return false;
    }
};