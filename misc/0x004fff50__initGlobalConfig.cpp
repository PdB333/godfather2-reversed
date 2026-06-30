// FUNC_NAME: initGlobalConfig
// Function address: 0x004fff50
// Role: Initializes a static global configuration structure (likely for streaming or resource management)
// The structure seems to contain a vtable pointer, a data pointer, a magic "ule." identifier,
// fields zeroed out, a version/count of 2, and a buffer size of 0x800 (2048 bytes).
// Returns a pointer to the static instance.

#include <cstdint>

// Structure definition (size 40 bytes, offsets relative to gConfigBase)
struct StaticConfig {
    void*   vtablePtr;   // +0x00 (points to PTR_LAB_00e37c38)
    void*   dataPtr;     // +0x04 (points to DAT_00e37bec)
    uint32_t magic;      // +0x08 (0x2e656c75 = "ule." in ASCII, little-endian)
    uint32_t zero1;      // +0x0C (0)
    uint32_t version;    // +0x10 (2)
    uint32_t zero2;      // +0x14 (0)
    uint32_t bufferSize; // +0x18 (0x800)
    uint32_t zero3;      // +0x1C (0)
    uint32_t zero4;      // +0x20 (0)
    uint32_t zero5;      // +0x24 (0)
};

// Global instance at absolute address 0x012190d8 (from Ghidra exports)
// Declared as extern to match the actual memory layout
extern StaticConfig gConfigInstance; // at 0x012190d8

// Function prototype
void* initGlobalConfig(void);

// Function implementation
void* initGlobalConfig(void) {
    gConfigInstance.vtablePtr   = (void*)&PTR_LAB_00e37c38; // from Ghidra label
    gConfigInstance.dataPtr     = (void*)&DAT_00e37bec;     // from Ghidra label
    gConfigInstance.magic       = 0x2e656c75;               // "ule." identifier
    gConfigInstance.zero1       = 0;
    gConfigInstance.version     = 2;
    gConfigInstance.zero2       = 0;
    gConfigInstance.bufferSize  = 0x800;
    gConfigInstance.zero3       = 0;
    gConfigInstance.zero4       = 0;
    gConfigInstance.zero5       = 0;

    return &gConfigInstance;
}