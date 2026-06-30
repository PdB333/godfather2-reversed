// FUNC_NAME: VFX::render
// Address: 0x005cc6b0
// This function appears to render a visual effect (e.g., sprite, decal) with transformation, fog, and color modulation.
// It pushes render state, transforms a point using the object's matrix, computes fog/color parameters, and calls the draw primitive.

void __thiscall VFX::render(void *this, int renderTargetIdx, int renderPass)
{
    float fVar1;
    float fVar2;
    float fVar3;
    int iVar4;
    char cVar5;
    int *piVar6;
    int iVar7;
    int *piVar8;
    uint uVar9;
    undefined4 uVar10;
    undefined4 uVar11;
    undefined4 uVar12;
    bool bVar13;
    float fVar14;
    float fVar15;
    undefined1 *puVar16;
    float *pfVar17;
    undefined4 *puVar18;
    // Stack variables for transformed coordinates and color
    undefined4 local_f8;
    uint local_f4;
    float local_f0;
    float fStack_ec;
    float fStack_e8;
    float fStack_e4;
    int local_d4;
    float local_d0;
    undefined1 local_cc;
    undefined1 local_cb;
    undefined1 local_ca;
    undefined1 local_c9;
    float local_c8;
    float local_c4;
    float local_c0;
    float fStack_bc;
    float fStack_b8;
    float fStack_b4;
    float local_b0;
    float local_ac;
    undefined **local_a8;
    undefined4 local_a4;
    code *local_a0;
    undefined1 local_9c;
    undefined1 local_9b;
    undefined4 local_98;
    float local_94;
    float local_90;
    float fStack_8c;
    float fStack_88;
    float fStack_84;
    float local_80;
    float fStack_7c;
    float fStack_78;
    float fStack_74;
    float local_70;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    float local_60;
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    undefined4 local_3c;

    // Push render state stack
    Engine::pushRenderStateStack();
    // Setup vtable (likely for render context)
    *(*renderStackPtr + 0x14) = &PTR_LAB_01126dc0; // static vtable
    *(*renderStackPtr + 0x14) += 4;

    Engine::pushWorldMatrix(renderTargetIdx, renderPass);

    // Read packed color from object (offset +0x54)
    local_d4 = *(int *)(this + 0x54); // color (RGBA packed as int)

    Engine::pushProjectionMatrix();

    iVar4 = DAT_0122349c; // global render state
    local_a4 = *(undefined4 *)(DAT_012234f0 + 0x20); // camera/projection data

    // Convert color int to float (byte-swapped to match engine format)
    local_f8._0_2_ = CONCAT11((char)((uint)local_d4 >> 0x10),(char)((uint)local_d4 >> 0x18));
    local_f8 = (float)CONCAT22(CONCAT11((char)local_d4,(char)((uint)local_d4 >> 8)), (undefined2)local_f8);

    local_f4 = DAT_0122349c;
    local_a8 = &PTR_FUN_00e33814; // function table for draw
    local_a0 = FUN_005bccb0; // likely a callback
    local_9c = 1;
    local_9b = 0;

    Engine::pushColor(&local_f8); // push color to stack

    // Bind texture/shader (offset +0x84 is resource ID)
    iVar7 = *(int *)(this + 0x84);
    if (DAT_01163d94 != 0) {
        iVar7 = DAT_01163d94; // override texture
    }

    piVar6 = (int *)(iVar4 + 0x1c); // some resource table
    cVar5 = Engine::checkResourceLoaded(piVar6, iVar7);
    if (cVar5 != '\0') {
        // Push additional state if resource exists
        iVar4 = *piVar6;
        piVar8 = (int *)(renderStackPtr + 0x14);
        *(*renderStackPtr + 0x14) = &PTR_LAB_01123c4c;
        *piVar8 += 4;
        *(int *)*piVar8 = iVar4;
        *piVar8 += 4;
    }

    Engine::bindTexture(*(int *)(this + 0x84));

    // Global constants for fog/effect
    local_98 = DAT_0119da60; // maybe fog color multiplier
    local_94 = DAT_0119da64; // fog density or enable flag
    local_d4 = 0;

    if (DAT_0119da64 == 0.0f) {
        // No fog (or simple mode)
        Engine::popMatrix(); // get current matrix (this+0x24 is object matrix)
        Engine::popMatrix(); // get projection matrix (stored in globals)

        // Extract object matrix rows (offset +0x24 to +0x30 are probably row0 and row1)
        fVar14 = *(float *)(this + 0x24); // matrix row0.x?
        fVar1 = *(float *)(this + 0x2c); // matrix row1.z?
        fVar2 = *(float *)(this + 0x28); // matrix row0.z?
        fVar3 = *(float *)(this + 0x30); // matrix row1.w? (maybe translation)

        // Transform local origin using matrix and constant globals
        // local_80, local_90, local_70, local_60 are from projection matrix
        local_f0 = fVar2 * local_80 + fVar14 * local_90 + 0.0f * local_70 + DAT_00e2b1a4 * local_60;
        fStack_ec = fVar2 * fStack_7c + fVar14 * fStack_8c + 0.0f * fStack_6c + DAT_00e2b1a4 * fStack_5c;
        fStack_e8 = fVar2 * fStack_78 + fVar14 * fStack_88 + 0.0f * fStack_68 + DAT_00e2b1a4 * fStack_58;
        fStack_e4 = fVar2 * fStack_74 + fVar14 * fStack_84 + 0.0f * fStack_64 + DAT_00e2b1a4 * fStack_54;

        // Another transform with different matrix rows
        local_c0 = fVar3 * local_80 + fVar1 * local_90 + 0.0f * local_70 + DAT_00e2b1a4 * local_60;
        fStack_bc = fVar3 * fStack_7c + fVar1 * fStack_8c + 0.0f * fStack_6c + DAT_00e2b1a4 * fStack_5c;
        fStack_b8 = fVar3 * fStack_78 + fVar1 * fStack_88 + 0.0f * fStack_68 + DAT_00e2b1a4 * fStack_58;
        fStack_b4 = fVar3 * fStack_74 + fVar1 * fStack_84 + 0.0f * fStack_64 + DAT_00e2b1a4 * fStack_54;

        // Read scaling factor (offset +0x70)
        local_b0 = *(float *)(this + 0x70); // e.g., object scale or particle size

        // Compute differences (world-space direction vector)
        local_f8 = local_c0 - local_f0;
        local_c8 = fStack_ec - fStack_bc;

        // Apply fog scaling if resource is loaded
        if (*piVar6 != 0) {
            fVar15 = (float)*(int *)(*piVar6 + 0x18) * *(float *)(local_f4 + 0x2c); // fog density * time
        }
        // Compute depth-based fog factor
        local_d0 = ((float)((uint)fStack_7c & 0x7FFFFFFF) / fVar15) * local_b0; // fabs of z?
    }
    else {
        // Fog enabled mode
        local_d4 = 1;
        Engine::popMatrix();
        fVar14 = *(float *)(this + 0x24);
        fVar1 = *(float *)(this + 0x2c);
        fVar2 = *(float *)(this + 0x28);
        fVar3 = *(float *)(this + 0x30);

        // Compute first set of transformed coordinates (similar to above)
        local_f0 = fVar2 * local_80 + fVar14 * local_90 + 0.0f * local_70 + DAT_00e2b1a4 * local_60;
        fStack_ec = fVar2 * fStack_7c + fVar14 * fStack_8c + 0.0f * fStack_6c + DAT_00e2b1a4 * fStack_5c;
        fStack_e8 = fVar2 * fStack_78 + fVar14 * fStack_88 + 0.0f * fStack_68 + DAT_00e2b1a4 * fStack_58;
        fStack_e4 = fVar2 * fStack_74 + fVar14 * fStack_84 + 0.0f * fStack_64 + DAT_00e2b1a4 * fStack_54;

        local_b0 = *(float *)(this + 0x70); // scale

        // Second transform
        local_c0 = fVar3 * local_80 + fVar1 * local_90 + 0.0f * local_70 + DAT_00e2b1a4 * local_60;
        fStack_bc = fVar3 * fStack_7c + fVar1 * fStack_8c + 0.0f * fStack_6c + DAT_00e2b1a4 * fStack_5c;
        fStack_b8 = fVar3 * fStack_78 + fVar1 * fStack_88 + 0.0f * fStack_68 + DAT_00e2b1a4 * fStack_58;
        fStack_b4 = fVar3 * fStack_74 + fVar1 * fStack_84 + 0.0f * fStack_64 + DAT_00e2b1a4 * fStack_54;

        // Compute differences
        local_f8 = local_c0 - local_f0;
        local_c8 = fStack_ec - fStack_bc;

        // Absolute value for fog depth
        local_c4 = (float)((uint)fStack_7c & 0x7FFFFFFF);
        fVar14 = 0.0f;
        if (*piVar6 != 0) {
            fVar14 = (float)*(int *)(*piVar6 + 0x18) * *(float *)(local_f4 + 0x2c); // fog density
        }
        local_d0 = (local_c4 / fVar14) * local_b0;

        // Additional transformations for fog computation
        Engine::popMatrix();
        Engine::popMatrix();
        fVar14 = *(float *)(this + 0x24);
        fVar1 = *(float *)(this + 0x28);
        local_f0 = fVar1 * local_80 + fVar14 * local_90 + 0.0f * local_70 + DAT_00e2b1a4 * local_60;
        fStack_ec = fVar1 * fStack_7c + fVar14 * fStack_8c + 0.0f * fStack_6c + DAT_00e2b1a4 * fStack_5c;
        fStack_e8 = fVar1 * fStack_78 + fVar14 * fStack_88 + 0.0f * fStack_68 + DAT_00e2b1a4 * fStack_58;
        fStack_e4 = fVar1 * fStack_74 + fVar14 * fStack_84 + 0.0f * fStack_64 + DAT_00e2b1a4 * fStack_54;
        fStack_bc = DAT_00e2b1a4 - fStack_ec; // 1.0 - something
        fStack_7c = local_c4; // store absolute z
        local_c0 = local_f0;
    }

    // Look up per-texture fog override
    uVar9 = 0;
    fVar15 = DAT_00e2b1a4; // default 1.0
    if (DAT_01205430 != 0) {
        do {
            if ((&DAT_01163d40)[uVar9 * 2] == *(int *)(this + 0x84)) {
                fVar15 = *(float *)(&DAT_01163d44 + uVar9 * 8); // fog override factor
                break;
            }
            uVar9++;
        } while (uVar9 < DAT_01205430);
    }

    local_d0 = fVar15 * local_d0; // apply fog scale

    // Get render context info
    Engine::getRenderState();
    uVar10 = Engine::getPassID(); // e.g., diffuse, specular
    uVar9 = *(uint *)(this + 0x80); // flags (offset +0x80)

    // Determine blend/lighting mode from flags (bit 4 = emissive, bit 3 = some)
    uVar12 = 0;
    if ((uVar9 & 0x10) == 0) {
        if ((uVar9 & 8) != 0) {
            uVar12 = 2;
        }
    }
    else {
        uVar12 = 1; // emissive
    }

    // Material type from offset +0x34
    if (*(int *)(this + 0x34) == 1) {
        uVar11 = 2;
    }
    else if (*(int *)(this + 0x34) == 2) {
        uVar11 = 1;
    }
    else {
        uVar11 = 0;
    }

    bVar13 = (uVar9 & 0x80) != 0; // use vertex color flag
    // Modify flag value
    local_f4 = CONCAT31(local_f4._1_3_,~(byte)(uVar9 >> 0x15)) & 0xffffff01;
    local_c4 = (float)CONCAT31(local_c4._1_3_,bVar13);

    if ((bVar13) || ((uVar9 & 1) != 0)) {
        // Compute color scaling factors
        local_ac = (float)((uint)fStack_7c & 0x7FFFFFFF) * local_b0 * DAT_00e44980; // scale by absolute z and object scale
        // Set RGBA color (solid white? local_cc=0,0,0,0xff means alpha=255, color=0? Actually 0,0,0,0xff is opaque white when interpreted as BGRA? Engine likely uses ARGB or RGBA)
        local_cc = 0;
        local_cb = 0;
        local_ca = 0;
        local_c9 = 0xff; // alpha

        if (local_d4 == 0) {
            puVar18 = (undefined4 *)0x0;
            pfVar17 = (float *)0x0; // no fog color
        }
        else {
            puVar18 = &local_98; // fog color multiplier
            pfVar17 = &local_c0; // fog depth
        }
        puVar16 = &local_cc; // pointer to RGBA
        fVar15 = local_c4; // bool flag as float?
        local_b0 = (float)((uint)local_90 & 0x7FFFFFFF) * local_b0 * DAT_00e44980; // another scale
    }
    else {
        // No vertex color
        if (local_d4 == 0) {
            puVar18 = (undefined4 *)0x0;
            pfVar17 = (float *)0x0;
        }
        else {
            puVar18 = &local_98;
            pfVar17 = &local_c0;
        }
        puVar16 = (undefined1 *)0x0; // no color override
        fVar15 = 0.0f;
    }

    // Draw primitive: likely a quad or textured sprite
    // Parameters: vtable, position (local_f0, fStack_ec), direction (local_f8, local_c8) or size, fog scale (local_d0),
    //             texture pass ID, material type, blend mode, fog factor, color ptr, additional data (fog color, position, flags)
    Engine::drawQuad(&local_a8,
                     local_f0, fStack_ec, // x,y?
                     local_f8, local_c8,  // width, height? or uv?
                     local_d0,            // depth/fog
                     uVar10,              // pass ID
                     uVar11,              // material type
                     uVar12,              // blend mode
                     fVar15,              // fog factor
                     puVar16,             // color (RGBA)
                     pfVar17,             // fog position
                     puVar18,             // fog color
                     local_f4);           // flags

    // Pop matrix stack
    Engine::popWorldMatrix();

    // Restore vtable
    *(*renderStackPtr + 0x14) = &PTR_LAB_01126dc0;
    *(*renderStackPtr + 0x14) += 4;

    // Call cleanup method (via vtable)
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(local_3c, 0); // likely a destructor or state restore

    // Store debug fog value if enabled
    if (((char)local_a4 != '\0') && (local_a4._1_1_ != '\0')) {
        *(*renderStackPtr + 0x14) = &PTR_LAB_01123d3c;
        *(*renderStackPtr + 0x14) += 4;
        *(float *)*(*renderStackPtr + 0x14) = local_ac; // store computed fog value
        *(*renderStackPtr + 0x14) += 4;
    }

    return;
}