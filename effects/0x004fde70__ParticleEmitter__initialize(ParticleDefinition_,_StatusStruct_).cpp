// FUNC_NAME: ParticleEmitter::initialize(ParticleDefinition*, StatusStruct*)
// Function address: 0x004fde70
// Reconstructed C++ for ParticleEmitter initialization.
// Parses a particle definition and allocates per-particle data, registers into global list.

#include <cstdint>

// Forward declarations
struct ParticleDefinition;
struct StatusStruct;

class ParticleEmitter
{
public:
    // Vtable pointer at offset 0
    void* vtable;

    // Fields (offsets in bytes)
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: unknown
    // +0x10: pointer to some internal buffer (e.g., vertex/position buffer)
    void* m_buffer;          // +0x10
    // +0x14: another buffer pointer
    void* m_buffer2;         // +0x14
    // +0x18..0x20: unknown (maybe transform?)
    // +0x24: next pointer in global linked list (m_next)
    ParticleEmitter* m_next; // +0x24
    // +0x28: stored pointer to the particle definition
    const ParticleDefinition* m_pDefinition; // +0x28
    // +0x2C: flags (bit0 = active? see code: m_flags |= 1)
    uint32_t m_flags;        // +0x2C
    // +0x30: some internal count or index
    int32_t m_internalCounter; // +0x30
    // +0x34: pointer to allocated particle data block
    // Each particle is 0x90 bytes.
    void* m_pParticles;      // +0x34
    // +0x38: unknown
    int32_t m_unknown38;     // +0x38
    // +0x3C: number of particles to emit (from definition)
    int32_t m_particleCount; // +0x3C
    // +0x40: computed scale factor (1.0 / life)
    float m_invLifeScale;    // +0x40
    // +0x44: another computed factor (velocity / scale2)
    float m_velocityFactor;  // +0x44
    // +0x48: 1.0 / life (float)
    float m_invLife;         // +0x48
    // +0x4C: copy of definition->m_someInt (offset 0x2C)
    int32_t m_definitionParam; // +0x4C
    // +0x50: flag indicating initialization is complete (0 or 1)
    uint8_t m_initializedFlag; // +0x50
};

// External globals
extern float DAT_00e44578;        // constant (e.g., 2^something)
extern float DAT_00e2b1a4;        // constant (e.g., 0.0f)
extern void* PTR_FUN_00e37ae8;    // vtable for ParticleEmitter
extern struct AllocatorVtable* DAT_01194538; // allocator vtable (function[0] = allocate, [4] = free)
extern ParticleEmitter* DAT_01194a90; // head of global linked list

// External functions
extern void criticalSectionEnter(); // FUN_00533cc0, presumably lock
extern uint32_t getSomeID();        // FUN_004e9240, returns texture/effect ID
extern void* allocateMemory(int size); // FUN_004e06d0, heap allocation
extern void finalizeInit(ParticleEmitter* self, void* buffer, const ParticleDefinition* def, uint32_t id, void* buf1, void* buf2); // FUN_004fcf10

struct ParticleDefinition
{
    // Offsets (bytes from this pointer)
    // +0x00..0x14: unknown (maybe header)
    // +0x18: position x
    float posX;          // +0x18
    // +0x1C: position y
    float posY;          // +0x1C
    // +0x20: position z
    float posZ;          // +0x20
    // +0x24: flags byte (bit1 checked)
    uint8_t flags;       // +0x24
    // +0x28: number of particles to emit
    int32_t particleCount; // +0x28
    // +0x2C: some integer parameter (e.g., type or identifier)
    int32_t someInt;     // +0x2C
    // +0x30..0x3C: min/max or offset vector (float4)
    float minX;          // +0x30
    float minY;          // +0x34
    float minZ;          // +0x38
    float minW;          // +0x3C (usually 0 or 1)
    // +0x6C: lifetime in ticks? (int)
    int32_t life;        // +0x6C
    // +0x84: velocity (float)
    float velocity;      // +0x84
    // +0x88: particle size or alloc size multiplier (int)
    int32_t sizeMultiplier; // +0x88
    // +0x94: scale factor 1
    float scale1;        // +0x94
    // +0x98: scale factor 2
    float scale2;        // +0x98
};

struct StatusStruct
{
    // +0x0C: indicates if allocation failed (set to 1 on failure)
    uint8_t allocFailed; // +0x0C
    // +0x0D: indicates if already initialized (checked, not set)
    uint8_t initialized; // +0x0D
};

