// FUNC_NAME: BufferPool::initialize

// Reconstructed C++ for function at 0x0065ba80
// Initializes a fixed-size buffer pool with a control structure and a 0x1000-byte buffer.

class BufferPool {
public:
    // Control structure for the pool (size 0xC)
    struct PoolControl {
        uint32_t freeCount;      // +0x00: number of free blocks (initially 0)
        uint8_t* buffer;         // +0x04: pointer to the allocated buffer
        uint32_t something;      // +0x08: unknown (initially 0)
    };

    // Global pool state
    static PoolControl* s_poolControl;   // DAT_01223b90
    static uint32_t s_bufferSize;        // _DAT_01223b94 (0x1000)
    static uint32_t s_unknown1;          // _DAT_01223b98 (0)
    static uint32_t s_controlSize;       // DAT_01223b9c (0xC)
    static uint32_t s_unknown2;          // DAT_01223ba0 (0)

    // Initialize the pool. Returns pointer to the global PoolControl pointer.
    static PoolControl** initialize() {
        s_bufferSize = 0x1000;  // 4096 bytes

        // Allocate control structure (0xC bytes)
        PoolControl* control = (PoolControl*)FUN_009c8e50(0xC);
        if (control != nullptr) {
            // Allocate the actual buffer (0x1000 bytes)
            uint8_t* buf = (uint8_t*)FUN_009c8e80(0x1000);
            control->buffer = buf;
        }

        s_poolControl = control;
        if (control != nullptr) {
            control->freeCount = 0;
            control->something = 0;
        }

        s_unknown1 = 0;
        s_controlSize = 0xC;
        s_unknown2 = 0;

        return &s_poolControl;
    }
};

// Static member definitions (would be placed in a .cpp file)
BufferPool::PoolControl* BufferPool::s_poolControl = nullptr;
uint32_t BufferPool::s_bufferSize = 0;
uint32_t BufferPool::s_unknown1 = 0;
uint32_t BufferPool::s_controlSize = 0;
uint32_t BufferPool::s_unknown2 = 0;