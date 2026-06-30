// FUNC_NAME: StringHasher::printFormattedHash
#include <cstdio>
#include <cstring>

class StringHasher {
public:
    int field_0;  // +0x00
    int field_4;  // +0x04

    // 0x004ead40
    void __fastcall printFormattedHash(char* inputString) {
        if (inputString != nullptr) {
            size_t len = strlen(inputString);
            if (len > 12) {
                // Compute hash of the string excluding the last 4 characters
                unsigned int hash = hashStringRange(inputString, inputString + len - 4);
                char buffer[12];
                // Format: hash as 8 hex digits followed by the last 4 characters
                sprintf(buffer, "%08x%s", hash, inputString + len - 4);
            }
            logFormattedHash();
            return;
        }
        // Clear the two fields when no string is provided
        this->field_0 = 0;
        this->field_4 = 0;
    }

private:
    // Helper: compute hash over a range [begin, end)
    unsigned int __fastcall hashStringRange(char* begin, char* end);
    void __fastcall logFormattedHash();
};