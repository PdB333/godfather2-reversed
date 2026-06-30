// FUNC_NAME: initParticleEffect
bool __fastcall initParticleEffect(void* config, void* effect)
{
    // +0x24: pointer to config data
    // +0x28: some identifier
    // +0x2c: flags
    // +0x4c: unknown
    // +0x5b: particle type (0-6)
    // +0x58: particle count (short)
    // +0x5c: stride (short)
    // +0x34,0x38: color (float[2])
    // +0x90,0x94: bounds (float[2])
    // +0x80-0x8c: transform matrix (4 floats)
    // +0xb0: particle data array
    // +0xa8: optional extra array (offset stored)
    // +0xac: optional second array (offset stored)

    float* floatPtr;
    char type;
    float fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar22, fVar23;
    int iVar14, iVar15, iVar16;
    uint* puVar17;
    int* piVar18;
    void** ppvVar19;
    void** ppvVar20;
    float* pfVar21;
    int intLocal1, intLocal2;
    void* local18;
    float local14;
    void* local20;
    float local1c;
    int unaff_FS_OFFSET; // Thread-local storage base

    // Clear flags and unknown field
    *(uint*)(effect + 0x2c) = 0;
    *(uint*)(effect + 0x4c) = 0;

    // Copy config data
    *(void**)(effect + 0x24) = *(void**)(config + 4);
    *(int*)(effect + 0x28) = *(int*)(config + 8);

    // Check config flag 0x8000, set bit 0x100 in some memory
    if ((*(uint*)(effect + 0x24) + 0x108) & 0x8000)
    {
        puVar17 = (uint*)(*(int*)(effect + 0x10) + *(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8));
        *puVar17 |= 0x100;
    }

    // Set default pointer
    *(void**)(effect + 0x48) = DAT_00e2b1a4;

    // Copy particle type
    type = *(char*)(config + 0x154);
    *(char*)(effect + 0x5b) = type;

    // Check config flag 0x4000 and type 6
    if ((*(uint*)(*(int*)(effect + 0x24) + 0x104) & 0x4000) && (type == 6))
    {
        puVar17 = (uint*)(*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8) + *(int*)(effect + 0x10));
        *puVar17 |= 0x4000000;
    }

    // Zero many fields
    *(uint*)(effect + 0xa0) = 0;
    *(uint*)(effect + 0xa4) = 0;
    *(uint*)(effect + 0x70) = 0;
    *(uint*)(effect + 100) = 0;
    *(uint*)(effect + 0x60) = 0;
    *(uint*)(effect + 0x68) = 0;
    *(uint*)(effect + 0x6c) = 0;

    // Get particle count (short at config+0x11a)
    int particleCount = (int)*(short*)(config + 0x11a);
    if (particleCount == 0)
        return false;

    // Round up particleCount to multiple of 8? Actually calculation for array size
    int countRounded = particleCount + 7;
    countRounded = (countRounded + (countRounded >> 31 & 7)) >> 3; // divide by 8
    int arrayByteSize = countRounded * 8; // 8 bytes per element? Or number of elements?
    void* arrayStart = effect + 0xb0;

    // Clear pointer +0xa8
    *(void**)(effect + 0xa8) = 0;

    // Check config flag 0x2000
    if ((*(uint*)(*(int*)(effect + 0x24) + 0x104) & 0x2000) != 0)
    {
        puVar17 = (uint*)(*(int*)(effect + 4) + 0xc);
        *puVar17 |= 0x800000;
        // Allocate extra array: 0x18 bytes per element
        void* extraArray = effect + arrayByteSize + 0xb0;
        arrayStart += countRounded * 0x18;
        *(void**)(effect + 0xa8) = extraArray;
    }

    type = *(char*)(effect + 0x5b);
    *(void**)(effect + 0xac) = 0;
    if ((type == 1) || (type == 2) || (type == 6))
    {
        // Allocate second extra array: 8 bytes per element
        void* secondArray = effect + arrayByteSize + 0xb0;
        arrayStart += countRounded * 8;
        *(void**)(effect + 0xac) = secondArray;
    }

    // Copy additional data from config
    *(float*)(effect + 0x34) = *(float*)(config + 0xec);
    *(float*)(effect + 0x38) = *(float*)(config + 0xf0);
    *(short*)(effect + 0x5c) = *(short*)(config + 0x11a);
    *(float*)(effect + 0x90) = *(float*)(config + 0xdc);
    *(float*)(effect + 0x94) = *(float*)(config + 0x17c);

    // Set flag based on some bit in TLS memory
    if ((*(byte*)(*(int*)(effect + 0x10) + *(int*)((int)(*(float**)unaff_FS_OFFSET) + 8)) & 0x10) != 0)
    {
        *(uint*)(effect + 0x2c) |= 0x800;
    }

    // Conditionally set flag based on config fields
    float fAcc = *(float*)(config + 0xac); // +0xac
    float fVal = *(float*)(config + 0xcc); // +0xcc
    if ((fAcc > 0.0f) && (fAcc != 0.0f) && (fVal > 0.0f))
    {
        *(uint*)(effect + 0x2c) |= 4;
    }
    else
    {
        if ((*(short*)(config + 0x118) < 1) && (*(float*)(config + 200) <= 0.0f))
        {
            puVar17 = (uint*)(*(int*)((int)(*(float**)unaff_FS_OFFSET) + 8) + *(int*)(effect + 0x10));
            *puVar17 |= 2;
        }
    }

    *(uint*)(effect + 0x44) = 0;
    float fTime = *(float*)(**(int**)unaff_FS_OFFSET); // get time from TLS (likely)

    // Call unknown init function
    if ((*(uint*)(*(int*)(effect + 0x24) + 0x10c) & 0x80000000) != 0)
    {
        FUN_0050d5e0();
    }

    // Calculate position offsets
    int baseAddr = *(int*)((int)fTime + 8);
    int offset = *(int*)(effect + 0x10);
    pfVar21 = (float*)(baseAddr + 0x40 + offset);
    fVar3 = pfVar21[1];
    fVar4 = pfVar21[2];
    fVar5 = pfVar21[3];
    fVar23 = *(float*)(baseAddr + 0x4c + offset);
    pfVar1 = (float*)(baseAddr + 0x40 + offset);

    float* configFloat = (float*)(config + 0x90); // +0x90,0x94,0x9c
    fVar6 = configFloat[0];
    fVar7 = configFloat[1];
    fVar8 = configFloat[2];
    pfVar1[0] = configFloat[0] + pfVar21[0];
    pfVar1[1] = fVar6 + fVar3;
    pfVar1[2] = fVar7 + fVar4;
    pfVar1[3] = fVar8 + fVar5;
    pfVar1[3] = fVar23; // Overwrite last? Looks like bug in decompiler; keep as is.

    FUN_00533fb0();

    // Copy transform data
    void* transformSrc = (void*)(*(int*)((int)fTime + 8) + 0x80 + *(int*)(effect + 0x10));
    *(uint*)(effect + 0x80) = *(uint*)transformSrc;
    *(uint*)(effect + 0x84) = *(uint*)(transformSrc + 0x4);
    *(uint*)(effect + 0x88) = *(uint*)(transformSrc + 0x8);
    *(uint*)(effect + 0x8c) = *(uint*)(transformSrc + 0xc);

    *(uint*)(effect + 0x2c) |= 8;
    *(uint*)(effect + 0x30) = 0;
    *(uint*)(effect + 0x50) = 0;
    *(uint*)(effect + 0x54) = 0;
    *(uint*)(effect + 0x3c) = 0;
    *(uint*)(effect + 0x40) = 0;
    *(uint*)(effect + 0x98) = 0;
    *(uint*)(effect + 0x9c) = DAT_00e2cd54;
    *(short*)(effect + 0x5e) = 0;
    *(short*)(effect + 0x76) = 0;
    *(short*)(effect + 0x74) = 0;

    int count = countRounded;
    void** particleArrayPtr = (void**)(effect + 0xb0);

    if ((*(uint*)(effect + 0x2c) & 0x200) == 0)
    {
        // Fill particle array with random values (2 floats per particle)
        if (DAT_0112509c != 0)
        {
            int i;
            for (i = 0; i < count; i++)
            {
                FUN_00513c70(&local18, &local14);
                if (local18 == 0)
                    break;
                *particleArrayPtr = local18;
                *(float*)(particleArrayPtr + 1) = local14;
                particleArrayPtr += 2; // each particle is 8 bytes (two pointers? Actually two floats)
            }
        }
    }
    else
    {
        // Alternate fill: compute offset from some base
        int base = ((int)arrayStart + 0xf) & 0xfffffff0;
        int offsetValue = base - *(int*)((int)fTime + 8); // maybe align to 16 bytes
        if (offsetValue < 0)
            offsetValue = 0;
        for (int i = 0; i < count; i++)
        {
            int srcAddr = 0;
            if (local18 != 0)
                srcAddr = *(int*)((int)fTime + 8) + (int)local18;
            srcAddr += i * 0x2a0; // stride 0x2a0
            int val = srcAddr;
            if (val != 0)
                val = srcAddr - *(int*)((int)fTime + 8);
            *(int*)particleArrayPtr = val;
            *(uint*)(particleArrayPtr + 1) = (srcAddr != 0) ? 1 : 0;
            particleArrayPtr += 2;
        }
    }

    // If config flag 0x1000, initialize 8 values per particle at offset +0x2c
    if ((*(uint*)(*(int*)(effect + 0x24) + 0x108) & 0x1000) != 0)
    {
        if (count > 0)
        {
            int* dataPtr = (int*)(effect + 0xb0);
            for (int i = 0; i < count; i++)
            {
                int* target = (int*)(*(int*)((int)fTime + 8) + *dataPtr + 0x2c);
                for (int j = 0; j < 8; j++)
                {
                    *target = DAT_00e44628;
                    target += 0x14; // stride 20 bytes
                }
                dataPtr += 2;
            }
        }
    }

    if (count == 0)
        return false;

    *(short*)(effect + 0x58) = (short)count;
    *(short*)(effect + 0x5c) = (short)(count * 8);

    // Additional logic for specific config flag and type
    if ((*(uint*)(*(int*)(effect + 0x24) + 0x108) & 0x100000) != 0)
    {
        type = *(char*)(effect + 0x5b);
        if (((type != 0) && (type != 3)) && (type != 5) && (type != 4))
        {
            return true;
        }

        if ((*(byte*)(*(int*)((int)fTime + 8) + *(int*)(effect + 0x10)) & 0x10) != 0)
        {
            return true;
        }

        float lifeTime = 0.0f;
        bool bVar12 = true;
        int maxIter = 1;

        FUN_00533fb0();

        float fAcc2 = *(float*)(config + 0xac);
        float fVal2 = *(float*)(config + 0xcc);
        if (fAcc2 > 0.0f)
        {
            if (fVal2 <= 0.0f)
            {
                if (*(short*)(config + 0x118) > 0)
                {
                    void* temp1 = DAT_00e2b1a4;
                    void* temp2 = DAT_00e2b1a4;
                    if ((*(uint*)(config + 0x10c) & 0x20000000) == 0)
                    {
                        FUN_00534350();
                    }
                    int config2 = *(int*)(effect + 0x24);
                    float fTemp = (float)temp1;
                    float fParticleCount = (float)*(short*)(config2 + 0x126);
                    float fOffset = (float)*(short*)(config2 + 0x124);
                    fVal2 = (fParticleCount + fOffset) * fTemp;
                    int iVal = (int)fVal2;
                    if (iVal == 0)
                        iVal = (int)*(short*)(config2 + 0x118);
                    else
                        iVal = (*(short*)(config2 + 0x118) + iVal - 1) / iVal;
                    maxIter = iVal;
                }
            }
            else
            {
                lifeTime = fVal2;
                bVar12 = false;
                maxIter = 1000;
            }
        }

        for (int iter = 0; iter < maxIter; iter++)
        {
            if ((*(float*)(config + 0xcc) > 0.0f) && (lifeTime <= DAT_00e2e210))
                break;
            FUN_0050d660(*(short*)(effect + 0x74), lifeTime, &local20);
            *(uint*)(effect + 0x3c) = 0;
            if (fVal2 <= 0.0f)
                break;
            if (!bVar12)
                lifeTime -= fVal2;
        }
    }

    *(uint*)(effect + 0x30) = 0;
    *(uint*)(effect + 0x3c) = 0;
    return true;
}