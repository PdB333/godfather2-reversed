// BUFFERPOOL::INITIALIZE (0x006678c0)
// Initializes a fixed-size buffer pool with alignment to 0x80 (128) bytes.
// The struct layout:
//   +0x00: m_usedCount (int)
//   +0x04: m_alignedSize (int)
//   +0x08: m_freeCount (int)
//   +0x0C: m_buffer (void*)
// Returns 0 on success, -2 on allocation failure.

class BufferPool {
public:
    int Initialize(int requestedSize);
private:
    int m_usedCount;       // +0x00
    int m_alignedSize;     // +0x04
    int m_freeCount;       // +0x08
    void* m_buffer;        // +0x0C
};

int BufferPool::Initialize(int requestedSize) {
    // Compute alignment offset: low 6 bits (mod 64) plus sign handling.
    unsigned int temp = requestedSize & 0x8000003f;
    if ((int)temp < 0) {
        // If high bit set, adjust to make it positive in a 6-bit wrap.
        temp = ((temp - 1) | 0xffffffc0) + 1;
    }
    // Round up requestedSize to the next multiple of 0x80 (128) that is at least 128.
    int actualSize = requestedSize + (0x80 - temp);  // actual size in elements (4-byte units)

    // Allocate buffer of actualSize * 4 bytes.
    void* newBuffer = calloc(4, actualSize);
    m_buffer = newBuffer;
    if (newBuffer == nullptr) {
        return -2; // allocation failed
    }

    m_alignedSize = actualSize;
    m_usedCount = 0;
    m_freeCount = 0;
    return 0;
}