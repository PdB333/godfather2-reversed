// FUNC_NAME: MemoryPool::MemoryPool
struct MemoryPool {
    uint* m_pBuffer;        // +0x00: pointer to allocated integer buffer
    int   m_numElements;    // +0x04: number of elements (each 4 bytes)
    int   m_field08;        // +0x08: initialized to 0
    int   m_field0C;        // +0x0C: initialized to 0
    int   m_field10;        // +0x10: initialized to 0
    byte  m_field14;        // +0x14: initialized to 0

    // Constructor at 0x004cfc30
    // elementCount: size of buffer in number of ints (passed in EAX via __fastcall)
    // blockGroupInitializer: used to compute number of initialization groups (each 1024 units)
    __thiscall MemoryPool(int elementCount, int blockGroupInitializer) {
        m_numElements = elementCount;
        m_pBuffer = nullptr;  // temp set to 0, then allocated below
        m_field08 = 0;
        m_field0C = 0;
        m_field10 = 0;
        m_field14 = 0;

        // Allocate buffer: elementCount * sizeof(uint) bytes using custom allocator (FUN_009c8e50)
        // In the original code, this is a custom memory allocator; replaced with new for clarity.
        m_pBuffer = new uint[elementCount]; // allocate and zero
        memset(m_pBuffer, 0, elementCount * 4);

        // Perform initialization for each group of 1024 blocks
        // blockGroupInitializer is likely total blocks or size in some unit
        uint groupCount = (blockGroupInitializer + 0x3FF) >> 10; // ceil division by 1024
        while (groupCount--) {
            FUN_004cfd30(); // called to initialize a group (likely increment internal state or prep blocks)
        }
    }
};