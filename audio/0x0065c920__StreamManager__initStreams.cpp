// FUNC_NAME: StreamManager::initStreams
// Function address: 0x0065c920
// Initializes a StreamManager object by setting up two streams from a global stream manager,
// and allocating two 16-byte objects using a constructor function.

class StreamManager {
public:
    // Fields (size: 36 bytes)
    int m_someId;                      // +0x00 (set to 0x11)
    int m_someValue1;                  // +0x04 (set to 0)
    int m_someValue2;                  // +0x08 (set to 0)
    Stream m_stream1;                  // +0x0C (8 bytes, initialized via createStream)
    Stream m_stream2;                  // +0x14 (8 bytes, initialized via createStream)
    SomeObject* m_obj1;                // +0x1C (allocated and constructed)
    SomeObject* m_obj2;                // +0x20 (allocated and constructed)

    void __thiscall initStreams() {
        bool bGlobalInitNeeded = (g_streamInitialized == 0);

        // Set up basic fields
        this->m_someId = 0x11;
        this->m_someValue1 = 0;
        this->m_someValue2 = 0;

        // Initialize global stream manager if not already done
        if (bGlobalInitNeeded) {
            g_streamInitialized = 1;
            initStreamManager(&g_streamManagerData);
            setupStreamManager(&g_streamManagerData);
        }

        // Create first stream from the global manager
        createStream(&this->m_stream1, 8, &g_streamManagerData);

        // (Second check is redundant but kept as in original; g_streamInitialized is already 1)
        if (g_streamInitialized == 0) {
            g_streamInitialized = 1;
            initStreamManager(&g_streamManagerData);
            setupStreamManager(&g_streamManagerData);
        }

        // Create second stream
        createStream(&this->m_stream2, 8, &g_streamManagerData);

        // Allocate and construct first 16-byte object
        void* mem1 = allocateMemory(0x10);
        if (mem1 != nullptr) {
            this->m_obj1 = constructSomeObject(mem1);
        } else {
            this->m_obj1 = nullptr;
        }

        // Allocate and construct second 16-byte object
        void* mem2 = allocateMemory(0x10);
        if (mem2 != nullptr) {
            this->m_obj2 = constructSomeObject(mem2);
        } else {
            this->m_obj2 = nullptr;
        }
    }
};

// Global flag and stream manager instance (addresses from decompiled context)
static uint8_t g_streamInitialized;              // DAT_0120588f
static StreamManagerData g_streamManagerData;    // DAT_01203740

// External functions (callees)
extern void initStreamManager(StreamManagerData* mgr);
extern void setupStreamManager(StreamManagerData* mgr);
extern void createStream(void* streamDest, int size, StreamManagerData* mgr);
extern void* allocateMemory(int size);
extern SomeObject* constructSomeObject(void* mem);  // FUN_0065c7c0