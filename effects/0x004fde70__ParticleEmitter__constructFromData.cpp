// FUNC_NAME: ParticleEmitter::constructFromData
// Address: 0x004fde70
// Role: Initializes a ParticleEmitter object from a template data structure. Allocates per-particle memory, sets up constants, and registers the emitter in a global linked list.

class ParticleEmitter {
public:
    // Vtable pointer at offset 0
    void* vtable;

    // Undefined members, offsets based on usage:
    // +0x04: unknown (unaff_ESI[1])
    // +0x08: unknown (unaff_ESI[2])
    // +0x0c: unknown (unaff_ESI[3])
    // +0x10: unknown (unaff_ESI[4]) - base pointer for particle data? Used in memory copy.
    // +0x14: unknown (unaff_ESI[5])
    // +0x18: unknown (unaff_ESI[6])
    // +0x1c: unknown (unaff_ESI[7])
    // +0x20: unknown (unaff_ESI[8])
    // +0x24: next emitter in global list (unaff_ESI[9])
    // +0x28: template pointer? (unaff_ESI[10]) set from source
    // +0x2c: flags (unaff_ESI[0xb])
    // +0x30: countdown? (unaff_ESI[0xc]) 
    // +0x34: particle memory pointer (unaff_ESI[0xd])
    // +0x38: unknown (unaff_ESI[0xe])
    // +0x3c: numParticles (unaff_ESI[0xf])
    // +0x40: speedRatio (unaff_ESI[0x10]) 
    // +0x44: sizeRatio (unaff_ESI[0x11]) 
    // +0x48: invLifetime? (unaff_ESI[0x12]) 
    // +0x4c: some id (unaff_ESI[0x13]) 
    // +0x50: byte flag (unaff_ESI+0x14)

    void constructFromData(void* pSource, void* pOwner);
};

// Forward declarations of global data and functions used
extern void** DAT_01194538; // Memory allocator vtable?
extern float DAT_00e2b1a4; // Some constant (possibly 1.0f)
extern float DAT_00e44578; // Float for negative adjust (maybe 0.5f? or 0?)
extern void* PTR_FUN_00e37ae8; // vtable for ParticleEmitter

uint FUN_004e9240(); // Returns some ID (maybe texture ID)
int FUN_004e06d0(int size); // Allocates memory (returns pointer)
void FUN_004fcf10(ParticleEmitter* emitter, int param2, void* source, uint id1, int param5, int param6); // Further initialization

