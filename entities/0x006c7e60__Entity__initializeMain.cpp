// FUNC_NAME: Entity::initializeMain

// Reconstructed C++ for 0x006c7e60 – Main initialization function for an Entity subclass (likely player vehicle or agent)
// The function heavily accesses fields at various offsets, suggesting a large class (e.g., BaseVehicle, Player, SimNpc)
// Uses EARS engine globals: _DAT_00d5780c (zero constant), _DAT_00d5c458 (scale factor), _DAT_012233a0 (sim pointer array)
// Known subcalls: base init (0x6c85d0), vehicle brain init (0x6ca8e0, 0x6ca410), random (0x425190), time query (0x6c55d0), etc.

void __thiscall Entity::initializeMain(void* thisPtr, int someIndex, char initFlag) {
    float* pfVar1;
    int* piVar7;
    float fVar9, fVar10, fVar11;
    float local_4;
    int iVar6;
    char cVar5;
    undefined4 uVar3;
    uint uVar4;

    // Store 'this' as float* for convenience (Ghidra decompiler artifact)
    float* thisFloat = (float*)thisPtr;
    void* thisVoid = thisPtr;

    // Base instance initialization
    FUN_006c85d0(someIndex, initFlag);

    // Set fields at known offsets (comments indicate likely purpose based on context)
    *(thisFloat + 0x18) = _DAT_00d5780c;          // +0x60: some timer/velocity (0.0 constant)
    *(undefined4*)(thisVoid + 0x2cc) = DAT_00e44940; // +0x2cc: state/flag
    *(undefined4*)(thisVoid + 0x2e4) = 0;           // +0x2e4: reset
    *(undefined4*)(thisVoid + 0x2e8) = 0;           // +0x2e8: reset

    if ((*(int*)(thisVoid + 0xe8) == 0) || (*(int*)(thisVoid + 0xe8) == 0x48)) {
        // +0xe8 likely subtype/state; if default or specific (0x48 = 72, maybe "driving"?)
        *(thisFloat + 0xb8) = (*(thisFloat + 0x42) + *(thisFloat + 0x41)) * _DAT_00d5c458; // +0x2e0 = (0x108 + 0x104) * scaleFactor
    } else {
        // Other subtypes: compute derived index and call functions
        iVar6 = (*(int*)(thisVoid + 0xe8) == 0) ? 0 : (*(int*)(thisVoid + 0xe8) - 0x48);
        *(int*)(thisVoid + 0x88) = iVar6; // +0x88: store index
        iVar6 = (*(int*)(thisVoid + 0xe8) == 0) ? 0 : (*(int*)(thisVoid + 0xe8) - 0x48);
        FUN_006ca8e0(iVar6);               // likely initializes sub-component (vehicle brain?)

        // Get pointer to sub-object using same offset trick
        piVar7 = (*(int*)(thisVoid + 0xe8) == 0) ? nullptr : (int*)(*(int*)(thisVoid + 0xe8) - 0x48);
        local_4 = 0.0f;
        // Query some property via virtual function at offset 0x10 (Hash: 0xf8b45dfb)
        cVar5 = (**(code**)(*piVar7 + 0x10))(0xf8b45dfb, &local_4);
        if ((cVar5 == 0) || (local_4 == 0.0f)) {
            cVar5 = 0;
        } else {
            cVar5 = 1;
        }
        *(char*)(thisVoid + 0x2bc) = cVar5; // +700 = +0x2bc: some activation flag

        if (cVar5 != 0) {
            piVar7 = (*(int*)(thisVoid + 0xe8) == 0) ? nullptr : (int*)(*(int*)(thisVoid + 0xe8) - 0x48);
            local_4 = 0.0f;
            cVar5 = (**(code**)(*piVar7 + 0x10))(0x10e5319e, &local_4);
            if ((cVar5 != 0) && (local_4 != 0.0f)) {
                // Add offsets from some external object (local_4 points to it)
                *(thisFloat + 0x44) += *(float*)((int)local_4 + 0xaa8);   // +0x110
                fVar10 = *(float*)((int)local_4 + 0xaac);                  // fetch value
                *(thisFloat + 0x41) += fVar10;  // +0x104
                *(thisFloat + 0x42) += fVar10;  // +0x108
                *(thisFloat + 0x70) += fVar10;  // +0x1c0
                *(thisFloat + 0x71) += fVar10;  // +0x1c4
                *(thisFloat + 0x74) += fVar10;  // +0x1d0
                *(thisFloat + 0x75) += fVar10;  // +0x1d4
            }
        }

        *(thisFloat + 0xb8) = (*(thisFloat + 0x41) + *(thisFloat + 0x42)) * _DAT_00d5c458; // +0x2e0

        iVar6 = (*(int*)(thisVoid + 0xe8) == 0) ? 0 : (*(int*)(thisVoid + 0xe8) - 0x48);
        FUN_006ca410(iVar6); // another sub-component init

        // Get a random/input value
        float fVar8 = (float10)FUN_00425190(someIndex); // likely random or time-based
        local_4 = (float)fVar8;

        if ((initFlag == 0) || (local_4 == _DAT_00d577a0)) {
            *(thisFloat + 0xa6) = _DAT_00d5780c; // +0x298: set to zero
        } else {
            FUN_006c3ad0(someIndex); // alternative path
        }

        // Copy world transform from a global object (FUN_00471610 likely gets camera/player)
        pfVar1 = (thisFloat + 0x88); // +0x220 (position in world)
        iVar6 = FUN_00471610();
        *(undefined8*)pfVar1 = *(undefined8*)(iVar6 + 0x30); // copy x,y
        *(thisFloat + 0x8a) = *(float*)(iVar6 + 0x38);       // +0x228: z

        // Add elapsed time (FUN_006c55d0 returns some delta)
        fVar8 = (float10)FUN_006c55d0();
        *(thisFloat + 0x89) += (float)fVar8; // +0x224: accumulate

        // Initialize various fields to defaults
        *(undefined4*)(thisVoid + 0x27c) = 0;
        *(undefined4*)(thisVoid + 0x268) = 0;
        *(undefined4*)(thisVoid + 0x284) = *(undefined4*)(thisVoid + 0x1e8);
        *(undefined4*)(thisVoid + 0x294) = *(undefined4*)(thisVoid + 0x1ec);
        *(thisFloat + 0xac) = *(thisFloat + 0x42); // +0x2b0 = +0x108
        *(undefined8*)(thisVoid + 0x24c) = *(undefined8*)pfVar1; // copy position
        *(undefined4*)(thisVoid + 0x2ec) = *(undefined4*)(thisVoid + 0x1f0);
        *(thisFloat + 0x95) = *(thisFloat + 0x8a); // +0x254 = +0x228

        if ((*(char*)(thisVoid + 0x2bc) == 0) && (local_4 != 0.0f)) {
            if (initFlag == 0) {
                FUN_006c7d60(someIndex, 0); // activate? (0 param)
            } else {
                FUN_006c5a60(someIndex); // variant
            }
        } else {
            FUN_006c5c70(); // default route
        }

        fVar10 = _DAT_00d5780c; // zero
        if (_DAT_00d5780c <= *(thisFloat + 0xa6)) {
            uVar3 = *(undefined4*)(thisVoid + 0x13c);
        } else {
            uVar3 = *(undefined4*)(thisVoid + 0x140);
        }
        *(undefined4*)(thisVoid + 0x2a8) = uVar3;

        // Interpolate a value based on +0x298 and +0x80
        fVar9 = *(thisFloat + 0x46); // +0x118
        fVar9 = (((*(thisFloat + 0x47) - fVar9) * *(thisFloat + 0xa6) + fVar9) - fVar9) * *(thisFloat + 0x20) + fVar9;
        *(thisFloat + 0x91) = fVar9; // +0x244

        if (*(char*)(thisVoid + 0x2bc) == 0) {
            if (fVar9 > 0.0f) {
                if (DAT_00d5eff8 <= fVar9) {
                    fVar9 = DAT_00d5eff8;
                }
            } else {
                fVar9 = 0.0f;
            }
            *(thisFloat + 0x91) = fVar9;
        }

        // Reset many fields:
        *(undefined4*)(thisVoid + 0x26c) = 0;
        *(char*)(thisVoid + 0x270) = 0;
        *(undefined4*)(thisVoid + 0x274) = 0;
        *(char*)(thisVoid + 0x278) = 0;
        *(undefined4*)(thisVoid + 0x280) = 0;
        *(undefined4*)(thisVoid + 0x288) = 0;
        *(thisFloat + 0xa3) = fVar10; // +0x28c = zero
        *(undefined4*)(thisVoid + 0x290) = 0;
        *(undefined4*)(thisVoid + 0x2ac) = *(undefined4*)(thisVoid + 0x14c);

        if ((*(char*)(thisVoid + 0x2bc) != 0) || (local_4 == 0.0f)) {
            float* puVar2 = (float*)(thisVoid + 0x238);
            FUN_006ca5e0(pfVar1, puVar2, puVar2); // compute something (e.g., quaternion)
            fVar10 = _DAT_00d5780c;
            *(thisFloat + 0x08) = *puVar2;         // +0x20
            *(thisFloat + 0x09) = *(thisFloat + 0x8f); // +0x24 = +0x23c
            *(thisFloat + 0x0b) = fVar10;           // +0x2c = 0
            *(thisFloat + 0x0a) = *(thisFloat + 0x90); // +0x28 = +0x240
            *(thisFloat + 0x10) = *(thisFloat + 0x8b); // +0x40 = +0x22c
            *(thisFloat + 0x11) = *(thisFloat + 0x8c); // +0x44 = +0x230
            *(thisFloat + 0x13) = fVar10;           // +0x4c = 0
            *(thisFloat + 0x12) = *(thisFloat + 0x8d); // +0x48 = +0x234
            *(thisFloat + 0x14) = *(thisFloat + 0x91) * DAT_00e445c8; // +0x50 = +0x244 * scale
        }

        // Compute distance from current position to target (stored in +0x238)
        fVar10 = *(thisFloat + 0x8e) - *pfVar1; // +0x238 - +0x220
        fVar9 = *(thisFloat + 0x8f) - *(thisFloat + 0x89); // +0x23c - +0x224
        fVar11 = *(thisFloat + 0x90) - *(thisFloat + 0x8a); // +0x240 - +0x228
        fVar10 = sqrtf(fVar11*fVar11 + fVar9*fVar9 + fVar10*fVar10);
        *(thisFloat + 0x1c) = fVar10; // +0x70: distance
        FUN_00473b10(fVar10); // log/debug

        // More field initializations:
        *(thisFloat + 0xad) = *(thisFloat + 0x42); // +0x2b4 = +0x108
        uVar3 = DAT_00e50e64;
        *(undefined4*)(thisVoid + 0x2b8) = 0;
        *(undefined4*)(thisVoid + 0x2c0) = 0;
        *(undefined4*)(thisVoid + 0x2c4) = uVar3;
    }

    // Common finalization regardless of branch
    *(undefined4*)(thisVoid + 0x2f4) = *(undefined4*)(thisVoid + 0x1b8);
    iVar6 = *(int*)(*(int*)(DAT_012233a0 + 4) + someIndex * 4);
    if (iVar6 == 0) {
        iVar6 = 0;
    } else {
        iVar6 = iVar6 - 0x1f30; // offset to some object
    }
    *(int*)(thisVoid + 0x2c8) = iVar6;
    if (iVar6 != 0) {
        *(uint*)(iVar6 + 0x249c) &= 0xffbfffff; // clear a bit
    }

    *(undefined4*)(thisVoid + 0x2d0) = DAT_00e44854;
    *(thisFloat + 0xb5) = _DAT_00d5780c; // +0x2d4 = 0
    *(undefined4*)(thisVoid + 0x2f0) = 0;
    *(thisFloat + 0xbf) = *(thisFloat + 0x85) - *(thisFloat + 0x88); // +0x2fc = +0x214 - +0x220
    *(thisFloat + 0xc0) = *(thisFloat + 0x86) - *(thisFloat + 0x89); // +0x300 = +0x218 - +0x224
    *(thisFloat + 0xc1) = *(thisFloat + 0x87) - *(thisFloat + 0x8a); // +0x304 = +0x21c - +0x228
    uVar4 = DAT_01205224;
    *(uint*)(thisVoid + 0x2f8) = DAT_01205224;
    if (*(uint*)(thisVoid + 0x204) < uVar4) {
        *(uint*)(thisVoid + 0x2f8) = uVar4 - *(uint*)(thisVoid + 0x204);
    }
    *(undefined4*)(thisVoid + 0x2d8) = DAT_00e50e78;
    if ((*(char*)(thisVoid + 0x2bc) != 0) && (*(int*)(thisVoid + 0xe8) != 0) && (*(int*)(thisVoid + 0xe8) != 0x48)) {
        iVar6 = FUN_00471610();
        FUN_006c1ab0(iVar6 + 0x20); // update something (camera follow?
    }
    *(char*)(thisVoid + 0x308) = 0;
    *(undefined4*)(thisVoid + 0x30c) = 0;
    return;
}