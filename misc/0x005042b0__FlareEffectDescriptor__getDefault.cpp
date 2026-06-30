// FUNC_NAME: FlareEffectDescriptor::getDefault

// Struct describing a flare particle effect (file extension .flr)
// Likely from EARS::Modules::VFX subsystem
struct FlareEffectDescriptor {
    void*   pVtable;           // +0x00: pointer to vtable or manager (PTR_LAB_00e38028)
    char*   name;              // +0x04: effect name string ("Flare")
    char    extension[4];      // +0x08: file extension packed as uint32 (".flr" = 0x2e666c72)
    int32_t field_0C;          // +0x0C: unknown (1)
    int32_t field_10;          // +0x10: unknown (3)
    int32_t zero_14;           // +0x14: zeroed
    int32_t flags;             // +0x18: flags (0x800)
    int32_t zero_1C;           // +0x1C: zeroed
    int32_t zero_20;           // +0x20: zeroed
    int32_t zero_24;           // +0x24: zeroed
};

// Static data for the default flare descriptor
static FlareEffectDescriptor sFlareEffectDescriptor;

// Returns pointer to the static default FlareEffectDescriptor
// Initializes it on first call (simulated by compiler-initiated CRT)
FlareEffectDescriptor* FlareEffectDescriptor::getDefault()
{
    // These assignments would be part of static initialization
    sFlareEffectDescriptor.pVtable = (void*)&PTR_LAB_00e38028; // +0x00
    sFlareEffectDescriptor.name    = "Flare";                  // +0x04
    *(uint32_t*)&sFlareEffectDescriptor.extension = 0x2e666c72; // +0x08 ".flr"
    sFlareEffectDescriptor.field_0C = 1;                       // +0x0C
    sFlareEffectDescriptor.field_10 = 3;                       // +0x10
    sFlareEffectDescriptor.zero_14  = 0;                       // +0x14 (explicit zero)
    sFlareEffectDescriptor.flags    = 0x800;                   // +0x18
    sFlareEffectDescriptor.zero_1C  = 0;                       // +0x1C
    sFlareEffectDescriptor.zero_20  = 0;                       // +0x20
    sFlareEffectDescriptor.zero_24  = 0;                       // +0x24

    return &sFlareEffectDescriptor;
}