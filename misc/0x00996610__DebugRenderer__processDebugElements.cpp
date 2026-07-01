// FUNC_NAME: DebugRenderer::processDebugElements

// Reconstructed from Ghidra decompilation of function at 0x00996610
// This function processes an array of debug visualization entries (each 0xC0 bytes)
// and performs updates and debug output based on a type field (1, 2, or 3).

void __thiscall DebugRenderer::processDebugElements(int thisPtr, unsigned int param2)
{
    uint uVar1;
    int loopIndex;
    float* pfVar3;
    unsigned int* puEntryBase;
    double dVar5;
    float fGlobalZero = _DAT_00d5780c; // global float, likely 0.0f or epsilon
    float fVar6 = fGlobalZero;
    // Stack arrays for temporary storage
    float afStack_12c[2];
    float afStack_60[4]; // size unknown, used as temp buffer
    char acStack_50[76]; // string buffer for debug output

    int entryCount = *(int*)(thisPtr + 0x38); // number of entries
    if (entryCount <= 0) return;

    int basePtr = *(int*)(thisPtr + 0x34); // pointer to first entry
    int currentOffset = 0; // byte offset into the array (increments by 0xC0)

    do {
        puEntryBase = (unsigned int*)(basePtr + currentOffset);

        int type = *(int*)(thisPtr + 0x50); // current processing type (1,2,3)

        // Type 1 or 2: drawing or transformation debug output
        if (type == 1 || type == 2) {
            // Prepare for virtual call at offset 0x90 (vtable + 0x90)
            // Arguments passed via stack pointers: pfStack_1a4, pfStack_1a8, pfStack_1ac, pfStack_1b0 (labels from decomp)
            float* arg1 = (float*)1; // not sure, maybe flag
            float* arg2 = (float*)(puEntryBase + 0x14); // points to entry + 0x50 (80 bytes)
            // Set some local vectors to zero
            local_d4 = 0; local_c4 = 0; local_b4 = 0;
            float* arg3 = (float*)&uStack_e0; // temp buffer
            float* arg4 = (float*)0x996a74; // debug string pointer
            local_a4 = fVar6; // set to global zero
            // Call virtual function at vtable+0x90 (likely some debug draw call)
            (**(code**)(**(int**)(thisPtr + 0x5c) + 0x90))();

            // Copy result from uStack_e0 to larger stack area (uStack_170 etc.)
            uStack_170 = uStack_e0;
            uStack_16c = uStack_dc;
            uStack_168 = uStack_d8;
            uStack_160 = uStack_d0;
            local_164 = 0;
            uStack_15c = uStack_cc;
            local_154 = 0;
            local_144 = 0;
            uStack_158 = uStack_c8;
            fStack_140 = fStack_b0;
            uStack_150 = uStack_c0;
            fStack_13c = fStack_ac;
            // More parameters for next call
            float* argA = (float*)&uStack_170; // new temp
            uStack_14c = uStack_bc;
            fStack_138 = fStack_a8;
            uStack_148 = uStack_b8;
            local_134 = fGlobalZero;
            float* argB = (float*)0x996b5c; // debug string
            // Call to write/print math info
            FUN_00aa1a80(); // likely prints matrix/transform info

            // Next: copy vector from entry+4 (offset 0x10) to some temp
            float* argC = (float*)(puEntryBase + 4); // entry + 0x10 (16 bytes)
            float* argD = (float*)0x996b6c; // debug string
            FUN_00aa1fc0(); // vector copy/print

            // Next: quaternion/rotation related
            float* argE = (float*)&local_120; // temp
            float* argF = (float*)0x996b80; // debug string
            FUN_00aa3930(); // e.g., quaternion extraction/print

            // Branch based on type (1 vs 2)
            if (type == 2) {
                // Use values at entry+0xA8 (offset 0xA8 = 168) and entry+0xAC (172)
                float* argG = (float*)puEntryBase[0x2A]; // offset 0xA8 (index 0x2A = 42)
                // Setup another temporary from local_120 etc.
                uStack_170 = local_120;
                uStack_16c = uStack_11c;
                uStack_168 = uStack_118;
                local_164 = local_114;
                uStack_160 = uStack_110;
                uStack_15c = uStack_10c;
                uStack_158 = uStack_108;
                local_154 = local_104;
                uStack_150 = uStack_100;
                float* argH = &fStack_f0;
                uStack_14c = uStack_fc;
                float* argI = (float*)1; // count?
                uStack_148 = uStack_f8;
                local_144 = local_f4;
                float* argJ = (float*)0x996c5a; // debug string
                FUN_009fbb20(); // debug print with vector

                // Similar with entry+0xAB? (0x2B = 43, offset 0xAC)
                float* argK = (float*)puEntryBase[0x2B]; // offset 0xAC
                float* argL = (float*)&uStack_170;
                float* argM = (float*)3; // count?
                float* argN = (float*)0x996c73; // debug string
                FUN_009fbb20();

                // Another debug print
                float* argO = (float*)0x996c7a;
                FUN_009f2000(); // simple debug string print
                fVar6 = fGlobalZero;
            }
            else { // type == 1
                // Use first value from entry as pointer? (puEntryBase[0])
                float* argP = (float*)*puEntryBase;
                float* argQ = (float*)afStack_60; // temp buffer
                float* argR = (float*)param2;
                float* argS = &fStack_f0;
                float* argT = (float*)0x996c9b; // debug string
                FUN_009de610(); // some debug output with pointer
                fVar6 = fGlobalZero;
            }
        }
        else if (type == 3) {
            // Check if entry has a non-null pointer at offset 8
            if (puEntryBase[2] != 0) {
                // Similar initialization but with virtual call at offset 0x8C (vtable+0x8C)
                float* arg1 = (float*)1;
                float* arg2 = (float*)(puEntryBase + 0x14); // entry + 0x50
                // Zero many locals
                local_114 = 0; local_104 = 0; local_f4 = 0;
                local_d4 = 0; local_c4 = 0; local_b4 = 0;
                local_164 = 0; local_154 = 0; local_144 = 0;
                local_94 = 0; local_84 = 0; local_74 = 0;
                float* arg3 = (float*)&local_120; // temp buffer
                float* arg4 = (float*)0x99671a; // debug string
                local_134 = fVar6;
                local_e4 = fVar6;
                local_a4 = fVar6;
                local_64 = fVar6;
                // Call virtual function at vtable+0x8C
                (**(code**)(**(int**)(thisPtr + 0x5c) + 0x8c))();

                // Some bit manipulation on values at entry+0x50 (offset 0x50)
                uVar1 = (uint)puEntryBase[0x14] >> 2; // shift right 2
                FUN_004c3f10(uVar1); // likely unpack/convert
                int iVar2 = FUN_004c3f00(uVar1); // get some int

                // More work with entry+0xA0 (offset 0xA0 = 160)
                float* arg5 = (float*)1;
                float* arg6 = (float*)(puEntryBase + 0x28); // entry + 0xA0
                float* arg7 = &fStack_17c; // temp
                (**(code**)(**(int**)(thisPtr + 0x5c) + 0x8c))(); // call again

                uVar1 = (uint)puEntryBase[0x28] >> 2;
                FUN_004c3f10(uVar1);
                iVar2 = FUN_004c3f00(uVar1);

                // Compute flags
                float* arg8 = (float*)( ((uint)(fStack_140 == 0.0) | (int)fStack_140 * 2) * 2 );
                (**(code**)(**(int**)(thisPtr + 0x5c) + 0x8c))(&uStack_f8, &arg8, 1);

                float* arg9 = (float*)( ((uint)arg7 & 1 | iVar2 * 4) ^ (uint)(iVar2 == 0) * 2 );
                (**(code**)(**(int**)(thisPtr + 0x5c) + 0x8c))(&local_c4, &arg9, 1);

                // Vector subtractions
                fStack_17c = fStack_f0 - fStack_b0;
                fStack_178 = fStack_ec - fStack_ac;
                fStack_174 = fStack_e8 - fStack_a8;
                fStack_188 = fStack_140 - fStack_70;
                fStack_184 = fStack_13c - fStack_6c;
                fStack_180 = fStack_138 - fStack_68;

                // Print these vectors via debug functions
                FUN_0043a210(&fStack_17c, (float*)0x99686f); // print vector with debug string
                FUN_0043a210(&fStack_188, (float*)0x99687e);

                // Compute dot product and clamp
                iVar2 = *(int*)(puEntryBase[2] + 12); // get component from pointer at entry+8
                float dotProduct = fStack_184*fStack_178 + fStack_188*fStack_17c + fStack_180*fStack_174;
                afStack_12c[0] = fGlobalZero;
                float fStack_130 = 0.0;
                // Clamping based on dot product sign
                float* pfSelect;
                if (dotProduct <= fGlobalZero) {
                    pfSelect = &fStack_130;
                    if (0.0 <= dotProduct) pfSelect = &dotProduct;
                } else {
                    pfSelect = afStack_12c;
                }
                dVar5 = (double)*pfSelect;
                FUN_00b9b988((float*)0x9968f6); // some math/debug
                fVar6 = fGlobalZero;
                *(float*)(iVar2 + 0xac) = (float)dVar5; // store result
            }

            // Second part of type 3: if entry+4 (offset 4) is non-null
            if (puEntryBase[1] != 0) {
                // Similar pattern with vtable call at 0x8C
                float* argA = (float*)1;
                float* argB = (float*)(puEntryBase + 0x14); // entry+0x50
                local_94 = 0; local_84 = 0; local_74 = 0;
                float* argC = (float*)auStack_a0; // temp
                float* argD = (float*)0x996956; // debug string
                local_64 = fVar6;
                (**(code**)(**(int**)(thisPtr + 0x5c) + 0x8c))();

                // Vector math and debug print
                FUN_00557660(&fStack_ec, &fStack_ac, (float*)0x99696b);

                // Copy vector from entry+4
                FUN_00aa1fc0((float*)(puEntryBase + 4), (float*)0x99697e);

                // Set some locals to zero and one to global zero
                auStack_a0[0] = 0.0;
                uStack_90 = 0; uStack_80 = 0;
                float* argE = (float*)1;
                float* argF = (float*)(puEntryBase + 0x28); // entry+0xA0
                fStack_70 = fGlobalZero;
                float* argG = &fStack_ac;
                (**(code**)(**(int**)(thisPtr + 0x5c) + 0x8c))();

                FUN_00557660((float*)&local_120, (float*)auStack_a0, (float*)0x9969e0);

                // Another vector copy
                FUN_00aa1fc0((float*)(puEntryBase + 0x18), (float*)0x9969f3); // entry+0x60? (index 0x18 = 24 -> offset 0x60)

                FUN_00aa20e0((float*)&local_120, (float*)&uStack_e0, (float*)0x996a0f); // transform/dbg

                // String buffer print
                FUN_00994890(acStack_50, (float*)0x996a20);

                // Final debug print
                FUN_009fa170((float*)&uStack_170, (float*)0x996a30);
                fVar6 = fGlobalZero;
            }
        }

        currentOffset += 0xC0; // next entry (192 bytes)
        loopIndex++;
    } while (loopIndex < entryCount);
}