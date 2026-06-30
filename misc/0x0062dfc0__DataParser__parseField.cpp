// FUNC_NAME: DataParser::parseField
// Reconstructed from 0x0062dfc0 in Godfather 2 (EARS engine)
//
// Parses a binary token from the stream and extracts data into an allocated slot.
// The token format: marker (5) at offset 0, key at offset 4, two ints at offsets 8 and 16 that must not be -1.
// Reads a 16-byte block from the end of the buffer (pops two ints) and stores them into the slot.
class DataParser {
public:
    int* m_pEnd;       // +0x08: end pointer (current write position, stack grows down)
    int* m_pCurrToken; // +0x0C: current token pointer in input stream

    void errorTable(); // FUN_00627ac0: log/assert with "table" string
    void reportError(int code, const char* msg); // FUN_00627a20
    int* allocateSlot(int key); // FUN_00638020: returns pointer to slot for given key

    int parseField();
};

int DataParser::parseField() {
    int* pEnd = m_pEnd;
    int* pCurr = m_pCurrToken;

    // Token at current pointer must be marker 5, and we must have room (pCurr < pEnd)
    if (pEnd <= pCurr || pCurr == nullptr || *pCurr != 5) {
        errorTable();
        // pCurr likely updated by errorTable via extraout_ECX, but not used further
    }

    // Check that the third int in token (offset 8) is not -1
    int* pNext = pCurr + 2; // offset 8 bytes
    if (pEnd <= pNext || pNext == nullptr || *pNext == -1) {
        reportError(2, "value expected");
        // pCurr updated via extraout_ECX_00
    }

    // Check that the fifth int in token (offset 16) is not -1
    pNext = pCurr + 4; // offset 16 bytes
    if (pEnd <= pNext || pNext == nullptr || *pNext == -1) {
        reportError(3, "value expected");
        // pCurr updated via extraout_ECX_01
    }

    // Allocate a slot using the second int in token (offset 4) as key
    int* pSlot = allocateSlot(pCurr[1]); // pCurr[1] is at offset 4

    // Pop two ints from the end of the buffer (stack) and store into slot
    // pEnd[-2] is at m_pEnd - 8, pEnd[-1] at m_pEnd - 4
    *pSlot = *(pEnd - 2);
    *(pSlot + 1) = *(pEnd - 1);

    // Remove the 16-byte block from the buffer (pop 4 ints)
    m_pEnd = m_pEnd - 4; // subtract 4 ints (0x10 bytes)

    return 1;
}