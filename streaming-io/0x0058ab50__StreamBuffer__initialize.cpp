// FUNC_NAME: StreamBuffer::initialize
// Address: 0x0058ab50
// Role: Initializes a stream buffer object, allocating a 0x400-byte buffer from a manager's allocator.

// Assumed class layout (offsets from this):
// +0x00: m_buffer (void*) - allocated buffer pointer
// +0x04: m_flags (int) - flags (set to 0)
// +0x08: m_size (int) - buffer size (set to 0x100 = 256)
// +0x0C: m_allocator (void*) - allocator handle from manager
// +0x10: m_manager (int*) - pointer to global stream manager

// External globals
extern int* g_streamManager; // DAT_0120556c
extern void* g_defaultAllocator; // DAT_01218a14

// Forward declaration of helper function (returns allocator handle)
void* FUN_004265d0(AllocatorInfo* info, int* manager);

// Allocator info struct (3 ints)
struct AllocatorInfo {
    int field0;
    int field4;
    int field8;
};

void StreamBuffer::initialize() {
    int* manager = g_streamManager;
    AllocatorInfo allocInfo = {0, 0, 0};

    this->m_flags = 0;          // +0x04
    this->m_size = 0x100;       // +0x08
    this->m_allocator = FUN_004265d0(&allocInfo, manager); // +0x0C
    this->m_manager = manager;  // +0x10

    // Call virtual function at vtable+8 on manager (e.g., prepareAllocator)
    (*(void (**)(void))(*manager + 8))();

    // Get allocator pointer (use default if null)
    void* allocator = this->m_allocator;
    if (allocator == nullptr) {
        allocator = g_defaultAllocator;
    }

    // Call virtual function at vtable+0 on manager with size 0x400 and allocator
    // Returns allocated buffer pointer
    this->m_buffer = (*(void* (*)(int, void*))(**manager))(0x400, allocator); // +0x00
}