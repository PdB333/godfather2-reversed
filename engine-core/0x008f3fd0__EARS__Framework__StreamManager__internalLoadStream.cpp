// FUNC_NAME: EARS::Framework::StreamManager::internalLoadStream
// Address: 0x008f3fd0
// This function loads a stream resource from a reference, releasing any existing stream handle first.

#include <cstdint>

// Forward declaration of helper functions
uint32_t* __cdecl parseResourceReference(uint32_t* param); // FUN_004d3b50
void __cdecl loadStreamData(const char* name, uint32_t size); // FUN_004dba80
void __cdecl initStreamBuffer(uint16_t* buffer, int32_t unknown, uint32_t flags); // FUN_004dbb10

// Unknown structures/classes (from offsets)
class StreamHandle { /* vtable +0x4 = release/destructor */ };
class StreamBuffer { /* buffer management */ };

class StreamManager {
public:
    // Offset: +0x2098 - pointer to an active stream handle (to be released)
    StreamHandle* m_pActiveStreamHandle;

    // Offset: +0x2260 - pointer to the current stream buffer (may be stack default)
    uint16_t* m_pCurrentBuffer;

    // Default stream buffer (static constant) - likely DAT_00e2df14
    static uint16_t* const kDefaultBuffer = (uint16_t*)0x00e2df14;

    // Default resource name fallback - likely DAT_0120546e
    static const char* const kFallbackName = (const char*)0x0120546e;

    void internalLoadStream(uint32_t resourceRef) {
        // 1. Release any existing stream handle
        if (m_pActiveStreamHandle != nullptr) {
            // Call virtual destructor at vtable+4 (release)
            m_pActiveStreamHandle->release();
            m_pActiveStreamHandle = nullptr;
        }

        // 2. Parse the resource reference to get name and size
        uint32_t* refData = parseResourceReference(resourceRef);
        const char* resourceName = (const char*)*refData;
        uint32_t resourceSize = refData[1];

        // Fallback if name is null
        if (resourceName == nullptr) {
            resourceName = kFallbackName;
        }

        // 3. Load the stream data (probably allocate and read)
        loadStreamData(resourceName, resourceSize);

        // 4. Check if the current buffer is not the default stack buffer
        if (m_pCurrentBuffer != &defaultStackBuffer) {
            // Local copy of buffer pointer (from stack)
            uint16_t* buffer = defaultStackBuffer;
            if (buffer == nullptr) {
                buffer = kDefaultBuffer;
            }
            // Initialize the stream buffer with zero and flags
            initStreamBuffer(buffer, 0, defaultStackFlags);
        }

        // 5. Release the stack buffer if it was allocated
        if (defaultStackBuffer != nullptr) {
            (*defaultStackReleaseFunc)(defaultStackBuffer);
        }

        // 6. Release a second local resource (if any)
        if (defaultStackExtra != 0) {
            (*defaultStackExtraFunc)(defaultStackExtra);
        }

        return;
    }

private:
    // Local stack variables (from decompiler)
    uint16_t* defaultStackBuffer;    // puStack_20
    uint32_t defaultStackFlags;      // uStack_1c
    void (*defaultStackReleaseFunc)(uint16_t*); // pcStack_14
    int32_t defaultStackExtra;       // local_10
    void (*defaultStackExtraFunc)(int32_t); // pcStack_4
};
```