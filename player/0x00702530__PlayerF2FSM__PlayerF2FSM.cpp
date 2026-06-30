// FUNC_NAME: PlayerF2FSM::PlayerF2FSM
// Constructor for PlayerF2FSM (Player Free-For-All State Machine) - offset 0x702530
// Initializes base class and all state machine fields with defaults

class PlayerF2FSM; // forward declare

// Known global constants (floats, vectors, etc.)
extern float DAT_00e44718; // uVar3
extern float DAT_00d5fb0c; // uVar1
extern float DAT_00d5eee4; // uVar2
extern float DAT_00d5f18c; // uVar4
extern float DAT_00d5c458;
extern float DAT_00d60d10;
extern float DAT_00d60d0c;
extern float DAT_00d5ef88;
extern float DAT_00d5e288;
extern float DAT_00d60d08;
extern float DAT_00d5ef90;
// Vtable pointers
extern void* PTR_FUN_00d60df8; // main vtable
extern void* PTR_LAB_00d60de8;
extern void* PTR_LAB_00d60de4;
extern void* PTR_LAB_00d60de0;
extern void* PTR_LAB_00d60d80;
extern void* PTR_LAB_00d60d18;
extern void* DAT_00d60d10; // latter reused as pointer
extern void* DAT_00d60d0c;
// Data block for default initialization
extern const float DAT_00e515e0[42]; // 0x2A * 4 bytes
extern const float DAT_00e51688[16]; // 0x10 * 4 bytes

// Base constructor (from FUN_00708560) - likely initializes common Player part
void __thiscall PlayerBaseConstructor(PlayerF2FSM* this, unsigned int param_2);

// Some debug or string initialization (FUN_006d9b40)
void __thiscall InitDebugName(PlayerF2FSM* this);

class PlayerF2FSM {
public:
    // Vtable at offset 0
    // Fields at various offsets, only those set in constructor
    // The exact structure is large; we document key offsets.
    
