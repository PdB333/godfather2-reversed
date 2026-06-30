// FUNC_NAME: getDistortionProcDescription

// Address: 0x004f3d50
// Initializes a static distortion effect description structure and returns a pointer to it.
// The structure likely corresponds to a shader or post-process effect named "DistortionProc".
// Fields: vtable pointer, string name, file extension, and effect parameters (width, flags, etc.)

struct DistortionProcDescription {
    void** vtable;          // +0x00: pointer to virtual function table (PTR_LAB_00e37758)
    const char* name;       // +0x04: "DistortionProc"
    const char* extension;  // +0x08: ".dtp" (stored as little-endian 0x2e647470)
    int32_t unk0C;          // +0x0C: 0
    int32_t flags;          // +0x10: 1
    int32_t unk14;          // +0x14: 0
    int32_t width;          // +0x18: 0x800 (2048)
    int32_t unk1C;          // +0x1C: 0
    int32_t unk20;          // +0x20: 0
    int32_t unk24;          // +0x24: 0
};

// Global static instance (stored at 0x01218f88)
static DistortionProcDescription distortionProcDescription;

DistortionProcDescription* getDistortionProcDescription(void) {
    // Initialize static fields
    distortionProcDescription.vtable = &PTR_LAB_00e37758;
    distortionProcDescription.name = "DistortionProc";
    distortionProcDescription.extension = ".dtp"; // reinterpreted as little-endian: 0x70,0x74,0x64,0x2e = "ptd." but string is ".dtp"
    distortionProcDescription.unk0C = 0;
    distortionProcDescription.flags = 1;
    distortionProcDescription.unk14 = 0;
    distortionProcDescription.width = 0x800;
    distortionProcDescription.unk1C = 0;
    distortionProcDescription.unk20 = 0;
    distortionProcDescription.unk24 = 0;
    return &distortionProcDescription;
}