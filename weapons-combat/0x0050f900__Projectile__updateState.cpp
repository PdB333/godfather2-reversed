//FUNC_NAME: Projectile::updateState
// Function address: 0x0050f900
// This function updates the state of a projectile (bullet, throwable, etc.)
// It handles different states: 0 = flying, 1 = impact, 5 = homing? , 3 = done
// Uses a global projectile data array (size 0x50 per slot) accessed via thread-local storage

#include <cstdint>

// Forward declarations of called functions (assumed from context)
extern float randomFloat(); // FUN_004e41b0
extern void matrixMultiply(float* out, float* a, float* b); // FUN_0044c4c0
extern int createProjectileEffect(int param1, int param2, int param3, float* param4, uint64_t param5); // FUN_0051c7c0
extern uint64_t getSomeValue(); // FUN_0051d730
extern void* allocateMemory(int size); // FUN_004e0750
extern int initSomeObject(void* obj); // FUN_00509260
extern void registerObject(void* obj); // FUN_004deb00
extern void spawnProjectile(int thisPtr, int* param2, int param3, int param4); // FUN_00510110
extern void updateProjectilePhysics(int thisPtr, int* param2, int param3); // FUN_00510f60
extern int getProjectileResult(int* param); // FUN_004e9720
extern void initMatrix(float* mat); // FUN_004f3c20
extern void someMatrixOp(); // FUN_00414aa0
extern void transformVector(float* vec, float* mat); // FUN_0056b420
extern float getProjectileSpeed(int thisPtr, uint32_t flags); // FUN_0050a630
extern void doSomething(int* param); // FUN_00412d90

// Global constant (likely 0.0f or some small value)
extern float DAT_00e2b1a4;

// Thread-local storage offset (FS segment)
#define TLS_OFFSET 0x2c

// Structure for projectile data (size 0x50)
struct ProjectileData {
    // Offsets relative to base of slot
    // +0x00: unknown
    // +0x20: position/velocity? (float[3])
    // +0x2c: some float
    // +0x30: unknown
    // +0x34: unknown
    // +0x38: unknown
    // +0x3c: unknown
    // +0x40: some float
    // +0x44: unknown
    // +0x48: some float
    // +0x4c: unknown
    // +0x50: unknown
    // +0x54: byte (flag?)
    // +0x55: byte (flag?)
    float field_0x20[3]; // offset 0x20
    float field_0x2c;    // offset 0x2c
    float field_0x30;
    float field_0x34;
    float field_0x38;
    float field_0x3c;
    float field_0x40;
    float field_0x44;
    float field_0x48;
    float field_0x4c;
    float field_0x50;
    uint8_t field_0x54;
    uint8_t field_0x55;
    // Note: there is also a ushort at offset 0x36 (within the float array? Actually pfVar3 + 0x36 is used as index)
    // That ushort is likely at offset 0x36 from the start of the slot? But pfVar3 points to offset 0x20, so +0x36 = 0x56? Actually pfVar3 = base + 0x20, so pfVar3 + 0x36 = base + 0x56. That's a ushort index.
    uint16_t index; // at offset 0x56? But careful: the code uses (int)pfVar3 + 0x36, which is base+0x56. So there is a ushort at offset 0x56.
};

// Main class (likely ProjectileManager or Projectile)
class Projectile {
public:
    // Offsets from this pointer
    // +0x04: pointer to something (maybe base class)
    // +0x10: pointer to something (maybe transform)
    // +0x24: pointer to config data
    // +0x28: pointer to something (maybe owner transform)
    // +0x5b: state byte (0,1,3,5)
    // +0x60: pointer to target/owner
    // +0xa8: pointer to something (maybe random offset data)
    // +0xac: pointer to array of results (indexed by ushort from projectile data)
    // +0xb8? (used via param_1+4+0xb8)
    // +0xc4? (used via param_1+4+0xc4)
    // +0x84? (used via param_1+4+0x84)
    // +0xc? (used via param_1+4+0xc)

    // Update function
    uint8_t updateState(int* param2, int param3);
};

