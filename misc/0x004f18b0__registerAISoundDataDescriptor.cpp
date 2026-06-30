// FUNC_NAME: registerAISoundDataDescriptor
// Address: 0x004f18b0
// Role: Initializes the static data descriptor for AI sound assets (".ais" extension).
// Returns pointer to the descriptor structure.

struct AISoundDataDesc {
    void** vtable;       // +0x00: Vtable pointer (typically for DataDescBase)
    const char* name;    // +0x04: Type name ("AISound")
    int extensionMagic;  // +0x08: ".ais" as little-endian int
    int versionMajor;    // +0x0C: Major version (1)
    int versionMinor;    // +0x10: Minor version (2)
    int reserved1;       // +0x14: 0
    int flags;           // +0x18: 0x800 (e.g., kIsSoundAsset)
    int reserved2;       // +0x1C: 0
    int reserved3;       // +0x20: 0
    int reserved4;       // +0x24: 0
};

// Global descriptor instance
static AISoundDataDesc gAISoundDataDesc;

// External vtable for the descriptor (defined elsewhere)
extern void* PTR_LAB_00e37518[];

AISoundDataDesc* registerAISoundDataDescriptor() {
    // Zero most fields first
    gAISoundDataDesc.reserved1 = 0;
    gAISoundDataDesc.reserved2 = 0;
    gAISoundDataDesc.reserved3 = 0;
    gAISoundDataDesc.reserved4 = 0;

    // Set identifying metadata
    gAISoundDataDesc.name = "AISound";
    gAISoundDataDesc.extensionMagic = 0x2E616973; // ".ais" in little-endian
    gAISoundDataDesc.versionMajor = 1;
    gAISoundDataDesc.versionMinor = 2;
    gAISoundDataDesc.flags = 0x800; // Audio/Sound flag

    // Wire up the vtable
    gAISoundDataDesc.vtable = PTR_LAB_00e37518;

    // Return the static descriptor pointer
    return &gAISoundDataDesc;
}