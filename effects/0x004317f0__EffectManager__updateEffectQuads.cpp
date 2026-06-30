// FUNC_NAME: EffectManager::updateEffectQuads
void EffectManager::updateEffectQuads(int quadIndex)
{
    // Global globals used for condition checks
    uint32_t baseColorValue;
    if (*(int*)(*(int*)(DAT_012233a8 + 4) + 0x39f8) != 0) {
        baseColorValue = DAT_0120536c;   // Alternate color
    } else {
        baseColorValue = DAT_012118c0;   // Default color
    }

    // --- Object A (type selector offset 0x1e4) ---
    // Pointer 0x0110b430 (first object of type A)
    {
        void* obj = PTR_DAT_0110b430;
        *(uint32_t*)((char*)obj + 0x1e4) = baseColorValue;           // +0x1e4: color/category
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e0) != 0) {
            FUN_006063b0();   // Some additional setup (maybe flush or update)
        }
    }
    // Pointer 0x0110b3dc (second object of type A)
    {
        void* obj = PTR_DAT_0110b3dc;
        *(uint32_t*)((char*)obj + 0x1e4) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e0) != 0) {
            FUN_006063b0();
        }
    }
    // Pointer 0x0110b3f8 (third object of type A)
    {
        void* obj = PTR_DAT_0110b3f8;
        *(uint32_t*)((char*)obj + 0x1e4) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e0) != 0) {
            FUN_006063b0();
        }
    }
    // Pointer 0x0110b5fc (fourth object of type A)
    {
        void* obj = PTR_DAT_0110b5fc;
        *(uint32_t*)((char*)obj + 0x1e4) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e0) != 0) {
            FUN_006063b0();
        }
    }

    // --- Object B (type selector offset 0x294) ---
    // Pointer 0x0110b4b0
    {
        void* obj = PTR_DAT_0110b4b0;
        *(uint32_t*)((char*)obj + 0x294) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x290) != 0) {
            FUN_006063b0();
        }
    }
    // Pointer 0x01206a58 (global)
    {
        void* obj = DAT_01206a58;
        *(uint32_t*)((char*)obj + 0x294) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x290) != 0) {
            FUN_006063b0();
        }
    }

    // --- Object C (type selector offset 0x274) ---
    // Pointer 0x0110b294
    {
        void* obj = PTR_DAT_0110b294;
        *(uint32_t*)((char*)obj + 0x274) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x270) != 0) {
            FUN_006063b0();
        }
    }

    // --- Object D (type selector offset 0x284) ---
    // Pointer 0x0110b324
    {
        void* obj = PTR_DAT_0110b324;
        *(uint32_t*)((char*)obj + 0x284) = baseColorValue;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x280) != 0) {
            FUN_006063b0();
        }
    }

    // --- Now compute UV coordinates for the quads ---
    // Tables: DAT_0110ac40 and DAT_0110ac44 are arrays of 2 floats each (8 bytes per entry)
    // param_1 (quadIndex) selects which pair of coordinates to use.
    float scaleX = DAT_0110ac30;   // Global scale factor for X
    float scaleY = DAT_0110ac2c;   // Global scale factor for Y (different from scaleX)

    // Read the chosen UV pair from the tables
    float u1 = *(float*)(&DAT_0110ac40 + quadIndex * 8);
    float v1 = *(float*)(&DAT_0110ac44 + quadIndex * 8);
    float u2 = *(float*)(&DAT_0110ac40 + quadIndex * 8);   // Actually we only read two pairs? Decompiled shows repeated access
    // Wait, the decompiled uses DAT_0110ac40+quadIndex*8 and DAT_0110ac44+quadIndex*8 twice, but with different scale factors.
    // It uses DAT_0110ac30 for first, DAT_0110ac2c for second. So we have two different scaled sets.
    // Let's compute:
    float c1_x = *(float*)(&DAT_0110ac40 + quadIndex * 8) * DAT_0110ac30;
    float c1_y = *(float*)(&DAT_0110ac44 + quadIndex * 8) * DAT_0110ac30;
    float c2_x = *(float*)(&DAT_0110ac40 + quadIndex * 8) * DAT_0110ac2c;
    float c2_y = *(float*)(&DAT_0110ac44 + quadIndex * 8) * DAT_0110ac2c;

    // Constant 1.0 (DAT_00e2b1a4) used for inverse computation
    float one = DAT_00e2b1a4;
    float inv_x1 = one - c1_x;
    float inv_y1 = one - c1_y;
    float inv_x2 = one - c2_x;
    float inv_y2 = one - c2_y;

    // --- Apply coordinates to each object ---
    // Object A (type A): offset 0x1f0 for first float, then 0x1f4 (500), 0x1f8, 0x1fc
    // Actually layout: +0x1f0 = inv_x1, +0x1f4 = inv_y1, +0x1f8 = c1_x, +0x1fc = c1_y
    {
        void* obj = PTR_DAT_0110b430;
        float* uvp = (float*)((char*)obj + 0x1f0);
        uvp[0] = inv_x1;
        uvp[1] = inv_y1;
        uvp[2] = c1_x;
        uvp[3] = c1_y;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e8) != 0) {
            FUN_0060add0(*(uint32_t*)((char*)obj + 0x14), *(int*)((char*)obj + 0x1e8), uvp);
            one = DAT_00e2b1a4;  // restore? Actually this assignment seems erroneous; it's just used again later.
        }
    }

    // Object B (type B): offset 0x2a0 (first float), then 0x2a4, 0x2a8, 0x2ac
    {
        void* obj = PTR_DAT_0110b4b0;
        float* uvp = (float*)((char*)obj + 0x2a0);
        uvp[0] = inv_x1;
        uvp[1] = inv_y1;
        uvp[2] = c1_x;
        uvp[3] = c1_y;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x298) != 0) {
            FUN_0060add0(*(uint32_t*)((char*)obj + 0x14), *(int*)((char*)obj + 0x298), uvp);
            one = DAT_00e2b1a4;
        }
    }

    // Object C (type A): reuses c2_x, c2_y (different scaling)
    {
        void* obj = PTR_DAT_0110b3dc;
        float* uvp = (float*)((char*)obj + 0x1f0);
        float inv_x2_local = one - c2_x;  // Note: here 'one' may have been changed if previous condition triggered, but original code used fVar6 (c2_x) and fVar8 (c2_y)
        float inv_y2_local = one - c2_y;
        uvp[0] = inv_x2_local;
        uvp[1] = inv_y2_local;
        uvp[2] = c2_x;
        uvp[3] = c2_y;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e8) != 0) {
            FUN_0060add0(*(uint32_t*)((char*)obj + 0x14), *(int*)((char*)obj + 0x1e8), uvp);
        }
    }

    // Object D (type A): same c2_x, c2_y
    {
        void* obj = PTR_DAT_0110b3f8;
        float* uvp = (float*)((char*)obj + 0x1f0);
        uvp[0] = inv_x2_local;  // Actually original code stored inv_x2 first, then c2_x at +0x1f8, then inv_y2 at 500, then c2_y at +0x1fc
        uvp[1] = inv_y2_local;
        uvp[2] = c2_x;
        uvp[3] = c2_y;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e8) != 0) {
            FUN_0060add0(*(uint32_t*)((char*)obj + 0x14), *(int*)((char*)obj + 0x1e8), uvp);
        }
    }

    // Object E (type A): same c2_x, c2_y (pointer 0x0110b5fc)
    {
        void* obj = PTR_DAT_0110b5fc;
        float* uvp = (float*)((char*)obj + 0x1f0);
        uvp[0] = inv_x2_local;
        uvp[1] = inv_y2_local;
        uvp[2] = c2_x;
        uvp[3] = c2_y;
        if (DAT_012058e8 == obj && *(int*)((char*)obj + 0x1e8) != 0) {
            FUN_0060add0(*(uint32_t*)((char*)obj + 0x14), *(int*)((char*)obj + 0x1e8), uvp);
        }
    }

    // Final call: FUN_0041bf60 takes three floats (c2_y, c1_x, c1_y) — likely sets a global transform.
    FUN_0041bf60(c2_y, c1_x, c1_y);
    return;
}