    // Constructor
    PlayerF2FSM* __thiscall PlayerF2FSM(PlayerF2FSM* this, unsigned int param_2) {
        float uVar1 = DAT_00d5fb0c;
        float uVar2 = DAT_00d5eee4;
        float uVar3 = DAT_00e44718;
        float uVar4 = DAT_00d5f18c;

        // Call base constructor
        PlayerBaseConstructor(this, param_2);

        // Set vtable
        *(void**)this = &PTR_FUN_00d60df8;                     // +0x00 vtable

        // Virtual method table pointers (alternative vtable or interface)
        *(void**)((int)this + 0x3C) = &PTR_LAB_00d60de8;      // +0x3C
        *(void**)((int)this + 0x48) = &PTR_LAB_00d60de4;      // +0x48
        *(void**)((int)this + 0x50) = &PTR_LAB_00d60de0;      // +0x50
        *(void**)((int)this + 0x54) = &PTR_LAB_00d60d80;      // +0x54
        *(void**)((int)this + 0x58) = &PTR_LAB_00d60d18;      // +0x58

        // Initialize various state variables
        *(float*)((int)this + 0x2D0) = 0.0f;                  // +0x2D0
        *(float*)((int)this + 0x2D4) = 0.0f;                  // +0x2D4
        *(float*)((int)this + 0x2D8) = 0.0f;                  // +0x2D8
        *(float*)((int)this + 0x2DC) = 1.0f;                  // +0x2DC
        *(float*)((int)this + 0x2E0) = uVar1;                 // +0x2E0
        *(float*)((int)this + 0x2E4) = uVar2;                 // +0x2E4
        *(float*)((int)this + 0x2E8) = 0.0f;                  // +0x2E8
        *(float*)((int)this + 0x2EC) = 0.0f;                  // +0x2EC
        *(float*)((int)this + 0x2F0) = uVar1;                 // +0x2F0
        *(float*)((int)this + 0x2F4) = uVar1;                 // +0x2F4
        *(float*)((int)this + 0x2F8) = uVar2;                 // +0x2F8
        *(float*)((int)this + 0x2FC) = uVar2;                 // +0x2FC
        *(float*)((int)this + 0x300) = uVar2;                 // +0x300
        *(float*)((int)this + 0x304) = uVar3;                 // +0x304
        *(float*)((int)this + 0x308) = uVar1;                 // +0x308
        *(float*)((int)this + 0x30C) = uVar3;                 // +0x30C
        *(float*)((int)this + 0x310) = uVar1;                 // +0x310
        *(float*)((int)this + 0x314) = uVar3;                 // +0x314
        *(void**)((int)this + 0x318) = DAT_00d60d10;          // +0x318
        *(float*)((int)this + 0x31C) = DAT_00d5c458;         // +0x31C
        *(void**)((int)this + 0x320) = (void*)uVar1;          // +0x320 (cast to void*? might be float)
        *(void**)((int)this + 0x324) = DAT_00d60d0c;          // +0x324
        *(float*)((int)this + 0x328) = 0.0f;                  // +0x328
        *(float*)((int)this + 0x32C) = 8.0f;                  // +0x32C
        *(float*)((int)this + 0x330) = 100.0f;                // +0x330
        *(float*)((int)this + 0x334) = 0.0f;                  // +0x334
        *(float*)((int)this + 0x338) = uVar1;                 // +0x338
        *(float*)((int)this + 0x33C) = uVar4;                 // +0x33C
        *(float*)((int)this + 0x340) = 0.0f;                  // +0x340
        *(float*)((int)this + 0x344) = 0.0f;                  // +0x344
        // Two shorts making a 32-bit value at 0x348
        *(short*)((int)this + 0x348) = 0;                     // +0x348 low
        *(short*)((int)this + 0x34A) = 0;                     // +0x34A high -> total 0
        *(float*)((int)this + 0x34C) = uVar2;                 // +0x34C
        *(float*)((int)this + 0x350) = uVar2;                 // +0x350
        *(float*)((int)this + 0x354) = 0.0f;                  // +0x354
        *(float*)((int)this + 0x358) = 0.0f;                  // +0x358
        *(float*)((int)this + 0x35C) = 0.0f;                  // +0x35C
        *(float*)((int)this + 0x360) = 0.0f;                  // +0x360
        *(float*)((int)this + 0x364) = 1.0f;                  // +0x364
        *(int*)((int)this + 0x368) = -1;                      // +0x368
        *(float*)((int)this + 0x36C) = 0.0f;                  // +0x36C
        *(float*)((int)this + 0x370) = 0.0f;                  // +0x370
        *(float*)((int)this + 0x374) = 0.0f;                  // +0x374
        *(float*)((int)this + 0x378) = 0.0f;                  // +0x378
        *(float*)((int)this + 0x37C) = uVar3;                 // +0x37C
        *(char*)((int)this + 0x380) = 0;                      // +0x380 (first byte)
        // Later range: +0x488 to +0x49C
        *(float*)((int)this + 0x488) = uVar1;                 // +0x488
        *(float*)((int)this + 0x48C) = 0.0f;                  // +0x48C
        *(float*)((int)this + 0x490) = uVar1;                 // +0x490
        *(float*)((int)this + 0x494) = 0.0f;                  // +0x494
        *(float*)((int)this + 0x498) = uVar1;                 // +0x498
        *(int*)((int)this + 0x49C) = 3;                       // +0x49C

        InitDebugName(this);

        // More state initialization (offsets around 0x4D0-0x528)
        for (int i = 0; i < 10; i++)
            *(float*)((int)this + 0x4D0 + i*4) = 0.0f;        // +0x4D0..0x4FC? Actually separate assignments
        // Actually the decompiler shows separate zeroing from 0x134 to 0x13c (indices)
        *(float*)((int)this + 0x4D0) = 0.0f;  // param_1[0x134]
        *(float*)((int)this + 0x4D4) = 0.0f;  // param_1[0x135]
        *(float*)((int)this + 0x4D8) = 0.0f;  // param_1[0x136]
        *(float*)((int)this + 0x4DC) = 0.0f;  // param_1[0x137]
        *(float*)((int)this + 0x4E0) = 0.0f;  // param_1[0x138]
        *(float*)((int)this + 0x4E4) = 0.0f;  // param_1[0x139]
        *(float*)((int)this + 0x4E8) = 0.0f;  // param_1[0x13a]
        *(float*)((int)this + 0x4EC) = 0.0f;  // param_1[0x13b]
        *(float*)((int)this + 0x4F0) = 0.0f;  // param_1[0x13c]
        *(float*)((int)this + 0x4F4) = 1000.0f; // param_1[0x13d]
        *(float*)((int)this + 0x4F8) = 0.0f;  // param_1[0x13e]
        *(void**)((int)this + 0x4FC) = (void*)uVar1; // param_1[0x13f] cast?
        *(void**)((int)this + 0x500) = (void*)DAT_00d5ef90; // +0x500
        *(float*)((int)this + 0x504) = 0.0f;  // param_1[0x141]
        *(float*)((int)this + 0x508) = 0.0f;  // param_1[0x142]
        *(float*)((int)this + 0x50C) = 0.0f;  // param_1[0x143]
        *(float*)((int)this + 0x510) = 0.0f;  // param_1[0x144]
        *(float*)((int)this + 0x514) = 0.0f;  // param_1[0x145]
        *(float*)((int)this + 0x518) = 0.0f;  // param_1[0x146]
        *(float*)((int)this + 0x51C) = 0.0f;  // param_1[0x147]
        *(float*)((int)this + 0x520) = 0.0f;  // param_1[0x148]
        *(float*)((int)this + 0x524) = 0.0f;  // param_1[0x149]
        *(float*)((int)this + 0x528) = 0.0f;  // param_1[0x14a]

        // Set flag at +0x1D0
        *(int*)((int)this + 0x1D0) |= 0x10;   // param_1[0x74]

        // Copy default data from static arrays
        // First block: copy 42 floats from DAT_00e515e0 to offset +0x384
        for (int i = 0; i < 42; i++)
            *(float*)((int)this + 0x384 + i*4) = DAT_00e515e0[i];

        // Second block: copy 16 floats from DAT_00e51688 to offset +0x42C
        for (int i = 0; i < 16; i++)
            *(float*)((int)this + 0x42C + i*4) = DAT_00e51688[i];

        // Copy first 4 floats of the first block (8 bytes each) to later offsets
        // Actually they copy double (8-byte) values? The decompiler uses undefined8*.
        // Since floats are 4 bytes, copying 8 bytes means two floats at a time.
        // We'll cast to __int64 or just copy two floats.
        *(long long*)((int)this + 0x46C) = *(long long*)((int)this + 0x384); // +0x46C = +0x11b
        *(long long*)((int)this + 0x474) = *(long long*)((int)this + 0x38C); // +0x474 = +0x11d
        *(long long*)((int)this + 0x47C) = *(long long*)((int)this + 0x394); // +0x47C = +0x11f
        *(float*)((int)this + 0x484) = *(float*)((int)this + 0x39C); // +0x484 = +0x121 (single float from +0x39C)

        return this;
    }
};