void ParticleEmitter::initialize(ParticleDefinition* def, StatusStruct* status)
{
    // this is in ESI
    criticalSectionEnter();

    // Set vtable
    this->vtable = &PTR_FUN_00e37ae8;

    // Check if already initialized (status->initialized == 0 means proceed)
    if (status->initialized != 0)
        return;

    // Store definition pointer
    this->m_pDefinition = def;

    uint32_t effectID = 0;

    // Check if definition has non-zero min/max vector and a positive count
    if ((def->minX != 0.0f || def->minY != 0.0f || def->minZ != 0.0f || def->minW != 0.0f) &&
        (def->particleCount > 0))
    {
        // Get an effect ID (e.g., texture index)
        effectID = getSomeID();
        if (effectID != 0 && effectID != 0xFFFFFFFF &&
            effectID < 0x1000 &&
            (/* some check on a global array */ /* omitted for brevity */))
        {
            // Increment reference count in some global array
            // Array DAT_011a0f38 indexed by effectID * 0x38
            // Reference: int* ptr = (int*)(&DAT_011a0f38 + effectID * 0x38);
            // *ptr = *ptr + 1;
        }

        float invLife = (float)def->life;
        if (def->life < 0)
            invLife += DAT_00e44578; // handle negative by adding constant

        this->m_invLife = 1.0f / invLife;
    }

    // Get thread-local storage pointer (FS segment)
    int* tlsBase = *(int**)(__readfsdword(0x2C)); // FS:[0x2C] points to TIB

    // Check if definition has flag 0x02 set, clear bit 2 in some buffer
    if ((def->flags & 0x02) != 0)
    {
        uint32_t* bufferFlags = (uint32_t*)(*(int*)(*tlsBase + 8) + (intptr_t)this->m_buffer);
        *bufferFlags &= ~0x04; // Clear bit 2 (0x04)
    }

    // Ensure sizeMultiplier is at least 1
    if (def->sizeMultiplier < 1)
        def->sizeMultiplier = 1;

    // Copy some fields from def
    this->m_definitionParam = def->someInt;
    this->m_flags = 0;

    // Copy position
    float pos[4] = { def->posX, def->posY, def->posZ, DAT_00e2b1a4 };
    // Write into some buffer at offset m_buffer + 0x40 + (tlsBase[2] offset)
    int offset = (intptr_t)this->m_buffer + 0x40 + *(int*)(*tlsBase + 8);
    float* dest = (float*)(offset);
    dest[0] = pos[0];
    dest[1] = pos[1];
    dest[2] = pos[2];
    dest[3] = pos[3];

    this->m_unknown38 = 0;
    this->m_particleCount = def->particleCount;
    this->m_initializedFlag = 0;

    // Check if definition has all min/max zero or count < 1
    if ((def->minX == 0.0f && def->minY == 0.0f && def->minZ == 0.0f && def->minW == 0.0f) ||
        (def->particleCount < 1))
    {
        // Set flag bit 0 (no particles)
        this->m_flags |= 1;
        this->m_internalCounter = 0;
        // Set bit 29 in a different buffer
        uint32_t* bufFlags = (uint32_t*)((intptr_t)this->m_buffer + *(int*)(*tlsBase + 8));
        *bufFlags |= 0x20000000;
    }
    else
    {
        // Initialize particle data
        this->m_internalCounter = 0;
        this->m_invLifeScale = DAT_00e2b1a4 / def->scale1; // Actually fVar3 / def->scale1, fVar3 is DAT_00e2b1a4
        this->m_velocityFactor = def->velocity / def->scale2;

        float lifeInv = (float)def->life;
        if (def->life < 0)
            lifeInv += DAT_00e44578;
        this->m_invLife = 1.0f / lifeInv;

        // Allocate memory for particles: each particle is 0x90 bytes
        int totalSize = this->m_particleCount * 0x90;
        this->m_pParticles = allocateMemory(totalSize);
        if (this->m_pParticles == nullptr)
        {
            status->allocFailed = 1;
            return;
        }

        bool allocFailed = false;
        int particleIndex = 0;
        // For each particle, allocate per-particle data
        for (int i = 0; i < this->m_particleCount; i++)
        {
            int allocSize = (def->sizeMultiplier + 1) * 0x10;
            int allocType = 2; // some type
            int allocSubType = 0x10;
            int extra = 0;
            // Use allocator vtable: first function at offset 0
            void* particleData = ((AllocatorVtable*)DAT_01194538)->allocate(allocSize, &allocType);
            // Store pointer at offset 0x60 within each particle block
            void** particleSlot = (void**)((intptr_t)this->m_pParticles + particleIndex * 0x90 + 0x60);
            *particleSlot = particleData;
            if (particleData == nullptr)
                allocFailed = true;
            particleIndex++;
        }

        if (allocFailed)
        {
            // Free any successfully allocated particles
            for (int i = 0; i < this->m_particleCount; i++)
            {
                void* data = *(void**)((intptr_t)this->m_pParticles + i * 0x90 + 0x60);
                if (data != nullptr)
                {
                    ((AllocatorVtable*)DAT_01194538)->free(data, 0);
                    *(int*)((intptr_t)this->m_pParticles + i * 0x90 + 0x60) = 0;
                }
            }
            // Free the particle block itself
            ((AllocatorVtable*)DAT_01194538)->free(this->m_pParticles, 0);
            this->m_pParticles = nullptr;
            status->allocFailed = 1;
            return;
        }

        // Initialize each particle's header fields
        for (int i = 0; i < this->m_particleCount; i++)
        {
            int slotBase = (intptr_t)this->m_pParticles + i * 0x90;
            *(int*)(slotBase + 0x64) = def->sizeMultiplier + 1; // offset 0x64 (100 decimal? actually 0x64 = 100)
            *(int*)(slotBase + 0x68) = 0;   // some field
            *(int*)(slotBase + 0x78) = 1;   // active flag?
            *(int*)(slotBase + 0x7C) = 0;   //
            *(int*)(slotBase + 0x84) = 0;   //
            *(int*)(slotBase + 0x80) = 0;   //
        }
    }

    // Register this emitter in global linked list
    this->m_next = DAT_01194a90;
    DAT_01194a90 = this;

    // Final initialization call
    finalizeInit(this, *(void**)((intptr_t)this->m_buffer2 + 0x10), def, effectID, this->m_buffer, this->m_buffer2);

    this->m_initializedFlag = 1;
}