// FUNC_NAME: StringParser::skipNumber

// Reconstructed from Ghidra export at 0x00603490
// This function appears to be a helper that advances a string pointer past an optional minus sign and digits.
// It uses the 'this' pointer to access a member (currentPos) and takes an end pointer as parameter.
// The caller must ensure the member pointer is set before calling.

class StringParser {
public:
    char* currentPos;  // +0x00 (assumed offset, may vary)

    // __thiscall: ECX = this, EDX = end
    void __thiscall skipNumber(char* end) {
        // Skip optional leading minus sign
        if ((end == nullptr || currentPos < end) && *currentPos == '-') {
            currentPos++;
        }
        // Advance while digit (ASCII '0'-'9')
        while ((end == nullptr || currentPos < end) && 
               ((unsigned int)(*currentPos - '0') < 10)) {
            currentPos++;
        }
    }
};