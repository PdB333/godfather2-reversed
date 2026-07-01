// FUNC_NAME: EARS::Framework::GUID::ensureHandleComputed

// Function address: 0x00983ab0
// This function converts a 16-byte GUID (at offsets +0xF0 to +0xFC) into a handle
// (stored at +0x100) if the handle is invalid and the GUID is not null nor a known dead pattern.
// It is likely used for lazy initialization of a cached handle (e.g., string or pointer) from a UUID.

#include <cstdint>

class GUID {
public:
    // Fields (offsets from this):
    // +0xF0 : uint32_t data[4]  (16-byte GUID)
    // +0x100: void* handle       (cached handle, e.g., hash or string pointer)

    // Known dead/poison patterns used to indicate uninitialized or freed GUIDs
    static constexpr uint32_t kDeadPattern0 = 0xBAADF0BA;  // -0x45245246
    static constexpr uint32_t kDeadPattern1 = 0xBEEFEEEF;  // -0x41104111
    static constexpr uint32_t kDeadPattern2 = 0xEAC15A55;  // -0x153EA5AB
    static constexpr uint32_t kDeadPattern3 = 0x91100911;  // -0x6EEFF6EF

    // Checks if the GUID is non-zero and not a dead pattern, then computes the handle.
    void ensureHandleComputed();

    // Internal: the 16-byte GUID storage accessed as uint32_t[4]
    uint32_t* getGuidData() { return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0xF0); }
    // Check if the entire 16 bytes are zero (null GUID)
    bool isNullGuid() const;
    // Check if GUID matches the dead pattern (all four uint32s equal the known dead values)
    bool isDeadPattern() const;
};

// Check if all four uint32s are zero
inline bool GUID::isNullGuid() const {
    const uint32_t* d = reinterpret_cast<const uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0xF0);
    return (d[0] == 0 && d[1] == 0 && d[2] == 0 && d[3] == 0);
}

// Check if the GUID equals the dead/poison pattern
inline bool GUID::isDeadPattern() const {
    const uint32_t* d = reinterpret_cast<const uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0xF0);
    return (d[0] == kDeadPattern0 &&
            d[1] == kDeadPattern1 &&
            d[2] == kDeadPattern2 &&
            d[3] == kDeadPattern3);
}

// Implementation of ensureHandleComputed
void GUID::ensureHandleComputed() {
    // If handle is already computed (non-zero), do nothing
    if (*(void**)(reinterpret_cast<uintptr_t>(this) + 0x100) != nullptr)
        return;

    // Check if GUID is null or matches the dead pattern
    if (isNullGuid() || isDeadPattern())
        return;

    // Compute the handle from the GUID data (function at 0x00446100)
    // This likely converts the 16-byte GUID into a string, hash, or other identifier.
    // Arguments: pointer to GUID data and a flag (0 in this case)
    void* handle = reinterpret_cast<void*(__fastcall*)(int*, int)>(0x00446100)(
                        reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xF0), 0);
    *(void**)(reinterpret_cast<uintptr_t>(this) + 0x100) = handle;
}