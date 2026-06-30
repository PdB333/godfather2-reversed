// FUNC_NAME: ParticleEmitter::constructor (or Emitter::init?)
// Address: 0x004887f0
// This function appears to be a constructor for a particle/emitter object that registers itself in a global list (max 32 entries).
// It takes a parent object (param_2) and initializes various fields (velocity, position, color, etc.)
// The global DAT_01222330 is an array of 12-byte entries; first 8 bytes at DAT_01222328, last 4 at DAT_01222330.
// The check with 0x80 may indicate a maximum particle "age" or "power" threshold.

class ParticleEmitter {
public:
    // vtable pointer at offset 0
    // parent node (some scene object) at offset 4 (param_2)
    void** vtable;
    void* parent;

    // raw data fields (offsets in bytes)
    // +0x08: unknown (param_1[2])
    // +0x0C: unknown (param_1[3])
    // +0x10: unknown (param_1[4])
    // +0x14: some handle/buffer (param_1[5] returned from FUN_004265d0)
    // +0x18: copy of parent (param_1[6])
    // +0x1C: unknown (param_1[7])
    // +0x20: unknown (param_1[8])
    // +0x28?: actually indexing is ambiguous, but from pattern:
    // param_1[0xa] = param_1[10] at +0x28
    // param_1[0xb] at +0x2C
    // param_1[0xc] at +0x30
    // param_1[0xd] at +0x34 (some float)
    // param_1[0xe] at +0x38 (some float)
    // param_1[0xf] at +0x3C
    // param_1[0x10] at +0x40
    // param_1[0x11] at +0x44 (from fVar5)
    // param_1[0x12] at +0x48 (from fVar5)
    // param_1[0x13] at +0x4C
    // +0x50: short (param_1[0x14])
    // +0x52: short (explicitly)
    // +0x54: param_1[0x15] = 0
    // +0x58: byte set to 1

    void unknownMethod(); // from parent's vtable+8

    // Called twice in constructor
};

// Global data (inferred from decompiled access)
extern ParticleEmitter* g_latestEmitter; // DAT_012234a0
extern float g_someConstant1; // DAT_00e2b1a4
extern float g_someConstant2; // DAT_00e2cd54
extern int g_divisor1; // DAT_01205898
extern int g_divisor2; // DAT_0120588c
extern void* g_particleListBase; // DAT_01222328 (start of 8-byte field)
extern void* g_particleListSecond; // DAT_01222330 (start of 4-byte field, offset +8)
extern int g_particleCount; // DAT_012224a8 (number of registered emitters, max 32)

// External functions
extern int FUN_004265d0(void* unknown, void* parent); // Returns some handle
extern void FUN_0048e040(int param); // Possibly allocation/reset
extern void FUN_00609bf0(); // Error handler

