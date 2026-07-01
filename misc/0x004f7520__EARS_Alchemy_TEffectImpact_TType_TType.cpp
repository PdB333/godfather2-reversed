// Xbox PDB: EARS::Alchemy::TEffectImpact::TType::TType
// FUNC_NAME: Global::initImpactResource

struct ImpactResource {
    void* vtable;                    // +0x00
    const char* name;                // +0x04
    uint32_t fourCC;                 // +0x08
    uint32_t field_0c;               // +0x0c
    uint32_t field_10;               // +0x10
    uint32_t field_14;               // +0x14
    uint32_t bufferSize;             // +0x18
    uint32_t field_1c;               // +0x1c
    uint32_t field_20;               // +0x20
};

extern void* PTR_LAB_00e378f8;       // vtable for Impact resource

static ImpactResource g_impactResource;

ImpactResource* initImpactResource(void)
{
    g_impactResource.vtable = &PTR_LAB_00e378f8;  // +0x00: assign vtable pointer
    g_impactResource.name = "Impact";              // +0x04: resource name string
    g_impactResource.fourCC = 0x2e696d70;          // +0x08: FourCC (likely ".imp" – stored as little‑endian bytes 70,6d,69,2e)
    g_impactResource.field_0c = 0;                 // +0x0c: (offset 0x0c) clear
    g_impactResource.field_10 = 0xd;               // +0x10: size/type field (13)
    g_impactResource.field_14 = 0;                 // +0x14: clear
    g_impactResource.bufferSize = 0x800;           // +0x18: buffer size (2048)
    g_impactResource.field_1c = 0;                 // +0x1c: clear
    g_impactResource.field_20 = 0;                 // +0x20: clear
    return &g_impactResource;
}