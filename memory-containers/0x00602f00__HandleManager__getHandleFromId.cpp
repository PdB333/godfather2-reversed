// FUNC_NAME: HandleManager::getHandleFromId

// Reconstructed from Ghidra at 0x00602f00
// This function converts an object ID (or default from this+0x3C) into a handle.
// The handle encodes the upper 24 bits of the object's address combined with a type byte at offset 0x60.
// If the ID is out of bounds, an invalid handle is returned.

#include <cstdint>

struct ArrayDescriptor {
    uint32_t capacity;   // +0xA4
    uint8_t* base;      // +0xAC  (array of entries, each 0x61 bytes)
};

class HandleManager {
public:
    // Returns a handle for the given ID. If ID is 0xFFFFFFFF, uses default from +0x3C.
    uint32_t getHandleFromId(uint32_t id) const;

private:
    // +0x3C: default ID (fallback when param is -1)
    uint32_t defaultId;
    // +0x20: pointer to array descriptor (contains capacity and base)
    ArrayDescriptor* arrayDescriptor;
};

uint32_t HandleManager::getHandleFromId(uint32_t id) const {
    if (id == 0xFFFFFFFF) {
        id = defaultId;  // +0x3C
    }

    // Capacity stored in descriptor at +0xA4
    if (id < arrayDescriptor->capacity) {
        // Each entry is 0x61 bytes; base at descriptor's +0xAC
        uintptr_t entryAddr = reinterpret_cast<uintptr_t>(arrayDescriptor->base) + id * 0x61;

        // Type byte is at offset 0x60 within the entry
        uint8_t typeByte = *reinterpret_cast<uint8_t*>(entryAddr + 0x60);

        // Handle = (entryAddr & 0xFFFFFF00) | typeByte
        return static_cast<uint32_t>((entryAddr & 0xFFFFFF00) | typeByte);
    }

    // Out of bounds: return invalid handle (0x12222 << 8 | byte from global 0x012222C0)
    // The exact invalid value depends on a global byte; here we use a placeholder.
    return 0x12222C0u;  // CONCAT31(0x12222, DAT_012222C0)
}