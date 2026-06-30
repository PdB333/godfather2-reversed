// FUNC_NAME: RibbonTrail::buildGeometry
// Address: 0x004fab60
// Role: Generates ribbon vertex data for a trail effect. Computes interpolated positions along two direction vectors and writes vertex data to a buffer. Also sets width/length scaling and optional additional vertex data.

void __thiscall RibbonTrail::buildGeometry(
    float* startPos1,       // param_1: Starting position for first direction
    float* startPos2,       // param_2: Starting position for second direction (may be offset)
    float* endPos1,         // param_3: Ending position for first direction
    float* endPos2,         // param_4: Ending position for second direction
    float param5,           // param_5: Base scale factor
    float param6,           // param_6: End scale factor
    float param7,           // param_7: Base width
    float param8,           // param_8: Width increment (after scaling)
    float param9,           // param_9: Base offset for optional geometry
    float param10,          // param_10: Offset increment for optional geometry
    char param11            // param_11: Flag to enable optional geometry (e.g., secondary ribbon)
    )
{
    float dir1_x, dir1_y, dir1_z;
    float dir2_x, dir2_y, dir2_z;
    float fVar1, fVar2, fVar3, fVar4;
    float fVar8, fVar9, fVar10, fVar11, fVar12, fVar13, fVar14, fVar16;
    int iVar7;
    float* pfVar6;
    undefined4 uVar5;
    undefined4 uVar15;

    // Global constants: DAT_00e2cd54 and DAT_00e35654 (likely frame time or scaling factors)
    float g_scale1 = DAT_00e2cd54;
    float g_scale2 = DAT_00e35654;

    // Compute direction vectors scaled by global constants
    dir1_x = g_scale1 * (*startPos1 - *endPos1);
    dir1_y = g_scale1 * (startPos1[1] - endPos1[1]);
    dir1_z = g_scale1 * (startPos1[2] - endPos1[2]);

    dir2_x = g_scale2 * (*endPos2 - *startPos2);
    dir2_y = g_scale2 * (endPos2[1] - startPos2[1]);
    dir2_z = g_scale2 * (endPos2[2] - startPos2[2]);

    // Two calls to an initialization function (may set sin/cos tables, but results ignored)
    FUN_00414aa0();
    FUN_00414aa0();

    // Local accumulators for interpolation (initialized to dir offsets)
    float accum1_x = dir2_x;
    float accum1_y = dir2_y;
    float accum1_z = dir2_z;
    float accum2_x = dir1_x;
    float accum2_y = dir1_y;
    float accum2_z = dir1_z;

    // iVar7 counts vertex index (starts at 2 to skip first two? Actually used as segment counter)
    iVar7 = 2;
    // pfVar6 points to vertex buffer at this+0x70 (each vertex: 4 floats: x,y,z,w)
    pfVar6 = (float*)((uint)this + 0x70);

    do {
        // Write first vertex of the pair (from startPos2 + accum1)
        fVar1 = pfVar6[3];                      // Get original W component (e.g., alpha)
        fVar2 = startPos2[1];
        fVar3 = startPos2[2];
        fVar4 = startPos2[3];
        pfVar6[0] = *startPos2 + accum1_x;
        pfVar6[1] = fVar2 + accum1_y;
        pfVar6[2] = fVar3 + accum1_z;
        pfVar6[3] = fVar4 + 0.0f;
        pfVar6[3] = fVar1;                      // Restore original W

        // Increment accum1 for next segment
        accum1_x += dir2_x;
        accum1_y += dir2_y;
        accum1_z += dir2_z;

        // Write second vertex of the pair (from endPos1 + accum2) if not exceeded
        if (!(6 < iVar7 + 1)) {
            fVar1 = pfVar6[7];                  // Get W of next vertex
            fVar2 = endPos1[1];
            fVar3 = endPos1[2];
            fVar4 = endPos1[3];
            pfVar6[4] = *endPos1 + accum2_x;
            pfVar6[5] = fVar2 + accum2_y;
            pfVar6[6] = fVar3 + accum2_z;
            pfVar6[7] = fVar4 + 0.0f;
            pfVar6[7] = fVar1;                  // Restore original W

            iVar7 += 2;
            pfVar6 += 8;                        // Move to next pair of vertices

            // Increment accum2 for next segment
            accum2_x += dir1_x;
            accum2_y += dir1_y;
            accum2_z += dir1_z;

            // For odd segment counts, also increment accum1 again (double step)
            if (iVar7 != 6) {
                accum1_x += dir2_x;
                accum1_y += dir2_y;
                accum1_z += dir2_z;
            }
        }
    } while (iVar7 < 7);

    // Access a shared data structure for scaling parameters (this+0x3c)
    int ptr_3c = *(int*)((uint)this + 0x3c);
    float baseScale = *(float*)(ptr_3c + 0x80);   // +0x80: base scale factor
    float endScale = *(float*)(ptr_3c + 0x84);    // +0x84: end scale factor

    // Compute interpolated scale for mid-point
    float midScale = (param6 - param5) * g_scale1 + param5;

    // Set width/length parameters in the object
    *(float*)((uint)this + 0x130) = endScale * param5;                    // +0x130: width at start
    *(float*)((uint)this + 0x138) = midScale;                              // +0x138: mid width
    *(float*)((uint)this + 0x134) = baseScale * endScale * param5;         // +0x134: length product
    *(float*)((uint)this + 0x13c) = baseScale * midScale;                  // +0x13c: length product at mid
    *(float*)((uint)this + 0x140) = midScale;                              // +0x140: another width
    *(float*)((uint)this + 0x144) = baseScale * endScale * param6;         // +0x144: length at end
    *(float*)((uint)this + 0x148) = endScale * param6;                     // +0x148: width at end

    // Set ribbon vertex positions for the first set of vertices (0xc0, 0xd0, etc.)
    float originalW = *(float*)((uint)this + 0x168);   // +0x168: base W (e.g., alpha)
    *(float*)((uint)this + 0xc0) = param7;             // +0xc0: x for vertex0
    *(float*)((uint)this + 0xd0) = param7;             // +0xd0: x for another vertex
    *(float*)((uint)this + 0xc4) = originalW;          // +0xc4: w for vertex0

    float offset_y = *(float*)(ptr_3c + 0x4c);         // +0x4c: Y offset from shared data
    *(float*)((uint)this + 0xd4) = originalW + offset_y; // +0xd4: w for vertex at 0xd0

    float widthStep = param8 * g_scale2;                // Scale width increment
    *(float*)((uint)this + 0xe0) = widthStep + param7; // +0xe0: x for vertex2
    float temp = widthStep * 2.0f + param7;
    *(float*)((uint)this + 0xe4) = originalW;          // +0xe4: w for vertex2
    *(float*)((uint)this + 0xf0) = temp;                // +0xf0: x for vertex3
    *(float*)((uint)this + 0xf4) = originalW + offset_y; // +0xf4: w for vertex3

    float next = widthStep + temp;
    float last = widthStep + next;
    *(float*)((uint)this + 0x100) = next;              // +0x100: x for vertex4
    *(float*)((uint)this + 0x104) = originalW;          // +0x104: w for vertex4
    *(float*)((uint)this + 0x110) = last;               // +0x110: x for vertex5
    *(float*)((uint)this + 0x114) = originalW + offset_y; // +0x114: w for vertex5
    *(float*)((uint)this + 0x120) = last;               // +0x120: x for vertex6
    *(float*)((uint)this + 0x124) = originalW;          // +0x124: w for vertex6

    // If flag is set, generate an additional set of vertices (secondary ribbon)
    uVar5 = DAT_00e2b1a4;  // Global constant (likely a color or value)
    uVar15 = 0;
    if (param11 != '\0') {
        float offsetStep = param10 * g_scale2;
        *(float*)((uint)this + 200) = param9;          // +0xc8: x for secondary vertex0
        *(float*)((uint)this + 0xd8) = param9;         // +0xd8: x for secondary vertex1

        float temp2 = offsetStep * 2.0f + param9;
        *(float*)((uint)this + 0xe8) = offsetStep + param9; // +0xe8: x for secondary vertex2
        float next2 = offsetStep + temp2;
        float last2 = offsetStep + next2;
        *(float*)((uint)this + 0xcc) = uVar15;         // +0xcc: w? set to 0
        *(float*)((uint)this + 0xdc) = uVar5;          // +0xdc: w? set to global constant
        *(float*)((uint)this + 0xec) = uVar15;         // +0xec: w
        *(float*)((uint)this + 0xf8) = temp2;          // +0xf8: x
        *(float*)((uint)this + 0xfc) = uVar5;          // +0xfc: w
        *(float*)((uint)this + 0x108) = next2;         // +0x108: x
        *(float*)((uint)this + 0x10c) = uVar15;        // +0x10c: w
        *(float*)((uint)this + 0x118) = last2;         // +0x118: x
        *(float*)((uint)this + 0x11c) = uVar5;         // +0x11c: w
        *(float*)((uint)this + 0x128) = last2;         // +0x128: x
        *(float*)((uint)this + 300) = uVar15;          // +0x12c: w? set to 0
    }
    return;
}