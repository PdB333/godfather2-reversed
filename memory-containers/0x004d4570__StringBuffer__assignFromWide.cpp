// FUNC_NAME: StringBuffer::assignFromWide
// Address: 0x004d4570
// Converts a null-terminated UTF-16 (wide) string (short*) into an ASCII buffer (char*)
// This object holds a dynamically allocated char buffer and its length.
// If input is NULL, the buffer is freed (via FUN_004d4060) and length is set to 0.

class StringBuffer {
public:
    char*  m_buffer;   // +0x00 : allocated char buffer
    int    m_length;   // +0x04 : length of current string (not including null)

    // Allocates a new buffer large enough for size+1 chars
    // (callee: FUN_004d3fe0, probably malloc)
    void allocBuffer(int size);

    // Frees the current buffer (callee: FUN_004d4060)
    void freeBuffer(int a, int b); // parameters may be flags; typically (0,0)

    // Assign a wide (16-bit) string, converting each wide char to its low byte.
    // Returns the new length stored in m_length.
    int assignFromWide(const short* wstring);
};

int StringBuffer::assignFromWide(const short* wstring) {
    // If input is null, free the buffer and return current length (likely 0 after free)
    if (wstring == nullptr) {
        freeBuffer(0, 0);
        return m_length;
    }

    // Find length of wide string (number of non-null wide characters)
    const short* p = wstring;
    while (*p != 0) {
        p++;
    }
    int wlen = (p - wstring); // number of wide chars

    // Allocate room for corresponding char buffer (including null)
    allocBuffer(wlen + 1);

    // Copy each wide character as a single char (low byte)
    for (int i = 0; i < wlen; i++) {
        m_buffer[i] = (char)wstring[i];
    }
    m_buffer[wlen] = '\0';
    m_length = wlen;
    return m_length;
}