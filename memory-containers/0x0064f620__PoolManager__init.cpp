// FUNC_NAME: PoolManager::init
// 0x0064f620: Initializes a pool of fixed-size elements (0x30 bytes each, 0x400 elements) and supporting buffers.
// This function is called once early in the game to set up a memory pool, possibly for network packets or other objects.
// It checks if the pool has already been allocated (m_poolPtr != NULL) and returns early if so.
// It allocates three buffers:
//   - m_poolStructPtr (0x1fc): 0x1000 bytes, zeroed (likely for pool metadata)
//   - m_poolArray (0x214): 0xc000 bytes, then constructs 0x400 elements of size 0x30 using a constructor function at LAB_0064f350,
//     then stores the element index (i) in each element at offset +0x28.
//   - m_someBuffer (0x218): 0x1000 bytes, zeroed word by word.
// Counters at 0x200 and 0x204 are set to zero.

class PoolManager {
public:
    void __thiscall init();

private:
    // offsets relative to this
    // +0x1fc: pointer to first buffer (0x1000 bytes)
    void* m_poolStructPtr;
    // +0x200: counter / flag
    int m_counter1;
    // +0x204: counter / flag
    int m_counter2;
    // +0x214: pointer to array of 0x400 elements (size 0x30 each)
    void* m_poolArray;
    // +0x218: pointer to second buffer (0x1000 bytes)
    void* m_someBuffer;
};

// Forward declaration of the allocation function (likely memoryAllocate)
extern void* __cdecl allocate(size_t size);

// Forward declaration of the vector constructor iterator (internal)
extern void __cdecl vector_constructor_iterator(void* array, int elementSize, int count, void* constructorFunc);

// Constructor function for the pool elements (defined elsewhere)
extern void __cdecl poolElementCtor(void* element); // at LAB_0064f350

// Structure of a pool element (size 0x30)
struct PoolElement {
    char padding[0x28];            // unknown fields
    int m_index;                   // +0x28: index of this element (0..1023)
    char remaining[0x30 - 0x2C]; // ensures total size 0x30
};

void __thiscall PoolManager::init() {
    if (m_poolStructPtr != nullptr) {
        // Already initialized – do nothing
        return;
    }

    // Reset counters
    m_counter1 = 0;
    m_counter2 = 0;

    // Allocate and zero the first buffer (0x1000 bytes)
    m_poolStructPtr = allocate(0x1000);
    memset(m_poolStructPtr, 0, 0x1000);

    // Allocate the pool array (0xc000 bytes = 0x400 * 0x30)
    void* pool = allocate(0xc000);
    m_poolArray = pool;

    if (pool != nullptr) {
        // Construct each element using the element constructor
        // This is equivalent to placement-new for an array
        vector_constructor_iterator(pool, 0x30, 0x400, &poolElementCtor);

        // Set the index field in each element
        // Loop increments by 0x30 bytes per element
        for (int i = 0; i < 0x400; ++i) {
            PoolElement* elem = reinterpret_cast<PoolElement*>(
                static_cast<char*>(pool) + i * 0x30);
            elem->m_index = i;
        }
    }

    // Allocate and zero the second buffer (0x1000 bytes) – word by word
    m_someBuffer = allocate(0x1000);
    if (m_someBuffer != nullptr) {
        // Zero out 0x400 words (0x1000 / 4)
        int* words = static_cast<int*>(m_someBuffer);
        for (int j = 0; j < 0x400; ++j) {
            words[j] = 0;
        }
    }
}