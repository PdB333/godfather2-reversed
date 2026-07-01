// FUN_NAME: EARSList::growSize
// Function address: 0x007edbf0
// Purpose: Safely increments the list size with overflow detection. If adding `addSize` would exceed the maximum allowable size (0x9249249), throws an exception with the message "list<T> too long".
// Notes: The maximum size 0x9249249 (153,391,689) is a hardcoded limit, possibly related to memory or indexing constraints in the EARS engine.
// Known callers: 0x007ede10, 0x007eddb0 (likely insert/push_back operations)

class EARSList {
public:
    // +0x00: vtable pointer (size 4)
    // +0x04: ... other members ...
    // +0x1c: current number of elements (uint32_t size)
    uint32_t size;

    // Adds `addSize` to the list size, with overflow protection.
    // If the operation would overflow the maximum size, throws a std::overflow_error.
    void __thiscall growSize(uint32_t addSize) {
        constexpr uint32_t kMaxListSize = 0x9249249U;  // 153,391,689 elements

        if (addSize <= (kMaxListSize - size)) {
            size += addSize;
            return;
        }

        // Overflow: throw an exception with a descriptive message.
        // The original implementation uses a custom exception function (FUN_0043f9f0)
        // and string setup, but the logical equivalent is:
        throw std::overflow_error("list<T> too long");
    }
};