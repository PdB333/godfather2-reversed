// FUNC_NAME: CollisionWorld::raycast
void CollisionWorld::raycast(CollisionWorld* this, RaycastHit* hitInfo, float* outDistance, bool* outHit, Vector2* outNormal, Vector2* outPoint)
{
    // this+0x2c: some transform or matrix
    // this+0x8: pointer to something with +0x70 (count?) and +0x6c (array?)
    // this+0x10: pointer to something with vtable at +0x1c (getWorldTransform)
    // this+0xa0: world transform matrix?
    // this+0xd0, +0xd4, +0xd8: ray origin (x,y,z)
    // this+0x150: array of collision objects (pointers)
    // this+0x154: count of objects
    // hitInfo+0x50: pointer to hit object
    // hitInfo+0x10: some float
    // hitInfo+0x4: some float
    // hitInfo+0x20: some int

    float* rayOrigin = (float*)(this + 0xd0); // x,y,z
    float* rayDirection = (float*)(this + 0xd8); // z? Actually in_EAX is passed as float* containing direction? The code uses in_EAX[0], in_EAX[2] so it's a 3-component vector passed in EAX. We'll assume it's the ray direction.
    // Actually the function receives in_EAX as a float* (likely the ray direction). We'll rename it as rayDir.
    float* rayDir = in_EAX;

    // Local variables
    float fStack_238; // some intermediate
    float fStack_228; // some intermediate
    float fStack_2a8; // computed distance
    float fStack_2ac; // rayOrigin.x + rayDir.x
    float fStack_2b0; // fStack_2a8 - fStack_238
    float fStack_2b4; // offset
    float fStack_248; // copy of fStack_238
    int iStack_2bc; // loop counter
    int* piStack_2d8; // current object pointer
    int* piVar8; // current object
    int* piVar6; // vtable pointer of object
    float* pfVar1; // transform matrix of object
    float fStack_29c, fStack_298, fStack_294; // transformed ray origin in object space
    float fStack_28c, fStack_288, fStack_284; // transformed ray origin (second point?)
    float local_26c; // min distance
    int local_2d0; // temporary allocation pointer
    int iStack_2cc; // count of sub-shapes
    int iStack_2c8; // allocation size
    int iStack_2c4; // saved allocation pointer
    int iStack_2c0; // loop index
    int iStack_2b8; // offset
    char cStack_2e2; // hit flag from sub-shape test
    char cStack_2e1; // hit flag from shape test
    undefined4 uStack_2e0, uStack_2dc; // hit normal/point components
    undefined4 uStack_290, uStack_280, uStack_260, uStack_250; // unused?
    float fStack_268, fStack_264, fStack_25c, fStack_258, fStack_254; // AABB min/max
    int iVar5; // temp
    bool bVar2, bVar3; // bools
    undefined4 local_270; // from this+0x2c
    float fStack_2b4; // computed offset
    float fStack_2a8; // computed distance along ray
    float afStack_2a4[2]; // ray origin z? Actually afStack_2a4[0] = rayOrigin.z + rayDir[2]
    float fStack_2a8; // (fStack_238 + fStack_228) * DAT_00e2cd54
    float fStack_2b0; // fStack_2a8 - fStack_238
    float fStack_2b4; // (((rayOrigin.y - fStack_238) - DAT_00e44834) - DAT_00e2cd50) + DAT_00e2cd48
    // Many stack variables are reused.

    // Constants (global floats)
    extern float DAT_00e2cd54; // max distance?
    extern float DAT_00e2fc48; // epsilon
    extern float DAT_00e44834; // offset
    extern float DAT_00e2cd50; // offset
    extern float DAT_00e2cd48; // offset
    extern float DAT_00e44838; // offset

    // TLS memory pool
    extern int gTlsMemPool; // DAT_01139810

    // Initialize
    local_270 = *(undefined4*)(this + 0x2c);
    iVar5 = *(int*)(*(int*)(this + 8) + 0x70); // some count
    local_2d0 = 0;
    local_2d4 = 0;
    if (iVar5 == 0) {
        local_26c = 0.0f;
    } else {
        local_26c = (float)(iVar5 + 0x10);
    }

    // Get world transform? Call vtable function at offset 0x1c on object at this+0x10
    (**(code**)(**(int**)(this + 0x10) + 0x1c))(this + 0xa0, *(float*)(*(int*)(*(int*)(this + 8) + 0x6c) + 4) + DAT_00e44838, local_230);

    iStack_2bc = *(int*)(this + 0x154); // number of objects
    fStack_2ac = rayDir[0] + *(float*)(this + 0xd0); // rayOrigin.x + rayDir.x
    afStack_2a4[0] = *(float*)(this + 0xd8) + rayDir[2]; // rayOrigin.z + rayDir.z
    fStack_2a8 = (fStack_238 + fStack_228) * DAT_00e2cd54; // some distance
    fStack_2b0 = fStack_2a8 - fStack_238;
    fStack_2b4 = (((*(float*)(this + 0xd4) - fStack_238) - DAT_00e44834) - DAT_00e2cd50) + DAT_00e2cd48;
    fStack_248 = fStack_238;

    do {
        while (true) {
            do {
                iStack_2bc--;
                if (iStack_2bc < 0) {
                    // No more objects, return default
                    iVar5 = *(int*)(hitInfo + 0x50);
                    *outNormal = Vector2(0,0);
                    *outPoint = Vector2(0,0);
                    if (iVar5 == 0) {
                        *outHit = false;
                        *outDistance = *(float*)(this + 0xd4); // ray origin y?
                    } else {
                        // Transform point? Call FUN_00aa2cd0
                        FUN_00aa2cd0(*(undefined4*)(iVar5 + 8), hitInfo);
                        *outDistance = (fStack_2a8 - *(float*)(hitInfo + 0x10) * fStack_2b0) + fStack_2b4;
                        bVar2 = DAT_00e2cd54 != *(float*)(hitInfo + 4);
                        bVar3 = *(float*)(hitInfo + 4) <= DAT_00e2cd54;
                        *outHit = bVar3 && bVar2;
                        if (!bVar3 || !bVar2) {
                            *outNormal = *(Vector2*)&uStack_2dc;
                            *outPoint = *(Vector2*)&uStack_2e0;
                            return;
                        }
                    }
                    return;
                }
                piVar8 = *(int**)(*(int*)(this + 0x150) + iStack_2bc * 4);
                piVar6 = (int*)*piVar8;
                piStack_2d8 = piVar8;
            } while (piVar6 == 0 || ((char)piVar8[6] != 1) || ((int)(char)piVar8[4] + (int)piVar8 == 0));
            // piVar8[6] is active flag, piVar8[4] is some offset

            pfVar1 = (float*)piVar8[2]; // transform matrix
            // Transform ray origin and direction into object local space
            fVar12 = fStack_2a8 - pfVar1[0xd];
            fVar11 = fStack_2ac - pfVar1[0xc];
            fVar13 = afStack_2a4[0] - pfVar1[0xe];
            fStack_29c = pfVar1[2] * fVar13 + pfVar1[1] * fVar12 + fVar11 * pfVar1[0];
            fStack_298 = fVar11 * pfVar1[4] + pfVar1[6] * fVar13 + pfVar1[5] * fVar12;
            fStack_294 = fVar11 * pfVar1[8] + pfVar1[10] * fVar13 + pfVar1[9] * fVar12;
            uStack_290 = 0;
            // Second point (maybe ray end?)
            fVar12 = fStack_248 - pfVar1[0xd];
            fVar13 = afStack_2a4[0] - pfVar1[0xe];
            fVar11 = fStack_2ac - pfVar1[0xc];
            fStack_28c = pfVar1[1] * fVar12 + pfVar1[2] * fVar13 + fVar11 * pfVar1[0];
            fStack_288 = fVar11 * pfVar1[4] + pfVar1[5] * fVar12 + pfVar1[6] * fVar13;
            fStack_284 = fVar11 * pfVar1[8] + pfVar1[9] * fVar12 + pfVar1[10] * fVar13;
            uStack_280 = 0;

            if (piVar6[3] == 0xb) break; // type 0xb is special (compound/mesh)

            // Call shape's test function (vtable+0x20)
            (**(code**)(*piVar6 + 0x20))(&cStack_2e1, &fStack_29c, hitInfo);
            if (cStack_2e1 != 0 && (*(int**)(hitInfo + 0x50) = piVar8, *(int*)(hitInfo + 0x20) == -1)) {
                // Store hit normal/point from shape data
                puVar10 = (undefined4*)piVar6[2];
                uStack_2dc = 0;
                if (puVar10 == 0) {
                    uStack_2e0 = 0;
                } else {
                    uStack_2e0 = puVar10[1];
                    uStack_2dc = *puVar10;
                }
            }
        } // end while(true) inner

        // Type 0xb: compound shape
        local_26c = fStack_28c;
        if (fStack_29c < fStack_28c) local_26c = fStack_29c;
        fStack_268 = fStack_288;
        if (fStack_298 < fStack_288) fStack_268 = fStack_298;
        fStack_264 = fStack_294;
        if (fStack_284 <= fStack_294) fStack_264 = fStack_284;
        fStack_268 -= DAT_00e2fc48;
        local_26c -= DAT_00e2fc48;
        fStack_264 -= DAT_00e2fc48;
        uStack_260 = 0;
        fStack_25c = fStack_28c;
        if (fStack_28c < fStack_29c) fStack_25c = fStack_29c;
        fStack_258 = fStack_298;
        if (fStack_298 <= fStack_288) fStack_258 = fStack_288;
        fStack_254 = fStack_294;
        if (fStack_294 <= fStack_284) fStack_254 = fStack_284;
        fStack_25c += DAT_00e2fc48;
        fStack_258 += DAT_00e2fc48;
        fStack_254 += DAT_00e2fc48;
        uStack_250 = 0;
        local_2d0 = 0;
        iStack_2cc = 0;
        iStack_2c8 = 0x80000000; // negative
        // Allocate temporary memory from TLS pool
        int* tlsPool = (int*)TlsGetValue(gTlsMemPool);
        iVar5 = tlsPool[8];
        if ((uint)tlsPool[0xb] < iVar5 + 0x30U) {
            iVar5 = (**(code**)(*tlsPool + 0x14))(0x30);
        } else {
            tlsPool[8] = iVar5 + 0x30U;
        }
        iStack_2c8 = -0x7ffffff6; // some size
        local_2d0 = iVar5;
        iStack_2c4 = iVar5;
        // Call shape's getSubShapes function (vtable+0x2c)
        (**(code**)(*piVar6 + 0x2c))(&local_26c, &local_2d0);
        piVar6 = (int*)(**(code**)(*piVar6 + 0x14))(); // get something
        iStack_2c0 = 0;
        if (0 < iStack_2cc) {
            do {
                iVar5 = iStack_2c0 * 4;
                iStack_2b8 = iVar5;
                // Call sub-shape's test function
                char* result = (char*)(**(code**)*puStack_278)((int)&local_2d4 + 3, &fStack_29c, *piVar8, piVar6, *(undefined4*)(local_2d0 + iVar5));
                piVar8 = piStack_2d8;
                if (*result != 0) {
                    piVar8 = (int*)(**(code**)(*piVar6 + 0x14))(*(undefined4*)(local_2d0 + iVar5), auStack_21c);
                    (**(code**)(*piVar8 + 0x20))(&stack0xfffffd16, afStack_2a4, hitInfo);
                    piVar8 = piStack_2d8;
                    if (cStack_2e2 != 0) {
                        *(int**)(hitInfo + 0x50) = piStack_2d8;
                        uint uVar9 = piStack_2d8[7];
                        if ((uVar9 & 0xc0000000) == 0x80000000) {
                            puVar10 = (undefined4*)(uVar9 * 4);
                            if (puVar10 != 0) {
                                uStack_2dc = *puVar10;
                                uStack_2e0 = puVar10[1];
                            }
                        } else if ((uVar9 & 0xc0000000) == 0xc0000000) {
                            puVar10 = *(undefined4**)(uVar9 * 4 + 0x60);
                            if (puVar10 != 0) {
                                uStack_2dc = *puVar10;
                                uStack_2e0 = puVar10[1];
                            }
                        } else {
                            uVar9 = (**(code**)(*piVar6 + 0x10))(*(undefined4*)(local_2d0 + iStack_2b8));
                            if ((uVar9 & 0xc0000000) == 0x80000000) {
                                puVar10 = (undefined4*)(uVar9 * 4);
                                if (puVar10 != 0) {
                                    uStack_2dc = *puVar10;
                                    uStack_2e0 = puVar10[1];
                                }
                            } else if ((uVar9 & 0xc0000000) == 0xc0000000) {
                                puVar10 = *(undefined4**)(uVar9 * 4 + 0x60);
                                if (puVar10 != 0) {
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
                iStack_2c0++;
            } while (iStack_2c0 < iStack_2cc);
        }
        // Free temporary memory
        iVar5 = iStack_2c4;
        int* tlsPool2 = (int*)TlsGetValue(gTlsMemPool);
        tlsPool2[8] = iVar5;
        if (iVar5 == tlsPool2[10]) {
            (**(code**)(*tlsPool2 + 0x18))(iVar5);
        }
        iVar5 = iStack_2c8;
        if (iStack_2c8 >= 0) {
            TlsGetValue(gTlsMemPool);
            FUN_00aa26e0(local_2d0, iVar5 * 4, 0x17);
        }
    } while (true);
}