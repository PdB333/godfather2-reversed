// FUNC_NAME: CollisionManager::sweepRay
void CollisionManager::sweepRay(float* startPos, int hitResult, float* outDist, char* outHit, int* outHandleLow, int* outHandleHigh)
{
    float* transformMatrix; // pfVar1
    bool bVar2, bVar3;
    float* eaxStart = startPos; // in_EAX
    int* primVtable; // piVar6
    int iVar5;
    int* primNode; // piVar8
    char* cVar7;
    int* piVar8_local;
    uint uVar9;
    int* puVar10;
    float fVar11, fVar12, fVar13;
    char cStack_2e2, cStack_2e1;
    int uStack_2e0, uStack_2dc;
    int* piStack_2d8;
    int local_2d4;
    int local_2d0;
    int iStack_2cc; // numSubTests
    int iStack_2c8; // allocator offset or flag
    int iStack_2c4; // saved allocator pointer
    int iStack_2c0; // loop counter
    int iStack_2bc; // prim index
    int iStack_2b8; // temp
    int iStack_2b4, iStack_2b0, iStack_2ac, iStack_2a8;
    float fStack_2b4, fStack_2b0, fStack_2ac, fStack_2a8;
    float afStack_2a4[2]; // actually float[3] but decompiler shows 2
    float fStack_29c, fStack_298, fStack_294; // local hit point components? 
    int uStack_290;
    float fStack_28c, fStack_288, fStack_284; // secondary hit point
    int uStack_280;
    int* puStack_278;
    int local_270; // saved from param_1+0x2c
    float local_26c; // used for min distance
    float fStack_268, fStack_264, fStack_260;
    float fStack_25c, fStack_258, fStack_254;
    int uStack_250;
    float fStack_248; // saved ray origin Y?
    float fStack_238, fStack_228; // ray direction components from earlier call
    char local_230[8]; // output of direction call
    float fStack_228; // overlapped with local_230? Actually local_230[4..7]? Not sure
    char auStack_21c[536]; // buffer for sub-primitive results

    // +0x2c: some saved pointer?
    local_270 = *(int*)(param_1 + 0x2c); // likely unused later, but stored

    // +0x8: pointer to something, +0x70: offset to count?
    iVar5 = *(int*)(*(int*)(param_1 + 8) + 0x70);
    local_2d0 = 0;
    local_2d4 = 0;
    if (iVar5 == 0) {
        local_26c = 0.0f;
    } else {
        local_26c = (float)(iVar5 + 0x10); // convert to float
    }

    // Call virtual function at (*(this+0x10))->vtable+0x1c to get ray direction from world transform?
    // param_1+0xa0 is likely the ray origin or transform? 
    // The call signature: (*(void**)(*(int*)(param_1+0x10) + 0x1c))(param_1+0xa0, *(float*)(*(int*)(*(int*)(param_1+8)+0x6c)+4) + _DAT_00e44838, local_230);
    (*(void (**)(int, float, char*))(**(int**)(param_1 + 0x10) + 0x1c))
                (param_1 + 0xa0, *(float*)(*(int*)(*(int*)(param_1 + 8) + 0x6c) + 4) + _DAT_00e44838, local_230);

    // Extract direction from local_230? Actually local_230[4..7] maybe fStack_228? 
    // fStack_238 = *(float*)(local_230 + 0) ?, fStack_228 = *(float*)(local_230 + 4)? The decompiler shows fStack_238 and fStack_228 used later.
    // They are set before the loop. They likely come from local_230.
    // Since we don't have exact, we'll assign later.

    iStack_2bc = *(int*)(param_1 + 0x154); // number of primitives
    // Start of ray: startPos + offset from this+0xd0 (world offset?)
    fStack_2ac = *eaxStart + *(float*)(param_1 + 0xd0);
    afStack_2a4[0] = *(float*)(param_1 + 0xd8) + eaxStart[2]; // note: original code uses in_EAX[2] as z? but array index 2 is out-of-bounds? Actually in_EAX is float*, so in_EAX[2] is third element.
    // fStack_2a8 = (fStack_238 + fStack_228) * DAT_00e2cd54? That seems like magnitude scaling.
    fStack_2a8 = (fStack_238 + fStack_228) * DAT_00e2cd54;
    fStack_2b0 = fStack_2a8 - fStack_238; // difference along direction?
    fStack_2b4 = (((*(float*)(param_1 + 0xd4) - fStack_238) - DAT_00e44834) - _DAT_00e2cd50) + DAT_00e2cd48; // some offset
    fStack_248 = fStack_238; // save ray direction component

    // Main loop over primitives from last to first
    do {
        while (true) {
            do {
                iStack_2bc = iStack_2bc - 1;
                if (iStack_2bc < 0) {
                    iVar5 = *(int*)(hitResult + 0x50); // store primitive pointer?
                    *outHandleLow = 0;
                    *outHandleHigh = 0;
                    if (iVar5 == 0) {
                        *outHit = 0;
                        *outDist = *(float*)(param_1 + 0xd4); // default return distance?
                    } else {
                        FUN_00aa2cd0(*(int*)(iVar5 + 8), hitResult); // some cleanup?
                        *outDist = (fStack_2a8 - *(float*)(hitResult + 0x10) * fStack_2b0) + fStack_2b4;
                        bVar2 = DAT_00e2cd54 != *(float*)(hitResult + 4);
                        bVar3 = *(float*)(hitResult + 4) <= DAT_00e2cd54;
                        *outHit = (char)(bVar3 && bVar2);
                        if (!bVar3 || !bVar2) {
                            *outHandleLow = uStack_2dc;
                            *outHandleHigh = uStack_2e0;
                            return;
                        }
                    }
                    return;
                }
                primNode = *(int**)(*(int*)(param_1 + 0x150) + iStack_2bc * 4);
                primVtable = (int*)*primNode; // pointer to vtable?
                piStack_2d8 = primNode;
            } while ((primVtable == (int*)0x0) || ((char)primNode[6] != '\x01') || ((int)(char)primNode[4] + (int)primNode == 0));

            // primNode[2] is transform matrix (12 floats? 3x4?)
            transformMatrix = (float*)primNode[2];
            // Transform ray start into local space of primitive
            fVar12 = fStack_2a8 - transformMatrix[0xd];
            fVar11 = fStack_2ac - transformMatrix[0xc];
            fVar13 = afStack_2a4[0] - transformMatrix[0xe];
            fStack_29c = transformMatrix[2] * fVar13 + transformMatrix[1] * fVar12 + fVar11 * *transformMatrix;
            fStack_298 = fVar11 * transformMatrix[4] + transformMatrix[6] * fVar13 + transformMatrix[5] * fVar12;
            fStack_294 = fVar11 * transformMatrix[8] + transformMatrix[10] * fVar13 + transformMatrix[9] * fVar12;
            uStack_290 = 0; // maybe padding

            // Also transform a second point (maybe the ray end? fStack_248 is saved direction component)
            fVar12 = fStack_248 - transformMatrix[0xd];
            fVar13 = afStack_2a4[0] - transformMatrix[0xe];
            fVar11 = fStack_2ac - transformMatrix[0xc];
            fStack_28c = transformMatrix[1] * fVar12 + transformMatrix[2] * fVar13 + fVar11 * *transformMatrix;
            fStack_288 = fVar11 * transformMatrix[4] + transformMatrix[5] * fVar12 + transformMatrix[6] * fVar13;
            fStack_284 = fVar11 * transformMatrix[8] + transformMatrix[9] * fVar12 + transformMatrix[10] * fVar13;
            uStack_280 = 0;

            if (primVtable[3] == 0xb) break; // type 0xb is a compound primitive? (like a mesh?)

            // For simple primitives, call vtable+0x20 to test intersection
            (**(void (**)(char*, float*, int))(*(int*)primVtable + 0x20))(&cStack_2e1, &fStack_29c, hitResult);
            if ((cStack_2e1 != '\0') && (*(int**)(hitResult + 0x50) = primNode, *(int*)(hitResult + 0x20) == -1)) {
                // Store primitive handle from primVtable[2] (user data pointer?)
                puVar10 = (int*)primVtable[2];
                uStack_2dc = 0;
                if (puVar10 == (int*)0x0) {
                    uStack_2e0 = 0;
                } else {
                    uStack_2e0 = puVar10[1];
                    uStack_2dc = *puVar10;
                }
            }
        }

        // For type 0xb (mesh/compound), we need to iterate sub-primitives
        local_26c = fStack_28c;
        if (fStack_29c < fStack_28c) {
            local_26c = fStack_29c;
        }
        fStack_268 = fStack_288;
        if (fStack_298 < fStack_288) {
            fStack_268 = fStack_298;
        }
        fStack_264 = fStack_294;
        if (fStack_284 <= fStack_294) {
            fStack_264 = fStack_284;
        }
        fStack_268 = fStack_268 - DAT_00e2fc48; // epsilon
        local_26c = local_26c - DAT_00e2fc48;
        fStack_264 = fStack_264 - DAT_00e2fc48;
        uStack_260 = 0;

        fStack_25c = fStack_28c;
        if (fStack_28c < fStack_29c) {
            fStack_25c = fStack_29c;
        }
        fStack_258 = fStack_298;
        if (fStack_298 <= fStack_288) {
            fStack_258 = fStack_288;
        }
        fStack_254 = fStack_294;
        if (fStack_294 <= fStack_284) {
            fStack_254 = fStack_284;
        }
        fStack_25c = fStack_25c + DAT_00e2fc48;
        fStack_258 = fStack_258 + DAT_00e2fc48;
        fStack_254 = fStack_254 + DAT_00e2fc48;
        uStack_250 = 0;

        local_2d0 = 0;
        iStack_2cc = 0;
        iStack_2c8 = 0x80000000; // Sentinel for allocator

        // Custom allocator using TLS
        int* allocator = (int*)TlsGetValue(DAT_01139810);
        iVar5 = allocator[8];
        if ((uint)allocator[0xb] < iVar5 + 0x30U) {
            iVar5 = (*(int (**)(int))(*(int*)allocator + 0x14))(0x30); // allocate 48 bytes
        } else {
            allocator[8] = iVar5 + 0x30U;
        }
        iStack_2c8 = -0x7ffffff6; // not overflow? Actually -2147483642? Use as alloc flag
        local_2d0 = iVar5; // pointer to allocated block
        iStack_2c4 = iVar5; // save for deallocation

        // Call vtable+0x2c to get number of sub-primitives? (likely aabb test)
        (**(void (**)(float*, int*))(*(int*)primVtable + 0x2c))(&local_26c, &local_2d0);
        // Call vtable+0x14 to get something else
        primVtable = (int*)(*(int (**)(void))(*(int*)primVtable + 0x14))();
        iStack_2c0 = 0;
        if (0 < iStack_2cc) {
            do {
                iVar5 = iStack_2c0 * 4;
                iStack_2b8 = iVar5;
                cVar7 = (char*)(**(int (**)(int, float*, int*, int*, int))(*(int*)primVtable + 0x00)) // first vtable entry?
                    ((int)&local_2d4 + 3, &fStack_29c, *primNode, primVtable, *(int*)(local_2d0 + iVar5));
                primNode = piStack_2d8; // restore
                if (*cVar7 != '\0') {
                    primNode = (int*)(*(int (**)(int, char*))(*(int*)primVtable + 0x14))
                        (*(int*)(local_2d0 + iVar5), auStack_21c);
                    // Call vtable+0x20 again on the sub-primitive
                    (**(void (**)(char*, float*, int))(*(int*)primNode + 0x20))(&stack0xfffffd16, afStack_2a4, hitResult);
                    primNode = piStack_2d8;
                    if (cStack_2e2 != '\0') {
                        *(int**)(hitResult + 0x50) = piStack_2d8;
                        uVar9 = piStack_2d8[7]; // flags
                        if ((uVar9 & 0xc0000000) == 0x80000000) {
                            puVar10 = (int*)(uVar9 * 4);
                            if (puVar10 != (int*)0x0) {
                                uStack_2dc = *puVar10;
                                uStack_2e0 = puVar10[1];
                            }
                        } else if ((uVar9 & 0xc0000000) == 0xc0000000) {
                            puVar10 = *(int**)(uVar9 * 4 + 0x60);
                            if (puVar10 != (int*)0x0) {
                                uStack_2dc = *puVar10;
                                uStack_2e0 = puVar10[1];
                            }
                        } else {
                            uVar9 = (*(int (**)(int))(*(int*)primVtable + 0x10))(*(int*)(local_2d0 + iStack_2b8));
                            if ((uVar9 & 0xc0000000) == 0x80000000) {
                                puVar10 = (int*)(uVar9 * 4);
                                if (puVar10 != (int*)0x0) {
                                    uStack_2dc = *puVar10;
                                    uStack_2e0 = puVar10[1];
                                }
                            } else if ((uVar9 & 0xc0000000) == 0xc0000000) {
                                puVar10 = *(int**)(uVar9 * 4 + 0x60);
                                if (puVar10 != (int*)0x0) {
                                    uStack_2dc = *puVar10;
                                    uStack_2e0 = puVar10[1];
                                }
                            } else {
                                uStack_2dc = 0;
                                uStack_2e0 = 0;
                            }
                        }
                    }
                }
                iStack_2c0 = iStack_2c0 + 1;
            } while (iStack_2c0 < iStack_2cc);
        }

        iVar5 = iStack_2c4; // allocate pointer
        int* allocator2 = (int*)TlsGetValue(DAT_01139810);
        allocator2[8] = iVar5; // restore allocator state
        if (iVar5 == allocator2[10]) {
            (*(void (**)(int))(*(int*)allocator2 + 0x18))(iVar5); // free memory
        }
        iVar5 = iStack_2c8;
        if (-1 < iStack_2c8) {
            TlsGetValue(DAT_01139810);
            FUN_00aa26e0(local_2d0, iVar5 * 4, 0x17); // likely memset
        }
    } while (true);
}