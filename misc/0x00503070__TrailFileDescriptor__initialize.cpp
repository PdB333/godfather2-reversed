// FUNC_NAME: TrailFileDescriptor::initialize
// Description: Initializes a static Trail file descriptor singleton for .trl files.
// Address: 0x00503070
// Structure: TrailFileDescriptor (size 0x28)
//   +0x00: vtable pointer (to PTR_LAB_00e37e60)
//   +0x04: name string ("Trail")
//   +0x08: extension integer (".trl" as 0x2e74726c)
//   +0x0C: unknown (0)
//   +0x10: size (6)
//   +0x14: unknown (0)
//   +0x18: maxSize (0x800 = 2048)
//   +0x1C: unknown (0)
//   +0x20: unknown (0)
//   +0x24: unknown (0)

struct TrailFileDescriptor {
    void** vtable;          // +0x00
    const char* name;       // +0x04
    uint32_t extension;     // +0x08
    int32_t unknown1;       // +0x0C
    int32_t size;           // +0x10
    int32_t unknown2;       // +0x14
    int32_t maxSize;        // +0x18
    int32_t unknown3;       // +0x1C
    int32_t unknown4;       // +0x20
    int32_t unknown5;       // +0x24
};

// Global instance at 0x01219130 (presumed to be defined in .data section)
extern TrailFileDescriptor g_trailFileDescriptor;

// Note: PTR_LAB_00e37e60 is an external vtable for TrailFileDescriptor.
extern void* PTR_LAB_00e37e60[];

// Constructor-like initializer
void TrailFileDescriptor::initialize(void) {
    g_trailFileDescriptor.vtable = (void**)&PTR_LAB_00e37e60;
    g_trailFileDescriptor.name = "Trail";
    g_trailFileDescriptor.extension = 0x2e74726c; // ".trl"
    g_trailFileDescriptor.unknown1 = 0;
    g_trailFileDescriptor.size = 6;
    g_trailFileDescriptor.unknown2 = 0;
    g_trailFileDescriptor.maxSize = 0x800;
    g_trailFileDescriptor.unknown3 = 0;
    g_trailFileDescriptor.unknown4 = 0;
    g_trailFileDescriptor.unknown5 = 0;
    return; // Original returns &g_trailFileDescriptor, but as void*; here we just initialize
}