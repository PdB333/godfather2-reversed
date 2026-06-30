// FUNC_NAME: FrustumCuller::collectVisibleObjects
void __thiscall FrustumCuller::collectVisibleObjects(int cameraIndex) {
    int *piVar1;
    int *piVar2;
    int iVar3;
    uint uVar4;
    int iVar5;
    int iVar6;
    int *piVar7;
    int iVar8;
    int local_dc;          // temp buffer pointer
    int local_d8;          // number of visible instances returned by cull test
    int local_d4;          // allocation flag
    int iStack_d0;         // saved temp buffer pointer
    int local_cc;          // loop index
    int local_c8;          // frustum data pointer
    int *local_c4;         // current renderable node pointer
    float local_c0;        // scaled max x
    float local_bc;        // scaled max y
    float local_b8;        // scaled max z
    float local_b4;        // scaled max w (or far plane)
    float local_b0;        // scaled min x
    float local_ac;        // scaled min y
    float local_a8;        // scaled min z
    float local_a4;        // scaled min w (or near plane)
    int *local_98;         // pointer to the object entry in the scene array
    int local_94;          // this pointer copy
    char auStack_90[48];   // buffer for world matrix (12 floats)
    float fStack_60;       // copy of local_c0 for function call
    float fStack_5c;       // copy of local_bc
    float fStack_58;       // copy of local_b8
    float fStack_54;       // copy of local_b4
    char auStack_50[76];   // output buffer for visibility data

    local_94 = (int)this;
    debugPrint(cameraIndex); // FUN_00bed560

    // Global frustum scaling factor (likely 1/tan(fov) or similar)
    float frustumScale = g_frustumScale; // DAT_00e2cd54

    // Get frustum data pointer (this+0x10)
    FrustumData* frustumData = *(FrustumData**)(this + 0x10);
    // Reset visible count
    *(int*)(this + 0x28) = 0; // visibleCount = 0

    // Compute scaled frustum corners (min and max of view frustum in some space)
    // Offsets: frustumData+0xa0 = minX, +0xa4 = minY, +0xa8 = minZ, +0xac = minW
    //          frustumData+0xb0 = maxX, +0xb4 = maxY, +0xb8 = maxZ, +0xbc = maxW
    local_b0 = (*(float*)(frustumData + 0xb0) - *(float*)(frustumData + 0xa0)) * frustumScale;
    local_ac = (*(float*)(frustumData + 0xb4) - *(float*)(frustumData + 0xa4)) * frustumScale;
    local_a8 = (*(float*)(frustumData + 0xb8) - *(float*)(frustumData + 0xa8)) * frustumScale;
    local_a4 = (*(float*)(frustumData + 0xbc) - *(float*)(frustumData + 0xac)) * frustumScale;

    local_c0 = (*(float*)(frustumData + 0xb0) + *(float*)(frustumData + 0xa0)) * frustumScale;
    local_bc = (*(float*)(frustumData + 0xb4) + *(float*)(frustumData + 0xa4)) * frustumScale;
    local_b8 = (*(float*)(frustumData + 0xb8) + *(float*)(frustumData + 0xa8)) * frustumScale;
    local_b4 = (*(float*)(frustumData + 0xbc) + *(float*)(frustumData + 0xac)) * frustumScale;

    local_cc = 0;
    local_c8 = (int)frustumData;

    // Iterate over all objects in the scene (frustumData+0xc0 = objectArray, +0xc4 = objectCount)
    if (0 < *(int*)(frustumData + 0xc4)) {
        do {
            // Get pointer to object entry (each entry is a pointer to a RenderableNode)
            piVar7 = *(int**)(*(int*)(frustumData + 0xc0) + local_cc * 4);
            // First field of the entry is a pointer to the renderable node
            piVar1 = (int*)*piVar7;
            // Check if node exists and is of type 0xb (e.g., "RenderableMesh")
            if ((piVar1 != (int*)0x0) && (piVar1[3] == 0xb)) {
                // Initialize temp buffer allocation state
                local_dc = 0;
                local_d8 = 0;
                local_d4 = 0x80000000; // sentinel for "not allocated"
                local_c4 = piVar1;     // save renderable node pointer
                local_98 = piVar7;     // save object entry pointer

                // Thread-local temporary allocator (TlsGetValue)
                piVar2 = (int*)TlsGetValue(g_tlsAllocatorIndex); // DAT_01139810
                iVar3 = piVar2[8]; // current offset in temp buffer
                if ((uint)piVar2[0xb] < iVar3 + 0x110U) {
                    // Need to allocate more memory
                    iVar3 = (**(code**)(*piVar2 + 0x14))(0x110); // allocate 0x110 bytes
                } else {
                    piVar2[8] = iVar3 + 0x110U; // advance offset
                }

                // Set up scaled frustum corners for the cull test
                fStack_60 = local_c0;
                fStack_5c = local_bc;
                fStack_58 = local_b8;
                local_d4 = -0x7fffffc0; // flag indicating allocation is from temp buffer
                fStack_54 = local_b4;
                local_dc = iVar3;       // temp buffer pointer
                iStack_d0 = iVar3;      // save for later free

                // Lock mutex (FUN_00aa5450)
                mutexLock(&g_cullMutex); // DAT_00ef3f00

                // Get world matrix of the object (piVar7[2] is the transform component)
                getWorldMatrix(piVar7[2], (float(*)[12])auStack_90); // FUN_00aa1e40

                // Perform cull test on the renderable node
                // Virtual function at vtable+0x24: returns number of visible instances
                // Arguments: output buffer, scaled frustum bounds, flags (0), temp buffer pointer
                local_d8 = (*(int(__thiscall**)(void*, char*, float*, int, int*))(*piVar1 + 0x24))
                           (piVar1, auStack_50, &local_b0, 0, &local_dc);

                // If there are visible instances, append them to the visible list
                if (local_d8 != 0) {
                    int currentCount = *(int*)(local_94 + 0x28); // visibleCount
                    int* arrayPtr = (int*)(local_94 + 0x24);    // pointer to visibleObjectsArray
                    int newCount = local_d8 + currentCount;
                    uint capacity = *(uint*)(local_94 + 0x2c) & 0x3fffffff; // capacity (masked)

                    // Grow array if needed (element size = 0xc = 12 bytes)
                    if ((int)capacity < newCount) {
                        int newCapacity = capacity * 2;
                        if (newCapacity <= newCount) {
                            newCapacity = newCount;
                        }
                        reallocateArray(arrayPtr, newCapacity, 0xc); // FUN_00aa4110
                    }

                    // Pointer to the first new slot
                    piVar7 = (int*)(*arrayPtr + currentCount * 0xc);
                    int i = 0;
                    *(int*)(local_94 + 0x28) = newCount; // update count

                    // Copy visible instance data
                    if (0 < local_d8) {
                        do {
                            *piVar7 = (int)local_98;                     // pointer to object entry
                            piVar7[1] = local_c4[0xd];                   // renderable node ID (offset 0x34)
                            piVar7[2] = *(int*)(local_dc + i * 4);      // instance data from temp buffer
                            i++;
                            piVar7 += 3; // advance by 3 ints (12 bytes)
                        } while (i < local_d8);
                    }
                }

                // Free temporary buffer
                int tempBuf = iStack_d0;
                piVar7 = (int*)TlsGetValue(g_tlsAllocatorIndex);
                piVar7[8] = tempBuf; // restore offset
                if (tempBuf == piVar7[10]) {
                    // If buffer is at the end, free it
                    (**(code**)(*piVar7 + 0x18))(tempBuf); // free function
                }

                // If we allocated a separate buffer (not from temp pool), free it
                if (-1 < local_d4) {
                    TlsGetValue(g_tlsAllocatorIndex);
                    freeTempBuffer(local_dc, local_d4 * 4, 0x17); // FUN_00aa26e0
                }
            }
            local_cc++;
        } while (local_cc < *(int*)(frustumData + 0xc4));
    }
    return;
}