void ParticleEmitter::constructFromData(void* pSource, void* pOwner) {
    // pOwner is param_1, used to check a flag at +0xd
    // pSource is in_EAX, the template data
    // this is in ESI (unaff_ESI)

    // Call some base init? Ghidra shows FUN_00533cc0() but no result used
    FUN_00533cc0(); // unknown

    // Set vtable
    this->vtable = &PTR_FUN_00e37ae8;

    // Check if pOwner indicates already initialized? 
    // pOwner->byte at +0xd should be 0 to proceed
    if (*(char*)((int)pOwner + 0xd) != '\0') {
        return;
    }

    // Store source pointer at offset 0x28 (unaff_ESI[10])
    *(void**)((int)this + 0x28) = pSource;

    uint textureID = 0;
    // Check if source has non-zero data at offsets 0x30,0x34,0x38,0x3c (maybe a color or vector) and count > 0
    if ((*(int*)((int)pSource + 0x30) != 0 || *(int*)((int)pSource + 0x34) != 0 ||
         *(int*)((int)pSource + 0x38) != 0 || *(int*)((int)pSource + 0x3c) != 0) &&
        *(int*)((int)pSource + 0x28) > 0) {
        textureID = FUN_004e9240();
        if (textureID != 0 && textureID != 0xffffffff && textureID < 0x1000) {
            // Access a global table at 0x011a0f38 with stride 0x38
            int** tableEntry = *(int***)(0x011a0f38 + textureID * 0x38);
            if (tableEntry != 0) {
                (*tableEntry)++;  // Reference count?
            }
        }
        // Compute inverse lifetime from source->+0x6c
        float lifetime = *(int*)((int)pSource + 0x6c);
        if (lifetime < 0.0f) {
            lifetime += DAT_00e44578; // Adjust negative?
        }
        *(float*)((int)this + 0x48) = 1.0f / lifetime; // invLifetime
    }

    // Something with TLS (stack pointer from FS:0x2c)
    int* tlsPtr = *(int**)(*(int*)((int)__readfsdword(0x2c) + 0x2c));

    // Check source flags at +0x24 bit 1? (byte & 2)
    if ((*(char*)((int)pSource + 0x24) & 2) != 0) {
        uint* flagPtr = (uint*)(*(int*)(*tlsPtr + 8) + *(int*)((int)this + 0x10));
        *flagPtr = *flagPtr & 0xfffffffb;
    }

    // Ensure source->+0x88 >= 1 (some count)
    if (*(int*)((int)pSource + 0x88) < 1) {
        *(int*)((int)pSource + 0x88) = 1;
    }

    int baseIndex = *tlsPtr;
    *(int*)((int)this + 0x4c) = *(int*)((int)pSource + 0x2c); // some id
    *(int*)((int)this + 0x2c) = 0; // flags initially clear

    // Copy a vector4 from source at offsets 0x18,0x1c,0x20 and a float constant
    float fConst = DAT_00e2b1a4;
    // Build vector4 on stack
    struct { float x, y, z, w; } vec;
    vec.x = *(float*)((int)pSource + 0x18);
    vec.y = *(float*)((int)pSource + 0x1c);
    vec.z = *(float*)((int)pSource + 0x20);
    vec.w = fConst;

    // Copy to memory pointed by [this+0x10] + 0x40 + *(int*)(baseIndex+8)
    float* dest = (float*)(*(int*)((int)this + 0x10) + 0x40 + *(int*)(baseIndex + 8));
    dest[0] = vec.x;
    dest[1] = vec.y;
    dest[2] = vec.z;
    dest[3] = vec.w;

    *(int*)((int)this + 0x38) = 0; // unknown
    *(int*)((int)this + 0x3c) = *(int*)((int)pSource + 0x28); // numParticles
    *(char*)((int)this + 0x50) = 0; // flag

    // Check if source has zero vector at 0x30-0x3c or count < 1
    if ((*(int*)((int)pSource + 0x30) == 0 && *(int*)((int)pSource + 0x34) == 0 &&
         *(int*)((int)pSource + 0x38) == 0 && *(int*)((int)pSource + 0x3c) == 0) ||
        *(int*)((int)pSource + 0x28) < 1) {
        // No particles: set flag bit 0 and clear particle memory pointer, set some other flag
        *(int*)((int)this + 0x2c) |= 1; // flag bit 0
        *(int*)((int)this + 0x34) = 0; // no particle memory
        uint* flag2 = (uint*)(*(int*)((int)this + 0x10) + *(int*)(baseIndex + 8));
        *flag2 = *flag2 | 0x20000000;
    } else {
        // Setup for particles
        *(int*)((int)this + 0x30) = 0; // some counter
        // speedRatio = 1.0 / (source->+0x94) * fVar3? Actually: fVar3 / *(float*)(pSource+0x94)
        float fVar3 = DAT_00e2b1a4;
        *(float*)((int)this + 0x40) = fVar3 / *(float*)((int)pSource + 0x94);
        // sizeRatio = source->+0x84 / source->+0x98
        *(float*)((int)this + 0x44) = *(float*)((int)pSource + 0x84) / *(float*)((int)pSource + 0x98);
        // Compute invLifetime again (duplicate code)
        float lifetime2 = *(int*)((int)pSource + 0x6c);
        if (lifetime2 < 0.0f) {
            lifetime2 += DAT_00e44578;
        }
        *(float*)((int)this + 0x48) = 1.0f / lifetime2;

        int particleSize = *(int*)((int)this + 0x3c) * 0x90; // each particle is 144 bytes
        int* particleMem = (int*)FUN_004e06d0(particleSize);
        *(int*)((int)this + 0x34) = (int)particleMem;

        if (particleMem == 0) {
            // Allocation failed: set pOwner->byte at +0xc to 1
            *(char*)((int)pOwner + 0xc) = 1;
            return;
        }

        bool allocFailed = false;
        int particleIndex = 0;
        int offset = 0;
        if (*(int*)((int)this + 0x3c) > 0) {
            do {
                // Allocate per-particle data block: each particle needs (source->+0x88 + 1) * 0x10 bytes
                int allocSize = (*(int*)((int)pSource + 0x88) + 1) * 0x10;
                int* particleData = (int*)(**(int (__cdecl**)(int, void*))DAT_01194538)(allocSize, &particleIndex); // custom allocator? Actually call via vtable
                // particleIndex local variable is reused for alloc parameters
                // It seems the call is: function pointer at *DAT_01194538 (vtable)
                // with two arguments: allocSize and &local_20 (which is set to 2 initially)
                // Ghidra shows: local_20 = 2; uStack_1c = 0x10; uStack_18 = 0; iVar7 = call(*DAT_01194538, ...)
                // We'll approximate.
                *(int*)((int)particleMem + offset + 0x60) = (int)particleData; // store pointer at particle+0x60

                if (particleData == 0) {
                    allocFailed = true;
                }
                offset += 0x90;
                particleIndex++;
            } while (particleIndex < *(int*)((int)this + 0x3c));

            if (allocFailed) {
                // Free previously allocated per-particle data
                int i = 0;
                int off = 0;
                do {
                    if (*(int*)((int)particleMem + off + 0x60) == 0) {
                        // Call deallocator
                        (**(void (__cdecl**)(int, int))(*DAT_01194538 + 4))(0, 0);
                        *(int*)((int)particleMem + off + 0x60) = 0;
                    }
                    i++;
                    off += 0x90;
                } while (i < *(int*)((int)this + 0x3c));
                // Free the main particle memory
                (**(void (__cdecl**)(int, int))(*DAT_01194538 + 4))(particleMem, 0);
                *(int*)((int)this + 0x34) = 0;
                *(char*)((int)pOwner + 0xc) = 1;
                return;
            }
        }

        // Initialize per-particle data
        int i2 = 0;
        int off2 = 0;
        if (*(int*)((int)this + 0x3c) > 0) {
            do {
                int particleBase = (int)particleMem + off2;
                *(int*)(particleBase + 0x64) = *(int*)((int)pSource + 0x88) + 1; // +0x64 = some count
                *(int*)(particleBase + 0x68) = 0; // +0x68
                *(int*)(particleBase + 0x78) = 1; // +0x78
                *(int*)(particleBase + 0x7c) = 0; // +0x7c
                *(int*)(particleBase + 0x84) = 0; // +0x84
                *(int*)(particleBase + 0x80) = 0; // +0x80
                i2++;
                off2 += 0x90;
            } while (i2 < *(int*)((int)this + 0x3c));
        }
    }

    // Link this emitter into global list
    *(int*)((int)this + 0x24) = (int)DAT_01194a90; // previous head
    DAT_01194a90 = this; // new head

    // Call further initialization
    FUN_004fcf10(this, *(int*)(*(int*)((int)this + 4) + 0x10), pSource, textureID, *(int*)((int)this + 0x10), *(int*)((int)this + 0x14));

    // Set flag at +0x50 to 1 (initialized)
    *(char*)((int)this + 0x50) = 1;
}