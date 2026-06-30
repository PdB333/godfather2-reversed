// FUNC_NAME: PhysicsComponent::applyConstraintForces
void PhysicsComponent::applyConstraintForces(void* context)
{
    int iVar1;
    int* piVar2;
    char cVar3;
    uint extraout_EDX;
    uint uVar4;
    uint* puVar5;
    // unaff_ESI is 'this'
    // unaff_FS_OFFSET is thread-local storage
    float fVar6, fVar7, fVar8, fVar9, fVar10, fVar11, fVar12, fVar13, fVar14, fVar15;
    int local_8c;
    float local_88;
    int local_84;
    float local_80;
    float diffX, diffY, diffZ;  // fStack_7c, fStack_78
    float baseVecX, baseVecY, baseVecZ; // local_70, fStack_6c, fStack_68, fStack_64
    float local_60[3]; // local_60, fStack_5c, fStack_58
    float matrix[4]; // local_50, uStack_4c, uStack_48, uStack_44 (actually 4 floats)
    float vec1[3]; // from context+0x50 (fVar12,fVar13,fVar14)
    float vec2[3]; // from context+0x70 (fVar9,fVar10,fVar11)
    float vec3[3]; // from context+0x60 (local_30,fStack_2c,fStack_28)
    float pad; // uStack_34, uStack_24

    // Check if this component is active (bitmask at +0xc)
    if ((*(uint*)(this + 0x0c) & 0x20340000) != 0) {
        return;
    }

    iVar1 = *(int*)(this + 0x10);
    uVar4 = *(uint*)(iVar1 + 0x14);

    local_88 = 0.0f;
    fVar15 = 0.0f;
    baseVecX = 0.0f; // local_70
    baseVecY = 0.0f; // fStack_6c
    baseVecZ = 0.0f; // fStack_68
    fVar9 = 0.0f;    // fStack_64? Actually used as fVar9

    if ((uVar4 & 0x2c00000) != 0) {
        // Read transformation from context (presumably a matrix + translation)
        matrix[0] = *(float*)(context + 0x40);
        matrix[1] = *(float*)(context + 0x44);
        matrix[2] = *(float*)(context + 0x48);
        matrix[3] = *(float*)(context + 0x4c);
        vec1[0] = *(float*)(context + 0x50);
        vec1[1] = *(float*)(context + 0x54);
        vec1[2] = *(float*)(context + 0x58);
        pad = *(float*)(context + 0x5c); // likely unused
        vec2[0] = *(float*)(context + 0x70);
        vec2[1] = *(float*)(context + 0x74);
        vec2[2] = *(float*)(context + 0x78);
        vec3[0] = *(float*)(context + 0x60);
        vec3[1] = *(float*)(context + 0x64);
        vec3[2] = *(float*)(context + 0x68);
        pad = *(float*)(context + 0x6c); // likely unused

        // Determine target position (anchor point)
        if (*(int*)(this + 0xbc) == 0) {
            fVar6 = *(float*)(this + 0x60);
            fVar7 = *(float*)(this + 0x64);
            fVar8 = *(float*)(this + 0x68);
        } else {
            // Transform local position to world using matrix at this+0x30
            FUN_0056b420(this + 0x30, *(int*)(this + 0xbc), local_60);
            uVar4 = extraout_EDX; // save updated flags
            fVar6 = local_60[0];
            fVar7 = local_60[1];
            fVar8 = local_60[2];
        }

        // Compute displacement from target to vec2
        diffX = fVar6 - vec2[0];
        diffY = fVar7 - vec2[1];
        diffZ = fVar8 - vec2[2];

        if ((uVar4 & 0x2800000) == 0) {
            // Dot product of displacement with vec1, scaled by a global constant
            fVar15 = (vec1[0] * diffX + vec1[1] * diffY + vec1[2] * diffZ) * DAT_00e44718;
            // Scale vec1 by fVar15 to get force direction
            baseVecX = fVar15 * vec1[0];
            baseVecY = fVar15 * vec1[1];
            baseVecZ = fVar15 * vec1[2];
        } else {
            // Alternative: use vec3 for comparison
            local_88 = vec3[0] * diffX + vec3[1] * diffY + vec3[2] * diffZ;
            // Reset baseVec to vec1? Actually it uses local_70 etc. which are uninitialized? Wait, local_70 was set to 0 earlier, but here we set to vec1? The code: fVar12 = local_70; fVar13 = fStack_6c; fVar14 = fStack_68; and later after else branch, it sets fVar12 = local_70 etc. So baseVec is vec1 initially? Actually the code before else branch: fVar12 = local_70; fVar13 = fStack_6c; fVar14 = fStack_68; fVar9 = fStack_64; and then in else: local_88 = ...; fVar12 = local_70; fVar13 = fStack_6c; fVar14 = fStack_68; So it's reading back the old values (which are from local_70 etc., which were set to 0). So this branch seems to reset baseVec to zero? But then there is an inner condition with 0x800000.

            if ((uVar4 & 0x800000) != 0) {
                fVar10 = *(float*)(iVar1 + 0x24);
                if (fVar10 < local_88) {
                    FUN_0045c110((fVar10 - local_88) / local_88, &local_80, &local_70);
                    // result in local_70, fStack_6c, fStack_68, fStack_64
                    baseVecX = local_70; // but careful: these are the output of FUN_0045c110
                    baseVecY = fStack_6c;
                    baseVecZ = fStack_68;
                    fVar9 = fStack_64;
                }
            }
        }
    }

    // Assemble base vector components (these might be used later)
    // The decompiled code stores them back to local variables
    fStack_64 = fVar9;
    fStack_68 = baseVecZ;
    fStack_6c = baseVecY;
    local_70 = baseVecX;

    // Loop over attachments/children
    local_84 = 0;
    if (0 < *(short*)(this + 0x80)) {
        local_8c = 0;
        puVar5 = (uint*)(this + 0xf0); // start of array of 5-uint structures
        do {
            piVar2 = (int*)puVar5[1]; // child object pointer
            if (piVar2 != nullptr &&
                ((*puVar5 & 0x4000000) == 0) && // check skip flag
                ((*(uint*)(*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8) + piVar2[4]) & 0x20000000) == 0) && // some global filter
                ((*(uint*)(piVar2[1] + 0x0c) & 0x20300000) == 0)) // child's active flag
            {
                if ((*(uint*)(*(int*)(piVar2[1] + 0x10) + 0x14) & 0x404040) != 0) {
                    FUN_00533fb0(); // unknown, maybe reset constraint
                }
                if ((*(uint*)(*(int*)(this + 0x10) + 0x14) & 0xc00000) != 0) {
                    FUN_0051a0e0(piVar2, &local_70); // apply force based on base vector
                }
                if ((*puVar5 & 8) != 0) {
                    // Scale displacement by a factor from some table
                    float scale = *(float*)(local_8c + 0x40 + *(int*)(this + 0x10)) / local_88;
                    local_60[0] = scale * diffX;
                    local_60[1] = scale * diffY;
                    local_60[2] = scale * diffZ;
                    FUN_0051a0e0(piVar2, local_60); // apply scaled force
                }
                // Check if child has a "callable" (vtable entry at +0xc) and it returns true
                if (((~*(byte*)(puVar5[2] + 0x0c) & 1) != 0) &&
                    (cVar3 = (**(code**)(*piVar2 + 0x0c))(), cVar3 != '\0')) {
                    (**(code**)(*piVar2 + 0x10))(context); // call child's method with context
                }
            }
            local_8c += 0x24; // stride of 36 bytes? Actually puVar5 increments by 5*4 = 20, so each structure is 20 bytes? But local_8c used as offset into a table? Looks like local_8c is an index * 0x24 but puVar5 increments by 5 (20 bytes)? That is suspicious. Likely Ghidra misinterpretation; we'll keep the increment as given.
            local_84++;
            puVar5 += 5; // each entry is 5 uint32
        } while (local_84 < *(short*)(this + 0x80));
    }
    return;
}