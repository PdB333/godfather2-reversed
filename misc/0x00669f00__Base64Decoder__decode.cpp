// FUNC_NAME: Base64Decoder::decode
class Base64Decoder {
public:
    int count;        // +0x00
    int elementSize;  // +0x04, size in bytes of each decoded integer
    int sign;         // +0x08
    int* data;        // +0x0C, pointer to array of elementSize * 4 bytes? (memset uses elementSize * 4)
};

int __thiscall Base64Decoder::decode(char* inputString, uint maxLen) {
    // Base64 alphabet: 0-9, A-Z, a-z, +, /
    static const char base64Alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
    int charIndex;
    char ch;
    bool negative = false;

    // Input length validation
    if ((int)maxLen > 64) {
        return -3;
    }

    // Check for leading minus sign
    ch = *inputString;
    if (ch == '-') {
        negative = true;
        inputString++;
    }

    // Reset state
    this->count = 0;
    this->sign = 0;
    memset(this->data, 0, this->elementSize * 4);

    // Process each character
    while (*inputString != '\0') {
        ch = *inputString;

        // If input is shorter than 36 chars (0x24), convert to uppercase for matching
        if ((int)maxLen < 0x24) {
            ch = (char)toupper((int)ch);
        }

        // Find character in base64 alphabet (unrolled search for speed)
        charIndex = 0;
        do {
            if (ch == base64Alphabet[charIndex]) break;
            if (ch == base64Alphabet[charIndex + 1]) { charIndex += 1; break; }
            if (ch == base64Alphabet[charIndex + 2]) { charIndex += 2; break; }
            if (ch == base64Alphabet[charIndex + 3]) { charIndex += 3; break; }
            charIndex += 4;
        } while (charIndex < 64);

        // Stop if character is out of alphabet (index >= maxLen)
        if ((int)maxLen <= charIndex) break;

        // Process the decoded index through internal state machines
        int result = FUN_00668f50();  // validation/accumulation step
        if (result != 0) return result;

        result = FUN_00665820();      // progress to next element
        if (result != 0) return result;

        inputString++;
    }

    // Set sign flag only if we decoded at least one element
    if (this->count != 0) {
        this->sign = (int)negative;
    }

    return 0;
}