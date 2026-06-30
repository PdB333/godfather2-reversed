// FUNC_NAME: PoolManager::initialize

// Reconstructed C++ for PoolManager initialization at 0x00596400
// Handles three pools of different element types, each with a free list (sequential indices, -1 sentinel).

class PoolManager {
public:
    // Vtable functions at offsets:
    // +0x10: virtual uint32 createDefaultElementForPool1();
    // +0x14: virtual uint32 createDefaultElementForPool2();
    // +0x18: virtual uint32 createDefaultElementForPool3();

    // Fields:
    // +0x00: void* vtable
    // +0x04: bool m_initialized; // char
    // +0x08: int m_pool1Size;
    // +0x0C: int m_pool2Size;
    // +0x10: int m_pool3Size;
    // +0x14: uint32* m_pool1Elements; // array of element values (size m_pool1Size)
    // +0x18: int* m_pool1FreeIndices; // array of next free index (size m_pool1Size)
    // +0x1C: int m_pool1FreeHead;     // head of free list (index)
    // +0x20: uint32* m_pool2Elements;
    // +0x24: int* m_pool2FreeIndices;
    // +0x28: int m_pool2FreeHead;
    // +0x2C: uint32* m_pool3Elements;
    // +0x30: int* m_pool3FreeIndices;
    // +0x34: int m_pool3FreeHead;
};

void __thiscall PoolManager::initialize(int* thisPtr, int pool1Size, int pool2Size, int pool3Size)
{
    // Cast pointer to class layout
    PoolManager* self = reinterpret_cast<PoolManager*>(thisPtr);
    int* asInt = reinterpret_cast<int*>(thisPtr);

    if (self->m_initialized != 0) {
        return;
    }

    // Store sizes
    asInt[2] = pool1Size;           // +0x08
    asInt[4] = pool3Size;           // +0x10 (note: swapped order in assignment)
    asInt[1] = 1;                   // +0x04: m_initialized = true
    asInt[3] = pool2Size;           // +0x0C
    asInt[7] = 0;                   // +0x1C: m_pool1FreeHead = 0

    // Allocate for pool1
    void* (*allocFunc)(int) = reinterpret_cast<void* (*)(int)>(*(void***)0x01205590[0x18]); // gMemoryManager->allocate
    asInt[5] = reinterpret_cast<int>(allocFunc(pool1Size * 4)); // +0x14: m_pool1Elements
    asInt[6] = reinterpret_cast<int>(allocFunc(pool1Size * 4)); // +0x18: m_pool1FreeIndices

    uint32* elem1 = reinterpret_cast<uint32*>(asInt[5]);
    int* idx1 = reinterpret_cast<int*>(asInt[6]);

    // Fill pool1 arrays
    int i;
    for (i = 0; i < pool1Size; i++) {
        uint32 defaultVal = reinterpret_cast<uint32 (__thiscall *)(PoolManager*)>(self->vtable + 0x10)(self);
        elem1[i] = defaultVal;
        idx1[i] = i + 1; // Link to next free slot (sequential)
    }
    idx1[pool1Size - 1] = -1; // End of free list

    asInt[10] = 0; // +0x28: m_pool2FreeHead = 0

    // Allocate for pool2
    asInt[8] = reinterpret_cast<int>(allocFunc(pool2Size * 4)); // +0x20
    asInt[9] = reinterpret_cast<int>(allocFunc(pool2Size * 4)); // +0x24

    uint32* elem2 = reinterpret_cast<uint32*>(asInt[8]);
    int* idx2 = reinterpret_cast<int*>(asInt[9]);

    for (i = 0; i < pool2Size; i++) {
        uint32 defaultVal = reinterpret_cast<uint32 (__thiscall *)(PoolManager*)>(self->vtable + 0x14)(self);
        elem2[i] = defaultVal;
        idx2[i] = i + 1;
    }
    idx2[pool2Size - 1] = -1;

    asInt[13] = 0; // +0x34: m_pool3FreeHead = 0

    // Allocate for pool3
    asInt[11] = reinterpret_cast<int>(allocFunc(pool3Size * 4)); // +0x2C
    asInt[12] = reinterpret_cast<int>(allocFunc(pool3Size * 4)); // +0x30

    uint32* elem3 = reinterpret_cast<uint32*>(asInt[11]);
    int* idx3 = reinterpret_cast<int*>(asInt[12]);

    for (i = 0; i < pool3Size; i++) {
        uint32 defaultVal = reinterpret_cast<uint32 (__thiscall *)(PoolManager*)>(self->vtable + 0x18)(self);
        elem3[i] = defaultVal;
        idx3[i] = i + 1;
    }
    idx3[pool3Size - 1] = -1;
}