// FUNC_NAME: CollisionMesh::queryContactPoint
// This function appears to perform a contact/collision query by transforming points, 
// computing bounding sphere min/max, and building a sorted contact list for a physics/collision system.

// The function takes a this pointer in EAX (likely a collision mesh/triangle mesh object) 
// and a second parameter which is a float array (transform matrix + offset data?)
void __fastcall CollisionMesh::queryContactPoint(void* thisPtr, float* transformData)
{
    float* pfVar1;
    float* pfVar2;
    uint uVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    uint* in_EAX;               // this pointer cast to uint* for field access
    int iVar9;                  // loop counter / stride
    byte* pbVar10;              // per-vertex data (bone weights or indices)
    ushort* puVar11;            // triangle index buffer
    float* pfVar12;             // temporary vertex pointer
    int iVar13;                 // vertex stride offset
    uint uVar14;                // vertex/triangle loop counter
    float fVar15, fVar16, fVar17, fVar18, fVar19;
    float fVar20, fVar21, fVar22, fVar23, fVar24;
    float fVar25, fVar26, fVar27, fVar28, fVar29;

    // Load global constants (likely from the collision physics globals)
    fVar8 = DAT_00e2b1a4;           // +0x0: some scale factor or epsilon
    iVar9 = 0;
    // First loop: compute a stride/adjust value (0x200 bytes? or 0x40 * 8?)
    do {
        iVar9 = iVar9 + 0x40;
    } while (iVar9 < 0x200);

    // Extract the last row of the transform matrix (translation?) + offset data from param_2
    fVar20 = transformData[8];      // +0x20
    fVar22 = transformData[9];      // +0x24
    fVar23 = transformData[10];     // +0x28
    pbVar10 = (byte*)in_EAX[2];     // this->m_vertexWeights? (byte array per vertex)
    fVar15 = *transformData;        // matrix row 0
    fVar16 = transformData[1];      // matrix row 0 Y
    fVar28 = transformData[2];      // matrix row 0 Z
    fVar18 = transformData[4];      // matrix row 1 X
    fVar17 = transformData[5];      // matrix row 1 Y
    fVar19 = transformData[6];      // matrix row 1 Z
    fVar24 = transformData[0xc];    // +0x30?
    fVar27 = transformData[0xd];    // +0x34?
    fVar7  = transformData[0xe];    // +0x38?
    uVar14 = 0;

    // Initialize min/max to extremes
    fVar21 = DAT_00e2e50c;          // +0x4: initial min (large positive)
    fVar26 = DAT_00e44758;          // +0x8: initial max (0.0 or large negative)

    if (*in_EAX != 0) { // this->m_vertexCount
        iVar9 = 0;
        iVar13 = 0;
        do {
            // Pointer to original vertex position (stride 0x14 bytes per vertex, likely 5 floats)
            pfVar12 = (float*)(in_EAX[1] + iVar13);
            fVar4 = *pfVar12;           // vertex X
            fVar5 = pfVar12[1];         // vertex Y
            fVar6 = pfVar12[2];         // vertex Z
            fVar25 = (float)*pbVar10 * _DAT_00e44898; // weight * some global scale

            // Transform vertex by matrix (note: uses fVar8 as the constant 1.0 for W?)
            fVar29 = fVar4 * fVar28 + fVar5 * fVar19 + fVar6 * fVar23 + fVar8 * fVar7;

            pbVar10++;

            // Update bounding sphere min/max (on Z? or on transformed result)
            if (fVar29 < fVar21) {
                fVar21 = fVar29;
            }
            if (fVar26 < fVar29) {
                fVar26 = fVar29;
            }

            // Write transformed vertex into output array (this->m_transformedVerts? in_EAX[5])
            pfVar12 = (float*)(in_EAX[5] + iVar9);
            uVar14++;
            *pfVar12 = fVar4 * fVar15 + fVar5 * fVar18 + fVar6 * fVar20 + fVar8 * fVar24;
            pfVar12[1] = fVar4 * fVar16 + fVar5 * fVar17 + fVar6 * fVar22 + fVar8 * fVar27;
            pfVar12[2] = fVar29;        // transformed Z
            pfVar12[3] = fVar25;        // scaled weight

            iVar13 += 0x14; // 20 bytes (5 floats) per vertex
            iVar9 += 0x10;  // 16 bytes (4 floats) per transformed vertex
        } while (uVar14 < *in_EAX);
    }

    // Now handle triangle data: compute contact depth + strength for each triangle
    fVar8 = DAT_00e2cbe0;           // epsilon for cross product length check
    puVar11 = (ushort*)in_EAX[4];   // this->m_triangles (index buffer: 3 shorts per triangle)
    fVar15 = (fVar26 - fVar21) * _DAT_00e44894; // range * some scale
    fVar16 = fVar15 * DAT_00e2eff4; // scaled penetration depth factor

    uVar14 = 0;
    // Compute contact strength divisor: denominator = (range*scale) + (range)
    fVar28 = DAT_00e2e22c / (fVar15 * DAT_00e2b04c + (fVar26 - fVar21));

    if (in_EAX[3] != 0) { // this->m_triangleCount
        do {
            uVar3 = in_EAX[5];       // transformed vertex array base
            // Get pointer to triangle vertices (3 indices -> 3 floats*4)
            pfVar12 = (float*)((uint)*puVar11 * 0x10 + uVar3);    // vertex A
            pfVar1  = (float*)((uint)puVar11[1] * 0x10 + uVar3); // vertex B
            pfVar2  = (float*)((uint)puVar11[2] * 0x10 + uVar3); // vertex C

            // Compute two edges: A-C and A-B
            fVar22 = *pfVar12 - *pfVar2;       // AX - CX
            fVar23 = pfVar12[1] - pfVar2[1];   // AY - CY
            fVar24 = pfVar12[2] - pfVar2[2];   // AZ - CZ
            fVar17 = *pfVar12 - *pfVar1;       // AX - BX
            fVar19 = pfVar12[1] - pfVar1[1];   // AY - BY
            fVar20 = pfVar12[2] - pfVar1[2];   // AZ - BZ

            // Cross product: (A-C) x (A-B) -> triangle normal * edge lengths
            fVar27 = fVar24 * fVar19 - fVar23 * fVar20;  // Nx
            fVar20 = fVar22 * fVar20 - fVar24 * fVar17;  // Ny
            fVar17 = fVar23 * fVar17 - fVar22 * fVar19;  // Nz

            puVar11 += 3;
            fVar19 = fVar17 * fVar17 + fVar27 * fVar27 + fVar20 * fVar20; // normal length squared

            if (fVar19 <= fVar8) {
                fVar19 = 0.0f;
            } else {
                fVar19 = DAT_00e2b1a4 / SQRT(fVar19); // normalize
            }

            fVar17 = fVar17 * fVar19; // normalized normal Z component

            // Clamp normal Z to a valid range for contact strength
            if (0.0f <= fVar17) {
                if (fVar17 <= DAT_00f17958) {
                    fVar17 = DAT_00f17958;
                }
                fVar17 = fVar17 * DAT_00e2cd54;
            } else {
                if (DAT_00e44890 <= fVar17) {
                    fVar17 = DAT_00e44890;
                }
            }

            // Compute contact strength based on:
            // - sum of vertex weights (pfVar12[3] + pfVar1[3] + pfVar2[3])
            // - normal Z and depth range
            // - triangle average depth (fVar18 + pfVar1[2] + pfVar2[2])
            // - current min/max distances
            fVar18 = (((pfVar12[3] + pfVar1[3] + pfVar2[3]) * _UNK_00e369cc * fVar17 * fVar16 +
                      (pfVar12[2] + pfVar1[2] + pfVar2[2]) * _UNK_00e369c8) - (fVar21 - fVar15)) * fVar28;

            // Clamp contact strength to [0, max]
            if (0.0f <= fVar18) {
                if (DAT_00e2e22c < fVar18) {
                    fVar18 = DAT_00e2e22c;
                }
            } else {
                fVar18 = 0.0f;
            }

            // Write contact index and strength into output array (in_EAX[6])
            *(short*)(in_EAX[6] + 2 + uVar14 * 4) = (short)(int)fVar18; // contact strength
            *(short*)(in_EAX[6] + uVar14 * 4) = (short)uVar14;          // triangle index
            uVar14++;
        } while (uVar14 < in_EAX[3]);
    }

    // Sort the contact list by strength (descending) via external function
    FUN_004cdc50(in_EAX[3], in_EAX[6], in_EAX[7]);
    return;
}