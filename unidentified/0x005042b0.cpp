// FUN_005042b0: getFlareAssetDescriptor

// Represents the static descriptor for the "Flare" asset type (particle effect file .flr)
struct FlareAssetDescriptor {
    void* unknownPtr;          // +0x00 -> points to external structure (PTR_LAB_00e38028)
    const char* name;          // +0x04 -> "Flare"
    uint32_t extension;        // +0x08 -> packed extension ".flr" (0x2e666c72)
    int32_t type;              // +0x0C -> 1
    int32_t version;           // +0x10 -> 3
    int32_t field_0x14;        // +0x14 -> unused ?
    int32_t size;              // +0x18 -> 0x800 (2048)
    int32_t reserved[3];       // +0x1C, +0x20, +0x24 -> zeros
};

// Returns a pointer to the static Flare asset descriptor, initializing it on first call.
FlareAssetDescriptor* getFlareAssetDescriptor() {
    static FlareAssetDescriptor desc = {
        /* unknownPtr = */ reinterpret_cast<void*>(0x00e38028), // PTR_LAB_00e38028
        /* name       = */ "Flare",
        /* extension  = */ 0x2e666c72,
        /* type       = */ 1,
        /* version    = */ 3,
        /* field_0x14 = */ 0,
        /* size       = */ 0x800,
        /* reserved   = */ {0, 0, 0}
    };
    return &desc;
}