// FUNC_NAME: BatchRenderer::submitQuad

void BatchRenderer::submitQuad(float* vertexPositions, float* vertexColorsOrNormals, undefined4* extraVertexData) {
    float fVar1, fVar2, fVar3, fVar4, fVar5;
    float fVar13;
    int iVar9;
    uint uVar11;
    undefined4 local_4;

    // +0x011f4234: initialization flag
    if (DAT_011f4234 == 0) {
        // +0x00f15990: profiler start
        FUN_00612210(&DAT_00f15990);
    }

    if (extraVertexData == NULL) {
        // +0x00612a60: setup default vertex buffer size/stride?
        FUN_00612a60();
        local_4 = 0x10; // vertex stride: 16 bytes (3 floats pos + 4 bytes color)
    } else {
        // check material type index
        // +0x011f4230: current material type index
        if ((DAT_011f4230 < 0x1000) && (DAT_011f4230 * 0x38 != -0x11a0f28)) {
            // +0x011a0f30: array of material types, size 0x38 per entry
            int materialType = *(int*)(&DAT_011a0f30 + DAT_011f4230 * 0x38);
            if (materialType == 9) {
                DAT_01127774 = DAT_01127878; // material pointer for type 9
                // +0x0060a580: get parameter "lodBias" from material
                DAT_01127868 = FUN_0060a580(DAT_01127878, "lodBias");
                if (DAT_012058e8 == &PTR_PTR_01127760) {
                    // +0x0060a460: apply material? // +0x0060aa90: set shader lodBias
                    FUN_0060a460(DAT_01127774);
                    FUN_0060aa90(DAT_01127774, DAT_01127868, DAT_01127840);
                }
                // +0x00619950: additional setup for type 9?
                FUN_00619950();
            } else if (materialType == 8) {
                DAT_01127774 = DAT_01127884; // material for type 8
                DAT_01127868 = FUN_0060a580(DAT_01127884, "lodBias");
                if (DAT_012058e8 == &PTR_PTR_01127760) {
                    FUN_0060a460(DAT_01127774);
                    FUN_0060aa90(DAT_01127774, DAT_01127868, DAT_01127840);
                }
            } else {
                DAT_01127774 = DAT_01127874; // default material
                DAT_01127868 = FUN_0060a580(DAT_01127874, "lodBias");
                if (DAT_012058e8 == &PTR_PTR_01127760) {
                    FUN_0060a460(DAT_01127774);
                    FUN_0060aa90(DAT_01127774, DAT_01127868, DAT_01127840);
                }
                // +0x00619900: additional setup for other types?
                FUN_00619900();
            }
        }
        // +0x00619650: setup for extra vertex data (UV or other)
        FUN_00619650();
        local_4 = 0x18; // vertex stride: 24 bytes (3 floats pos + 4 bytes color + 2 floats extra)
    }

    // global color components (RGBA) and alpha multiplier
    fVar5 = DAT_011f422c; // color A
    fVar4 = DAT_011f4228; // color B
    fVar3 = DAT_011f4224; // color G
    fVar2 = DAT_011f4220; // color R
    fVar1 = DAT_00e448b8; // global alpha/intensity multiplier

    // fill vertex buffer at DAT_011f4240
    // loop 4 times (quad)
    undefined4* puVar8 = (undefined4*)(vertexPositions + 2); // +8 bytes from start of positions array? Actually puVar8 = param_1 + 8
    float* pfVar10 = (float*)(vertexColorsOrNormals + 3); // +12 bytes from start of color/normal array
    int iVar9 = 4;
    undefined4* puVar6 = &DAT_011f4240;
    undefined4* puVar12 = extraVertexData;
    do {
        // copy position (x,y,z) from vertexPositions (index 0,4,8)
        *puVar6 = puVar8[-2]; // x
        puVar6[1] = puVar8[-1]; // y
        puVar6[2] = *puVar8; // z

        if (vertexColorsOrNormals == 0) {
            // use constant color from global variables
            *(char*)(puVar6 + 3) = (char)(int)(fVar2 * fVar1); // red
            *(char*)((int)puVar6 + 0xd) = (char)(int)(fVar3 * fVar1); // green
            *(char*)((int)puVar6 + 0xe) = (char)(int)(fVar4 * fVar1); // blue
            // alpha from fVar5 (via fVar13 below)
            fVar13 = fVar5;
        } else {
            // use per-vertex colors from vertexColorsOrNormals array
            *(char*)(puVar6 + 3) = (char)(int)(pfVar10[-3] * fVar1); // red (offset -12 bytes)
            *(char*)((int)puVar6 + 0xd) = (char)(int)(pfVar10[-2] * fVar1); // green (offset -8 bytes)
            *(char*)((int)puVar6 + 0xe) = (char)(int)(*(float*)((vertexColorsOrNormals - vertexPositions) + (int)puVar8) * fVar1); // blue (reads from vertexColorsOrNormals+8)
            fVar13 = *pfVar10; // alpha (from current pfVar10)
        }
        // write alpha
        *(char*)((int)puVar6 + 0xf) = (char)(int)(fVar13 * fVar1);

        undefined4* puVar7 = puVar6 + 4;
        if (extraVertexData != NULL) {
            // copy extra vertex data (UVs or other)
            puVar6[4] = *puVar12;
            puVar7 = puVar6 + 6;
            puVar6[5] = puVar12[1];
        }
        // advance pointers (each vertex: 4 floats? Actually puVar8+4 moves by 16 bytes, pfVar10+4 by 16, puVar12+4 by 16)
        puVar8 = puVar8 + 4;
        pfVar10 = pfVar10 + 4;
        puVar12 = puVar12 + 4;
        iVar9 = iVar9 - 1;
        puVar6 = puVar7;
    } while (iVar9 != 0);

    // submit primitive: 5 = triangle strip, 4 vertices, buffer + stride
    // +0x0060cc10: render_submit
    FUN_0060cc10(5, 4, &DAT_011f4240, local_4);

    if (extraVertexData == NULL) {
        if (DAT_01127958 != 0) {
            uVar11 = DAT_01127958 & 0xff;
            if ((&DAT_011eb8fc)[DAT_011278cc * 0x10] != '\0') {
                uVar11 = uVar11 + 0x10;
            }
            // +0x00618d40: some cleanup
            FUN_00618d40();
            // +0x011d912c: array of something (texture handles?) set to 0
            (&DAT_011d912c)[uVar11] = 0;
        }
    } else {
        if (DAT_01127800 != 0) {
            uVar11 = DAT_01127800 & 0xff;
            if ((&DAT_011eb8fc)[DAT_01127774 * 0x10] != '\0') {
                uVar11 = uVar11 + 0x10;
            }
            FUN_00618d40();
            (&DAT_011d912c)[uVar11] = 0;
        }
        // reset color components (maybe for next primitive)
        _DAT_01127804 = 0;
        _DAT_01127808 = 0;
        _DAT_0112780c = 0;
        _DAT_01127810 = 0;
        _DAT_01127814 = 0;
        _DAT_01127818 = 0;
        _DAT_0112781c = 0;
    }

    // reset current shader state
    DAT_012058f0 = 0;
    DAT_012058e8 = (undefined**)0x0;

    if (DAT_011f4234 == 0) {
        // +0x011f6b70: profiler end
        FUN_00612210(&DAT_011f6b70);
    }
    return;
}