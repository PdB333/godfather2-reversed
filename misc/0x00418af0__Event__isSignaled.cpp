// FUNC_NAME: Event::isSignaled
// Address: 0x00418af0
// Role: Checks if a per-thread event object is signaled by looking up handle data in thread-local storage.

#include <cstdint>

// Forward declaration of the event status check function.
int checkEventStatus(const uint32_t* eventHandle);

class Event
{
public:
    bool isSignaled();
};

bool Event::isSignaled()
{
    // Offset of index within the event object.
    static const uint32_t kIndexOffset = 0x18;

    // TLS and thread context offsets (Windows x86).
    static const uint32_t kTlsArrayOffset = 0x2c;   // fs:[0x2c] -> TLS array pointer
    static const uint32_t kTlsSlotSize   = 4;       // Each TLS slot is 4 bytes
    static const uint32_t kThreadCtxBase = 8;       // Offset in first TLS slot to event data base
    static const uint32_t kHandleArray   = 0x30;    // Offset of handle array from base
    static const uint32_t kStateArray    = 0x70;    // Offset of additional state array (unused)

    int32_t index = *(int32_t*)((uint8_t*)this + kIndexOffset);

    // Read TLS pointer.
    uint32_t* tlsArray = *(uint32_t**)__readfsdword(kTlsArrayOffset);
    // First TLS slot points to per-thread context.
    uint32_t* threadCtx = *(uint32_t**)tlsArray;
    uint32_t base = (uint32_t)threadCtx + kThreadCtxBase;

    // Read 12-byte handle from the handle array.
    uint32_t* handlePtr = (uint32_t*)(base + kHandleArray + index);
    uint32_t handle[3];
    handle[0] = handlePtr[0];
    handle[1] = handlePtr[1];
    handle[2] = handlePtr[2];

    // Call the low-level function to check handle state.
    int status = checkEventStatus(handle);
    return (status == 2);
}