// FUNC_NAME: ParticleSystem::ParticleSystem

// Address: 0x005097d0
// This is the constructor for a static global ParticleSystem descriptor instance.
// It initializes the vtable, name, extension, version, and flags for the default particle system type.

class ParticleSystem {
public:
    // +0x00: pointer to vtable (likely _DAT_012191b4)
    int* vtable;
    // +0x04: pointer to name string "ParticleSystem"
    const char* name;
    // +0x08: file extension (0x2e707274 = ".prt" in little-endian)
    int extension;
    // +0x0C: unknown1 (0)
    int unknown1;
    // +0x10: version? (0x1d = 29)
    int version;
    // +0x14: unknown2 (0)
    int unknown2;
    // +0x18: flags (0x800)
    int flags;
    // +0x1C: unknown3 (0)
    int unknown3;
    // +0x20: unknown4 (0)
    int unknown4;
    // +0x24: unknown5 (0)
    int unknown5;

    // Constructor
    ParticleSystem() {
        vtable = reinterpret_cast<int*>(0x00e38140); // &PTR_LAB_00e38140
        name = "ParticleSystem";
        extension = 0x2e707274; // ".prt"
        unknown1 = 0;
        version = 0x1d;         // 29
        unknown2 = 0;
        flags = 0x800;
        unknown3 = 0;
        unknown4 = 0;
        unknown5 = 0;
    }
};

// Static global instance
static ParticleSystem gParticleSystemDefault; // corresponds to DAT_012191b4

// Note: The function returns a pointer to the static object (gParticleSystemDefault).