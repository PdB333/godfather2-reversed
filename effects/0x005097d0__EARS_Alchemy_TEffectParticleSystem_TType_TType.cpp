// Xbox PDB: EARS::Alchemy::TEffectParticleSystem::TType::TType
// FUNC_NAME: ParticleSystem::getStaticDescriptor

struct ParticleSystemDescriptor {
    void* vtable;           // +0x00
    const char* name;       // +0x04
    uint32_t extension;     // +0x08 (".prt" as little-endian)
    uint32_t field_0C;      // +0x0C
    uint32_t field_10;      // +0x10 (0x1d)
    uint32_t field_14;      // +0x14
    uint32_t field_18;      // +0x18 (0x800)
    uint32_t field_1C;      // +0x1C
    uint32_t field_20;      // +0x20
    uint32_t field_24;      // +0x24
};

static ParticleSystemDescriptor particleSystemDescriptor;

ParticleSystemDescriptor* ParticleSystem::getStaticDescriptor() {
    particleSystemDescriptor.field_0C = 0;
    particleSystemDescriptor.field_14 = 0;
    particleSystemDescriptor.field_1C = 0;
    particleSystemDescriptor.field_20 = 0;
    particleSystemDescriptor.field_24 = 0;
    particleSystemDescriptor.name = "ParticleSystem";
    particleSystemDescriptor.extension = 0x2e707274; // ".prt"
    particleSystemDescriptor.field_10 = 0x1d;
    particleSystemDescriptor.field_18 = 0x800;
    particleSystemDescriptor.vtable = &PTR_LAB_00e38140;
    return &particleSystemDescriptor;
}