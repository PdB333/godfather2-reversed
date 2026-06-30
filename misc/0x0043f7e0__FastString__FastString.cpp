// FUNC_NAME: FastString::FastString
class FastString {
public:
    FastString(const char* str);
private:
    // +0x04: some 1-byte flag (set to 0)
    char m_flag;
    // +0x14: hash value (initialized to 0)
    int m_hashValue;
    // +0x18: hash type/algorithm identifier (set to 0xf = 15)
    int m_hashType;

    // Helper called after setting fields to compute hash from string and its length
    void computeHash(const char* str, int len);
};

FastString::FastString(const char* str) {
    m_hashType = 0xF;          // Algorithm ID (e.g., FNV-1 or custom variant)
    m_hashValue = 0;           // Reset hash accumulator
    m_flag = 0;                // Clear flag

    // Compute string length without including null terminator
    const char* end = str;
    while (*end != '\0')
        ++end;
    int len = end - str;

    // Perform actual hashing (likely FNV, CRC, or similar)
    computeHash(str, len);
}