uint8_t Projectile::updateState(int* param2, int param3) {
    // Get thread-local storage base
    int* tlsBase = *(int**)(__readfsdword(TLS_OFFSET) + 0x2c);
    int slotOffset = param3 * 0x50;
    int slotBase = *(int*)(tlsBase + 8) + slotOffset; // base of projectile data slot

    // param2 is a pointer to an index into the slot's data (offset from slotBase)
    int dataIndex = *param2;
    float* pfVar3 = (float*)(slotBase + 0x20 + dataIndex); // points to field_0x20

    float fVar11 = *(float*)(slotBase + 0x2c + dataIndex); // field_0x2c
    float fVar15 = pfVar3[7]; // pfVar3[7] = field_0x20+7*4 = offset 0x3c? Actually pfVar3 is float*, so pfVar3[7] = *(float*)(slotBase+0x20+7*4) = slotBase+0x3c. So that's field_0x3c.

    uint8_t result = 0;

    // If random offset data exists, compute a random offset vector
    if (*(int*)(this + 0xa8) != 0) {
        int configPtr = *(int*)(this + 0x24);
        float* randomOffset = (float*)(*(int*)(this + 0xa8) + (uint16_t)(*(uint16_t*)((int)pfVar3 + 0x36)) * 12); // index from projectile data ushort
        float fVar14 = fVar15;
        randomFloat(); // random
        fVar14 = fVar14 * *(float*)(configPtr + 0x164) + *(float*)(configPtr + 0x158);
        randomOffset[0] = fVar14;
        randomFloat(); // random
        fVar14 = fVar14 * *(float*)(configPtr + 0x168) + *(float*)(configPtr + 0x15c);
        randomOffset[1] = fVar14;
        randomFloat(); // random
        randomOffset[2] = fVar14 * *(float*)(configPtr + 0x16c) + *(float*)(configPtr + 0x160);
    }

    // Clear flags at offsets 0x54 and 0x55
    *(uint8_t*)(*(int*)(tlsBase + 8) + slotOffset + 0x54 + dataIndex) = 0;
    *(uint8_t*)(*(int*)(tlsBase + 8) + slotOffset + 0x55 + dataIndex) = 0;

    // Store values
    pfVar3[3] = fVar11; // offset 0x2c
    pfVar3[7] = fVar15; // offset 0x3c

    int base2 = *(int*)(tlsBase + 8) + slotOffset;
    float fVar11b = *(float*)(base2 + 0x48 + dataIndex); // offset 0x48
    if (fVar11b < *(float*)(base2 + 0x40 + dataIndex)) { // offset 0x40
        *(float*)(base2 + dataIndex + 0x40) = fVar11b;
    }

    // If result array exists, clear entry for this projectile
    if (*(int*)(this + 0xac) != 0) {
        *(int*)(*(int*)(this + 0xac) + (uint16_t)(*(uint16_t*)((int)pfVar3 + 0x36)) * 4) = 0;
    }

    pfVar3[0xc] = 0.0f; // offset 0x50? Actually pfVar3[12] = offset 0x20+12*4 = 0x50

    // State machine
    switch (*(uint8_t*)(this + 0x5b) - 1) {
    case 0: // State 1 (flying)
        if (*(int*)(this + 0x60) != 0) {
            int local_70 = *(int*)(*(int*)(this + 4) + 0xc4);
            if (local_70 == 0) {
                local_70 = 0;
            } else {
                local_70 = local_70 - 0x48;
            }
            uint32_t flags = *(uint32_t*)(*(int*)(this + 0x24) + 0x10c);
            int local_6c = -1;
            if ((flags & 0x200000) == 0) {
                if ((flags & 0x400000) != 0) {
                    local_6c = *(int*)(*(int*)(this + 4) + 0xb8);
                }
            } else {
                local_70 = 0;
            }

            float local_60 = 0.0f; // 2.8026e-45 is essentially 0
            float fStack_5c = (float)local_70;
            float fStack_58 = (float)local_6c;
            float fStack_54 = 0.0f;

            // Initialize matrix
            float matrix[12]; // local_50 is 48 bytes = 12 floats
            initMatrix(matrix);
            someMatrixOp();

            local_60 = DAT_00e2b1a4; // global constant

            // Check some flag
            if ((*(uint8_t*)(*(int*)(this + 0x10) + *(int*)(tlsBase + 8)) & 4) != 0) {
                int transformPtr = *(int*)(this + 0x10) + *(int*)(tlsBase + 8) + 0x50;
                float vec[3];
                transformVector(transformPtr, vec, vec);
                if ((*(uint32_t*)(*(int*)(this + 0x24) + 0x104) & 0x200) != 0) {
                    // extraout_EDX is used, but we don't have it; assume some offset
                    // transformPtr = extraout_EDX + 0x10; // not reconstructable
                }
                matrixMultiply(transformPtr, pfVar3 + 4, pfVar3 + 4); // pfVar3+4 = offset 0x30
            }

            int local_68 = 0;
            if ((*(uint32_t*)(*(int*)(this + 4) + 0xc) & 0x400000) != 0) {
                local_68 = 4;
            }

            // Prepare parameters for effect creation
            float params[4] = { local_60, fStack_5c, fStack_58, fStack_54 };
            uint64_t uVar19 = getSomeValue();
            int effectId = createProjectileEffect(
                *(int*)(this + 0x60),
                *(int*)(*(int*)(this + 4) + 0x84),
                local_68,
                params,
                uVar19
            );

            // Store effect ID in result array
            int resultArray = *(int*)(this + 0xac);
            uint16_t idx = *(uint16_t*)((int)pfVar3 + 0x36);
            *(int*)(resultArray + idx * 4) = effectId;

            if (effectId != 0) {
                int* effectPtr = (int*)(resultArray + idx * 4);
                *(int**)(*effectPtr + 8) = effectPtr; // link effect into list
                someMatrixOp();

                // Allocate and initialize some object
                void* obj = allocateMemory(0x40);
                if (obj != 0) {
                    if (initSomeObject(obj) != 0) {
                        *(float*)((int)obj + 0x2c) = *(float*)(*(int*)(tlsBase + 8) + slotOffset + 0x40 + dataIndex);
                        if ((*(uint32_t*)(*(int*)(this + 0x24) + 0x10c) & 0x20) != 0) {
                            int ownerTransform = *(int*)(this + 0x28);
                            *(float*)((int)obj + 0x10) = *(float*)(ownerTransform + 0x40);
                            *(float*)((int)obj + 0x14) = *(float*)(ownerTransform + 0x44);
                            *(float*)((int)obj + 0x18) = *(float*)(ownerTransform + 0x48);
                            *(float*)((int)obj + 0x1c) = *(float*)(ownerTransform + 0x4c);
                        }
                        registerObject(obj);
                    }
                }
                spawnProjectile((int)this, param2, param3, 0);
                return 1;
            }
        }
        break;

    case 1: // State 2 (impact)
        if (*(int*)(this + 0x60) != 0) {
            someMatrixOp();
            uint8_t* flagsPtr = (uint8_t*)(*(int*)(this + 0x10) + *(int*)(tlsBase + 8));
            float fStack_54 = DAT_00e2b1a4;
            if ((*flagsPtr & 4) != 0) {
                // Matrix multiplication with projectile data
                float fVar11 = fStack_5c * *(float*)(flagsPtr + 0x68);
                float fVar15 = fStack_5c * *(float*)(flagsPtr + 0x6c);
                float fVar14 = local_60 * *(float*)(flagsPtr + 0x54);
                float fVar16 = local_60 * *(float*)(flagsPtr + 0x58);
                float fVar17 = local_60 * *(float*)(flagsPtr + 0x5c);
                float fVar18 = fStack_58 * *(float*)(flagsPtr + 0x7c);
                local_60 = fStack_5c * *(float*)(flagsPtr + 0x60) + local_60 * *(float*)(flagsPtr + 0x50) +
                           fStack_58 * *(float*)(flagsPtr + 0x70) + DAT_00e2b1a4 * *(float*)(flagsPtr + 0x80);
                fStack_5c = fStack_5c * *(float*)(flagsPtr + 100) + fVar14 +
                            fStack_58 * *(float*)(flagsPtr + 0x74) + DAT_00e2b1a4 * *(float*)(flagsPtr + 0x84);
                fStack_58 = fVar11 + fVar16 + fStack_58 * *(float*)(flagsPtr + 0x78) +
                            DAT_00e2b1a4 * *(float*)(flagsPtr + 0x88);
                fStack_54 = fVar15 + fVar17 + fVar18 + DAT_00e2b1a4 * *(float*)(flagsPtr + 0x8c);
                pfVar3[0] = local_60;
                pfVar3[1] = fStack_5c;
                pfVar3[2] = fStack_58;
                matrixMultiply(*(int*)(tlsBase + 8) + 0x50 + *(int*)(this + 0x10), pfVar3 + 4, pfVar3 + 4);
            }
            updateProjectilePhysics((int)this, param2, param3);
            int result = getProjectileResult(matrix);
            uint16_t idx = *(uint16_t*)((int)pfVar3 + 0x36);
            *(int*)(*(int*)(this + 0xac) + idx * 4) = result;
            if (*(int*)(*(int*)(this + 0xac) + idx * 4) != 0) {
                return 1;
            }
        }
        break;

    case 5: // State 6 (homing?)
        doSomething(matrix);
        float speed = getProjectileSpeed((int)this, (*(uint32_t*)(*(int*)(this + 0x24) + 0x10c) >> 0x1a) & 0xffffff01);
        uint16_t idx2 = *(uint16_t*)((int)pfVar3 + 0x36);
        *(float*)(*(int*)(this + 0xac) + idx2 * 4) = speed;
        if (speed == 0.0f) {
            return 0;
        }
        pfVar3[0xc] = speed;
        // Fall through to case 3

    case 3: // State 4 (done)
        result = 1;
        break;
    }

    return result;
}