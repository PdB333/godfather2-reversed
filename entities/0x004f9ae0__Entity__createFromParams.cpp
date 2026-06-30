// FUNC_NAME: Entity::createFromParams
// Address: 0x004f9ae0
// This function initializes an Entity from a parameter block (EntityParams). 
// It sets up position, rotation, scale, attaches children, and resolves sound/effect hashes.

Entity* __thiscall Entity::createFromParams(Entity* this, int creationContext, EntityParams* params)
{
    char cVar1;
    int* piVar2;
    float* pfVar3;
    int iVar4;
    Entity* puVar5;
    int* piVar7;
    uint32_t uVar8;
    char* pcVar9;
    uint32_t uVar10;
    int iVar11;
    int iVar13;
    uint32_t* puVar14;
    double dVar15;
    float fVar16;
    uint64_t uVar17;
    uint32_t local_34;
    uint32_t local_30;
    uint32_t uStack_2c;
    uint32_t uStack_28;
    uint32_t uStack_24;

    // Call base class constructor (likely Entity base initializer)
    Entity::baseConstructor();

    // Set vtable pointer (class-specific)
    this->vtable = &gEntityVTable;

    // Initialize child/index fields
    this->childIndex1 = 0;      // +0x40
    this->childIndex2 = 0;      // +0x44

    // Get a pointer to the scene's placement/transform data
    piVar2 = (int*)getScenePlacementPointer(&local_30);
    iVar11 = *piVar2;
    this->childIndex1 = iVar11;
    this->childIndex2 = piVar2[1];   // +0x44

    // Check if we are in a creation context (flag at +0xd)
    if (*(char*)(creationContext + 0xd) == '\0') {
        if (iVar11 == 0) {
            iVar11 = this->childList;   // +0x10
            if (iVar11 != 0) {
                // Free child list using a memory pool allocator
                piVar2 = (int*)(gMemoryPool + 0x14);
                **(int**)(gMemoryPool + 0x14) = &gChildListFreeNode;   // +0x14
                *piVar2 = *piVar2 + 4;
                *(int*)*piVar2 = iVar11;
                *piVar2 = *piVar2 + 4;
                this->childList = 0;     // +0x10
                this->childCount = 0;    // +0x14
            }
            // Mark creation flag as done
            *(char*)(creationContext + 0xd) = 1;
            return this;
        }
    } else {
        if (iVar11 != 0) {
            // Clean up child allocation
            removeChildAllocation();    // FUN_004fbf00
        }
        if (*(char*)(creationContext + 0xd) != '\0') {
            return this;    // Already finalized
        }
    }

    // If we reach here, we need to continue initialization
    // Set a creation flag on the context (might be an error or abort flag)
    *(uint32_t*)(creationContext + 4) = *(uint32_t*)(creationContext + 4) | 0x80000000;

    piVar2 = (int*)(*(int*)(__readfsdword(0x2c)) + 8);   // Thread-local storage?
    this->paramsBlock = params;   // +0x3c

    // Compute position offset based on params
    pfVar3 = (float*)(this->childList + 0x40 + *piVar2);    // +0x50? Actually offset from childList
    if ((params->flags & 0x40) == 0) {
        *pfVar3 = (float)params->positionX;        // +0x90
        pfVar3[1] = (float)params->positionY;      // +0x94
        pfVar3[2] = (float)params->positionZ;      // +0x98
    } else {
        *pfVar3 = (float)params->positionX + *pfVar3;
        pfVar3[1] = (float)params->positionY + pfVar3[1];
        pfVar3[2] = (float)params->positionZ + pfVar3[2];
    }

    // Update physics state
    updatePhysics();        // FUN_00533fb0
    addChild();             // FUN_004ebb40
    addChild();             // FUN_004ebb40 (second call)

    // Set flags based on object type (maybe child count limit?)
    if (this->maxChildren1 != 2) {   // +0x150
        params->flags = params->flags & 0xfffffffe;
    }
    if (this->maxChildren2 != 2) {   // +0x158
        params->flags = params->flags & 0xfffffffd;
    }

    fVar16 = gDefaultScale;          // DAT_00e2b1a4
    this->objectType = params->objectType;   // +0x38 (param_3[0x22])

    if ((float)params->scale == 0.0f) {
        this->scaleValue = fVar16;   // +0x48
    } else {
        dVar15 = (double)((float)params->scale * gScaleMultiplier);   // DAT_00e445c8
        fun_00b99e20();      // unknown math function
        fVar16 = gDefaultScale;
        this->scaleValue = (float)dVar15;   // +0x48
    }

    // Initialize array of 7 floats (maybe component scaling factors)
    this->componentScale0 = 0;   // +0x160
    this->componentScale1 = 0;   // +0x164
    this->componentScale2 = 0;   // +0x168
    pfVar3 = &this->componentScaleArray;   // +0x5c
    iVar11 = 7;
    do {
        *pfVar3 = fVar16;
        pfVar3 = pfVar3 + 4;    // each float is 4 bytes, but we increment pointer by 4 floats? Actually pfVar3++ would be 4 bytes. So this writes consecutive floats.
        iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    // This sets 7 floats starting at componentScaleArray, each 4 bytes apart? Actually pfVar3 is float*, so pfVar3++ increments by 4 bytes. It runs 7 times, so writes to indices 0,1,2,3,4,5,6. But the pointer advances by 1 each time, meaning each write is to the next float. So it initializes an array of 7 floats.

    // Set rotation matrix (or orientation) based on params
    if ((float)params->rotation == 0.0f) {
        // Use default rotation from static data
        puVar5 = &gDefaultRotation;   // DAT_00e2dba4
        puVar12 = &this->rotationMatrix;   // +0xc4
        do {
            puVar6 = puVar5 + 2;
            puVar12[-1] = puVar5[-1];
            *puVar12 = *puVar5;
            puVar12[1] = puVar5[-1];
            puVar12[2] = *puVar5;
            puVar5 = puVar6;
            puVar12 = puVar12 + 4;
        } while ((int)puVar6 < 0xe2dbdc);    // This loop copies a 4x4 matrix? It runs 8 iterations (0xe2dbdc - 0xe2dba4 = 56 bytes / 8 = 7? Actually the condition checks the address of puVar6, which is incremented by 8 each iteration. So it copies 8 blocks of 4 words? That seems like a 4x4 matrix of float? But the copying pattern is weird (copy from puVar5[-1] and puVar5[0] to adjacent locations). Might be constructing a rotation matrix from two vectors.
    } else {
        // Build rotation from scaled parameters
        iVar11 = 0;
        puVar5 = &this->rotationMatrix;
        do {
            iVar4 = iVar11 + 8;
            puVar5[-1] = *(uint32_t*)((int)&gRotationData0 + iVar11);   // DAT_00e2dbd8
            *puVar5 = *(uint32_t*)((int)&gRotationData1 + iVar11);      // DAT_00e2dbdc
            puVar5[1] = *(uint32_t*)((int)&gRotationData2 + iVar11);    // DAT_00e2dba0
            puVar5[2] = *(uint32_t*)((int)&gRotationData3 + iVar11);    // DAT_00e2dba4
            iVar11 = iVar4;
            puVar5 = puVar5 + 4;
        } while (iVar4 < 0x38);    // 56 bytes total (0x38 = 56) => 14 floats => 3.5 vectors? But each iteration copies 4 words = 16 bytes, so 56/16 = 3.5 iterations? Actually iVar4 < 0x38 and iVar4 increments by 8, so it runs 56/8 = 7 times. But each iteration copies 4 words, so 28 words = 112 bytes? That seems too large. I'm likely misunderstanding the pointer arithmetic.
        // This likely copies 7 rows of a 4x4 matrix (7 * 16 = 112 bytes).
    }

    // Set uniform scaling for some bounding box or other values
    this->uniformScale0 = 0x3f000000;   // 0.5f   +0x130
    this->uniformScale1 = 0x3f000000;   // 0.5f   +0x134
    this->uniformScale2 = 0x3f000000;   // 0.5f   +0x138
    this->uniformScale3 = 0x3f000000;   // 0.5f   +0x13c
    this->uniformScale4 = 0x3f000000;   // 0.5f   +0x140
    this->uniformScale5 = 0x3f000000;   // 0.5f   +0x144
    this->uniformScale6 = 0x3f000000;   // 0.5f   +0x148

    // Copy additional placement data
    puVar5 = (uint32_t*)(this->childList + 0x80 + *piVar2);
    local_30 = *puVar5;
    uStack_2c = puVar5[1];
    uStack_28 = puVar5[2];
    uStack_24 = puVar5[3];

    // Copy world position and orientation from params
    this->worldPosX = params->worldPosX;   // +0x28
    this->worldPosY = params->worldPosY;   // +0x2c
    uVar8 = params->worldPosZ;              // +0x30
    this->worldOrientation = this->parentOrientation;   // +0x34? Actually param_1[0xd] = param_1[1]
    this->worldPosZ = uVar8;                // +0x30

    // Check if child index is valid (collision? bounding box?)
    cVar1 = checkChildIndexValidity(gGlobalEntityManager, *piVar2 + this->childIndex1);
    if (cVar1 == '\0') {
        *(char*)(creationContext + 0xc) = 1;   // Mark as invalid
        return this;
    }

    // Iterate over children and initialize them
    iVar11 = *piVar2;
    iVar4 = 0;
    if (0 < *(int*)(iVar11 + 0x58 + this->childIndex1)) {
        do {
            iVar13 = *(int*)(iVar11 + 8 + iVar4 * 8 + this->childIndex1);
            if (iVar13 != 0) {
                iVar11 = iVar11 + iVar13;
                iVar13 = *(int*)(iVar11 + 0x10);
                if (iVar13 < 1) {
                    iVar13 = params->entityType;   // +0x8c
                } else if (*(float*)(*(int*)(iVar11 + 0x24) + 0x3c) == gDefaultScale) continue;
                if (0 < iVar13) {
                    createChildEntity(iVar13);   // FUN_00519450
                }
            }
            iVar11 = *piVar2;
            iVar4 = iVar4 + 1;
        } while (iVar4 < *(int*)(iVar11 + 0x58 + this->childIndex1));
    }

    // Handle optional script/behavior attachment (params[4..7])
    if ((params->scriptOrEffectFlags & 0xF) == 0) {
        this->attachedScript = 0;   // +0x16c
    } else {
        local_30 = *(uint32_t*)(this->parent + 0x84);   // Parent's script ID
        local_34 = 0;
        if (((params->scriptOrEffectFlags & 0xF) == 0) ||
           ((piVar7 = (int*)getSomeManager(), piVar7 == (int*)0x0 || (iVar11 = *piVar7, iVar11 == 0))))
        {
            iVar11 = 0;
        } else {
            uVar17 = getScriptHash();   // FUN_0051d730
            iVar11 = findScriptAsset(iVar11, local_30, 0, &local_34, uVar17);   // FUN_0051c7c0
        }
        this->attachedScript = iVar11;
        if (iVar11 != 0) {
            *(uint32_t**)(iVar11 + 8) = &this->attachedScript;   // Self-referencing linked list
        }
    }

    // Resolve sound/effect IDs from string hashes (params[8..11])
    if ((params->soundGroupFlags & 0xF) != 0) {
        if ((params->soundGroupFlags & 0xF) == 0) {
            uVar8 = 0;
        } else {
            stringCopy(params->soundName, &local_30);   // FUN_004eaec0
            pcVar9 = (char*)&local_30;
            do {
                cVar1 = *pcVar9;
                pcVar9 = pcVar9 + 1;
            } while (cVar1 != '\0');
            uVar10 = hashString(0, &local_30, (int)pcVar9 - ((int)&local_30 + 1));   // FUN_00ab8560
            puVar14 = *(uint32_t**)(*(int*)(gHashTable + 0x80c) + (uVar10 % *(uint32_t*)(gHashTable + 0x808)) * 4);
            if (puVar14 == (uint32_t*)0x0) {
                uVar8 = 0xffffffff;
            } else {
                do {
                    if (*puVar14 == uVar10) {
                        if ((uint32_t*)puVar14[1] == (uint32_t*)0x0) goto LAB_004f9f6f;
                        uVar8 = *(uint32_t*)puVar14[1];
                        break;
                    }
                    puVar14 = (uint32_t*)puVar14[2];
                } while (puVar14 != (uint32_t*)0x0);
                if (puVar14 == (uint32_t*)0x0) uVar8 = 0xffffffff;
            }
        }
        // Store resolved sound ID at child index offset
        *(uint32_t*)(*piVar2 + 0xac + this->childIndex1) = uVar8;
        uVar10 = *(uint32_t*)(*piVar2 + 0xac + this->childIndex1);
        if ((uVar10 != 0) && (uVar10 != 0xffffffff) && (uVar10 < 0x1000) &&
            (uVar10 * 0x38 != 0xEEE0D8) && (piVar7 = *(int**)(&gSoundHashArray + uVar10 * 0x38), piVar7 != (int*)0x0))
        {
            *piVar7 = *piVar7 + 1;
        }
    }

    // Resolve effect IDs from string hashes (params[12..15])
    if ((params->effectGroupFlags & 0xF) != 0) {
        if ((params->effectGroupFlags & 0xF) == 0) {
            uVar8 = 0;
        } else {
            stringCopy(params->effectName, &local_30);
            pcVar9 = (char*)&local_30;
            do {
                cVar1 = *pcVar9;
                pcVar9 = pcVar9 + 1;
            } while (cVar1 != '\0');
            uVar10 = hashString(0, &local_30, (int)pcVar9 - ((int)&local_30 + 1));
            puVar14 = *(uint32_t**)(*(int*)(gHashTable + 0x80c) + (uVar10 % *(uint32_t*)(gHashTable + 0x808)) * 4);
            if (puVar14 == (uint32_t*)0x0) {
                uVar8 = 0xffffffff;
            } else {
                do {
                    if (*puVar14 == uVar10) {
                        if ((uint32_t*)puVar14[1] == (uint32_t*)0x0) goto LAB_004fa057;
                        uVar8 = *(uint32_t*)puVar14[1];
                        break;
                    }
                    puVar14 = (uint32_t*)puVar14[2];
                } while (puVar14 != (uint32_t*)0x0);
                if (puVar14 == (uint32_t*)0x0) uVar8 = 0xffffffff;
            }
        }
        *(uint32_t*)(*piVar2 + 0xb0 + this->childIndex1) = uVar8;
        uVar10 = *(uint32_t*)(*piVar2 + 0xb0 + this->childIndex1);
        if ((uVar10 != 0) && (uVar10 != 0xffffffff) && (uVar10 < 0x1000) &&
            (uVar10 * 0x38 != 0xEEE0D8) && (piVar2 = *(int**)(&gSoundHashArray + uVar10 * 0x38), piVar2 != (int*)0x0))
        {
            *piVar2 = *piVar2 + 1;
        }
    }

    return this;
}