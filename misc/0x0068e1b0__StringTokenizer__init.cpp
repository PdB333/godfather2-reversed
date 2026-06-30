// FUNC_NAME: StringTokenizer::init
// Address: 0x0068e1b0
// Role: Initializes a string tokenizer/paser state from a given C string.
// The class stores multiple pointers and lengths for parsing operations.

class StringTokenizer {
public:
    void init(const char* str);

private:
    const char* m_pBufferStart;   // +0x00: pointer to beginning of buffer
    const char* m_pCurrent;       // +0x04: current parse position (initially same as start)
    const char* m_pEnd;           // +0x08: end pointer (initially point to start, meaning no token)
    int m_tokenLength;            // +0x0C: length of current token (full string length)
    int m_delimiterFlag;          // +0x10: delimiter indicator (0 = no delimiter set)
    int m_remainingLength;        // +0x14: remaining characters count (same as token length initially)
    const char* m_pOriginal;      // +0x18: copy of original string pointer
    int m_originalLength;         // +0x1C: length of original string (same as token length)
    int m_flags;                  // +0x20: general flags (0 initially)
    int m_someCount;              // +0x24: additional counter (same as length)
};

void __thiscall StringTokenizer::init(const char* str) {
    // Save original pointer multiple times
    m_pBufferStart = str;
    m_pCurrent     = str;
    m_pEnd         = str;
    m_delimiterFlag = 0;

    // First pass: find end of string and compute token length
    const char* pScan = str;
    while (*pScan) {
        pScan++;
    }
    // pScan now points one past the null terminator
    // Length = (pScan - (str + 1))   // because str+1 is second character, so full length is computed correctly
    m_tokenLength     = pScan - (str + 1);
    m_remainingLength = m_tokenLength;

    // Store original pointer again
    m_pOriginal = str;
    m_flags = 0;

    // Second pass: recompute length using a different pointer base
    const char* pStartPlusOne = str + 1;
    // Reuse the parameter variable (now local copy) to scan again
    while (*str) {
        str++;
    }
    // str now points one past the null
    m_originalLength = str - pStartPlusOne;
    m_someCount      = m_originalLength;
}