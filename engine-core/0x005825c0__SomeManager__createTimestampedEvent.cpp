// FUNC_NAME: SomeManager::createTimestampedEvent
// Function address: 0x005825c0
// Creates a small 8-byte object holding a unique ID (from getGlobalUniqueId) and a zero flag.

class SomeManager {
public:
    // Virtual function for custom memory allocation (via vtable)
    virtual void* allocMemory(size_t size, int* pAlignment) = 0; // alignment parameter (often 0)
};

// Structure returned – two 32-bit fields
struct TimestampedEvent {
    int uniqueId; // +0x00: result of getGlobalUniqueId()
    int reserved; // +0x04: always 0 (possibly flags or padding)
};

__thiscall TimestampedEvent* SomeManager::createTimestampedEvent() {
    int id = getGlobalUniqueId(); // FUN_004dafd0 – assumed to return a global unique ID
    int alignInfo = 0;            // alignment input for allocator
    int unused1 = 0;              // local_8, unused
    int unused2 = 0;              // local_4, unused

    TimestampedEvent* event = (TimestampedEvent*)this->allocMemory(sizeof(TimestampedEvent), &alignInfo);
    if (event != nullptr) {
        event->uniqueId = id;
        event->reserved = unused2; // always 0
        return event;
    }
    return nullptr;
}