ParticleEmitter* __thiscall ParticleEmitter::constructor(ParticleEmitter* this, void* parent)
{
    int i;
    float fVar5;
    
    g_latestEmitter = this;
    this->vtable = &PTR_FUN_00e3380c; // class vtable
    this->parent = parent;
    
    // Call to setup some resource (maybe allocate particle buffer)
    {
        // local variables for function call
        void* local_c = 0;
        void* local_8 = 0;
        int local_4 = 0;
        // Note: local_c and local_8 are used as out params? The function returns a handle
        int handle = FUN_004265d0(&local_c, parent);
        // Store handle and parent copy
        *((int*)this + 5) = handle;        // offset +0x14
        *((int*)this + 6) = (int)parent;   // offset +0x18
    }
    
    // Call a method on parent (maybe initialize something)
    (*(void (**)(void))(*((int*)parent) + 8))();
    
    // Load initial values from globals
    float someFloat1 = g_someConstant1;   // DAT_00e2b1a4
    float someFloat2 = g_someConstant2;   // DAT_00e2cd54
    
    // Initialize many fields to zero/some values
    *((int*)this + 2) = 0;  // offset +0x08
    *((int*)this + 4) = 0;  // offset +0x10
    *((int*)this + 3) = 0;  // offset +0x0C
    *((int*)this + 7) = 0;  // offset +0x1C
    *((int*)this + 8) = 0;  // offset +0x20
    *((int*)this + 10) = 0; // offset +0x28
    *((int*)this + 11) = 0; // offset +0x2C
    *((int*)this + 12) = 0; // offset +0x30
    *((float*)this + 13) = someFloat1; // offset +0x34
    *((float*)this + 14) = someFloat2; // offset +0x38
    *((int*)this + 15) = 0; // offset +0x3C
    *((int*)this + 16) = 0; // offset +0x40
    *((float*)this + 17) = someFloat1; // offset +0x44
    *((float*)this + 18) = someFloat1; // offset +0x48
    *((int*)this + 19) = 0; // offset +0x4C
    
    // Write shorts
    *(short*)((char*)this + 0x50) = 0;  // offset +0x50
    *(short*)((char*)this + 0x52) = 0;  // offset +0x52
    
    *((int*)this + 21) = 0; // offset +0x54
    *(char*)((char*)this + 0x58) = 1; // offset +0x58 (byte)
    
    // Call method on parent again (same vtable offset)
    (*(void (**)(void))(*((int*)parent) + 8))();
    
    // Compute scaling factors from global constants
    float scaleX = g_someConstant1 / (float)g_divisor1; // DAT_00e2b1a4 / DAT_01205898
    float scaleY = g_someConstant1 / (float)g_divisor2; // DAT_00e2b1a4 / DAT_0120588c
    *((float*)this + 10) = scaleY; // offset +0x28? Actually careful: param_1[10] was set before, but now overwritten?
    // The decompiled code sets param_1[10] to this division, then param_1[0xb] to fVar5 (which is scaleX)
    // But earlier param_1[10] and [0xb] were set to 0. So this overwrites them.
    // param_1[10] is at offset +0x28, param_1[0xb] at +0x2C
    *((float*)this + 10) = scaleY;
    *((float*)this + 11) = scaleX;
    
    // Call another function (maybe initialize timer or something)
    FUN_0048e040(0x40);
    
    // Check global list for any existing entry with first byte > 0x80
    // The list entries are 12 bytes each; first byte is at address of each entry
    // The list base for the first 8-byte field is DAT_01222328, but the loop uses DAT_01222330? Actually the check uses pbVar3 = &DAT_01222330 and increments by 0xc each iteration.
    // So the loop iterates over the array of 12-byte entries starting at DAT_01222330 (which is the second field of the first entry? Might be confusion).
    // We'll treat the array as starting at DAT_01222328 with 12-byte stride, but the pointer used is to the second field? The code: pbVar3 = &DAT_01222330; do { if (0x80 < *pbVar3) ... } while (uVar4 < DAT_012224a8);
    // So pbVar3 points to the 4-byte field (offset +8 within each entry), and it checks the first byte of that 4-byte field? Actually *pbVar3 dereferences as byte, so it checks the first byte of that field.
    // So the condition is: if the first byte of the second field (which we'll call flags) is > 0x80, then error.
    // The constant 0x80 is being used both as a threshold and as the value we are about to write.
    
    {
        uint index = 0;
        byte* pEntrySecondField = (byte*)&g_particleListSecond; // start of second fields
        // Check existing entries
        while (index < g_particleCount)
        {
            if (pEntrySecondField[0] > 0x80) // first byte of second field
            {
                FUN_00609bf0(); // error: some particle already "full"?
                return this;
            }
            index++;
            pEntrySecondField += 0xC; // 12-byte stride
        }
    }
    
    // If count < 32, add a new entry
    if (g_particleCount < 32)
    {
        int entryIndex = g_particleCount;
        // Compute offsets: first field is 8 bytes at base+entryIndex*12, second field at base+8+entryIndex*12
        // Write 8-byte value: 0x4887a000000000 (unknown constant, maybe NULL or ID)
        *(uint64_t*)((char*)&g_particleListBase + entryIndex * 12) = 0x4887a000000000ULL;
        // Write 4-byte value: 0x80 (the second field low byte set to 0x80)
        *(uint32_t*)((char*)&g_particleListSecond + entryIndex * 12) = 0x80; // local_4 was built as 0x80
        g_particleCount++;
    }
    
    return this;
}