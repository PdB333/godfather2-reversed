// FUNC_NAME: CPacketBuffer::CPacketBuffer

#include <windows.h> // for CRITICAL_SECTION and InitializeCriticalSection

// Forward declaration of custom allocator
void* allocateBuffer(int size);
void initializeGlobals(); // from FUN_00abd570

class CPacketBuffer
{
public:
    // Constructor-style initialization
    CPacketBuffer(int bufferCapacity);

    // Fields (offsets relative to this)
    int m_head;          // +0x00
    int m_tail;          // +0x04
    char m_bSomeFlag;    // +0x08 (byte at start of word, originally set via cast to undefined1*)
    // padding to align to 4 bytes? The original code sets unaff_ESI[2]=0 as a byte, but subsequent fields at +0xA8 are 4-byte aligned,
    // so there may be padding after m_bSomeFlag. We assume structure packing of 4 bytes.
    int m_unknownField1; // +0xA8 (0x2a * 4 = 0xA8)
    int m_invalidMarker; // +0xAC (0x2b) = 0xFFFFFFFF
    int m_errorMarker;   // +0xB0 (0x2c) = 0xFFFFFF99
    int m_fieldX[7];     // +0xB4 to +0xD0 (0x2d to 0x34 inclusive)
    void* m_buffer;      // +0xD8 (0x36) allocated pointer
    int m_capacity;      // +0xDC (0x37) element count
    int m_usedCount;     // +0xE0 (0x38)
    int m_freeCount;     // +0xE4 (0x39)
    CRITICAL_SECTION m_cs; // +0xE8 (0x3a * 4)
    int m_fieldAfterCS[4]; // +0x108 (0x42 to 0x45)
};

// Reconstructed constructor
CPacketBuffer::CPacketBuffer(int bufferCapacity)
{
    // Set initial state
    m_head = 0;
    m_tail = 0;
    m_bSomeFlag = 0; // byte set via pointer cast

    m_unknownField1 = 0;
    m_invalidMarker = -1;               // 0xFFFFFFFF
    m_errorMarker = -103;               // 0xFFFFFF99
    for (int i = 0; i < 7; i++)        // fields from 0x2d to 0x34
        m_fieldX[i] = 0;

    // Allocate buffer: capacity * 4 bytes (size of each element?)
    // The original code computes size = bufferCapacity * 4, with overflow check
    int size = bufferCapacity * 4;      // simplified, original used uint64 to check overflow
    m_buffer = allocateBuffer(size);
    m_capacity = bufferCapacity;

    m_usedCount = 0;
    m_freeCount = 0;

    // Initialize the critical section
    InitializeCriticalSection(&m_cs);

    // Set remaining fields to zero
    m_fieldAfterCS[0] = 0;
    m_fieldAfterCS[1] = 0;
    m_fieldAfterCS[2] = 0;
    m_fieldAfterCS[3] = 0;

    // Global initialization call
    initializeGlobals();

    // Set byte flag again? Actually the original code wrote a byte after the call.
    // But we already set m_bSomeFlag = 0 earlier. To be faithful, we set it again here.
    // However, the original sets it as the very last thing, so we keep it here.
    m_bSomeFlag = 0;
}