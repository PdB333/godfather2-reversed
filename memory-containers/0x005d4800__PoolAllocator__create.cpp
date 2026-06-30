// FUNC_NAME: PoolAllocator::create
// Function address: 0x005d4800
// This function initializes a fixed-size block allocator pool by allocating a chunk of memory
// from a source allocator and setting up a free list of blocks.

class PoolAllocator {
public:
    // Members at known offsets (assuming 32-bit, sizeof(int)=4)
    int m_blockHeaderSize;        // +0x08 (uVar1)
    int m_blockCount;             // +0x0C (iVar2)
    int m_blockSize;              // +0x10 (iVar7? actually iVar7 from code, but offset 0x10)
    int m_poolCount;              // +0x14 (incremented each allocation)
    Allocator* m_allocator;       // +0x18 (pointer to base allocator with vtable)

    // Pool header structure returned by this function
    struct PoolHeader {
        int m_flags;              // +0x00
        int m_unknown1;           // +0x04
        void* m_firstFreeBlock;   // +0x08
        void* m_endOfPool;        // +0x0C
        int m_unknown2;           // +0x10
        // followed by blocks of size m_blockSize
    };

    // Returns a pointer to the newly created PoolHeader, or 0 on failure.
    PoolHeader* create() {
        // Calculate aligned header size (round up to multiple of m_blockHeaderSize?)
        int alignedHeaderSize = ((m_blockHeaderSize + 0x13) / m_blockHeaderSize) * m_blockHeaderSize;

        // Allocate memory from underlying allocator via virtual function (vtable[1])
        PoolHeader* pool = (PoolHeader*)((*(code**)(m_allocator->vtable))[1])(m_allocator);

        if (pool == nullptr) {
            return nullptr;
        }

        // Increment pool count
        m_poolCount++;

        // Compute the start of free blocks (after header)
        void* firstBlock = (char*)pool + alignedHeaderSize;

        // Setup header fields
        pool->m_flags = 0;
        pool->m_unknown1 = 0;
        pool->m_firstFreeBlock = firstBlock;
        // End of pool = total allocated memory (should be header + count * blockSize)
        pool->m_endOfPool = (char*)pool + m_blockCount * m_blockSize + alignedHeaderSize;
        pool->m_unknown2 = 0;

        // Initialize free list (linked list of blocks)
        void* current = firstBlock;
        for (int i = 1; i < m_blockCount; i++) {
            void* next = (char*)current + m_blockSize;
            *(void**)current = next;
            current = next;
        }
        // Last block points to null
        *(void**)current = nullptr;

        return pool;
    }
};

// Allocator base (simplified)
class Allocator {
public:
    void** vtable; // +0x00
    // vtable[0] = destructor? vtable[1] = allocate?
};