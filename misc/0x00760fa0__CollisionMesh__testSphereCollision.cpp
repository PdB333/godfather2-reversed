// FUNC_NAME: CollisionMesh::testSphereCollision
// Function address: 0x00760fa0
// Role: Check if a sphere (defined by bounding node) intersects any triangles in a mesh.
// Returns 1 if collision detected, 0 otherwise.

unsigned char __fastcall CollisionMesh::testSphereCollision(int thisPtr) {
    byte bCount1;
    int meshPtr;
    float *pCollisionNode;
    char bTemp;
    int iVar5;
    float *pfVar6;
    uint uLoopIdx1;
    uint uLoopIdx2;
    float10 fVar9;
    float fDistSq;
    float fRadiusSq;
    float fLocal1c;
    float fLocal18;
    float fLocal14;
    float fLocal10;
    int local_c[3]; // For triangle data

    // Check if both mesh and collision node pointers are valid
    if ((*(int *)(thisPtr + 0x70) != 0) && (*(int *)(thisPtr + 0x78) != 0)) {
        meshPtr = FUN_00471610(); // Get the mesh's transform/world data
        iVar5 = *(int *)(thisPtr + 0x70);
        pfVar6 = (float *)(meshPtr + 0x30); // +0x30: position/center of mesh? (float[3])

        if ((iVar5 != 0) &&
            ((pCollisionNode = *(float **)(thisPtr + 0x78), pCollisionNode != (float *)0x0 &&
              // pCollisionNode[3] is radius? Actually used: local_14 = pCollisionNode[3]*pCollisionNode[3], so it's radius
              (fRadiusSq = pCollisionNode[3] * pCollisionNode[3],
               // Compute squared distance between mesh position and collision node center
               fDistSq = (*(float *)(meshPtr + 0x34) - pCollisionNode[1]) * (*(float *)(meshPtr + 0x38) - pCollisionNode[2]),
               fDistSq = fDistSq * fDistSq + 
                         (*(float *)(meshPtr + 0x34) - pCollisionNode[1]) * (*(float *)(meshPtr + 0x34) - pCollisionNode[1]) +
                         (*pfVar6 - *pCollisionNode) * (*pfVar6 - *pCollisionNode),
               // Global distance threshold from DAT_00d654a0 (max collision distance?)
               fDistSq < DAT_00d654a0)))) {
            // First list: likely triangle faces or nodes
            bCount1 = *(byte *)(pCollisionNode + 5); // +0x14: count of elements in first list
            uLoopIdx1 = 0;
            if (bCount1 != 0) {
                do {
                    // Compute offset into triangle list: base from mesh + index * 0x10 (per element size)
                    iVar5 = (uint)(ushort)(*(short *)(pCollisionNode + 4) + (short)uLoopIdx1) * 0x10 +
                            *(int *)(iVar5 + 0x24);
                    if ((*(ushort *)(iVar5 + 10) & 0x9c00) == 0) { // Some flag test (collision mask?)
                        // FUN_004a09b0: likely distance to segment/triangle from sphere center
                        fVar9 = (float10)FUN_004a09b0(pfVar6, pCollisionNode,
                                                      *(int *)(iVar5 + 0x20) + 
                                                      (uint)*(ushort *)(iVar5 + 4) * 0x24, &fLocal18);
                        fLocal1c = (float)fVar9;
                        // Check against global distance thresholds
                        if (((DAT_00d577a0 < fLocal18) && (fLocal18 < DAT_00d5780c)) && (fLocal1c <= fRadiusSq)) {
                            return 1;
                        }
                    }
                    uLoopIdx1 = uLoopIdx1 + 1;
                } while (uLoopIdx1 < bCount1);
            }

            // Second list: count is sum of two bytes
            uLoopIdx1 = (uint)*(byte *)(pCollisionNode + 7) + (uint)*(byte *)((int)pCollisionNode + 0x15);
            uLoopIdx2 = 0;
            if (uLoopIdx1 != 0) {
                do {
                    iVar5 = (uint)(ushort)(*(short *)((int)pCollisionNode + 0x16) + (short)uLoopIdx2) * 0x10 +
                            *(int *)(iVar5 + 0x30);
                    if ((*(ushort *)(iVar5 + 10) & 0x9c00) == 0) {
                        // FUN_005fd1c0: fetch triangle info into local_c (3 indices?)
                        FUN_005fd1c0(local_c, iVar5);
                        fLocal1c = 0.0;
                        fLocal18 = 0.0;
                        bTemp = FUN_005f5cb0(&fLocal1c, &fLocal18); // Get barycentric coordinates?
                        if (((bTemp != '\0') && (fLocal1c != 0.0)) && (fLocal18 != 0.0)) {
                            fVar9 = (float10)FUN_004a09b0(pfVar6, pCollisionNode, fLocal18, &fLocal10);
                            fLocal18 = (float)fVar9;
                            if (((DAT_00d577a0 < fLocal10) && (fLocal10 < DAT_00d5780c)) && (fLocal18 <= fRadiusSq)) {
                                if (local_c[0] == 0) {
                                    return 1;
                                }
                                FUN_004daf90(local_c); // Release temporary memory
                                return 1;
                            }
                        }
                        if (local_c[0] != 0) {
                            FUN_004daf90(local_c);
                        }
                    }
                    uLoopIdx2 = uLoopIdx2 + 1;
                    if (uLoopIdx1 <= uLoopIdx2) {
                        return 0;
                    }
                } while (true);
            }
        }
    }
    return 0;
}