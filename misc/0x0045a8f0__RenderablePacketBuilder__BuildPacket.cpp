// FUNC_NAME: RenderablePacketBuilder::BuildPacket

undefined4* RenderablePacketBuilder::BuildPacket(
    uint** objectArray,           // param_1: array of object pointers
    uint objectCount,            // param_2: number of objects
    uint* prevStateList,         // param_3: previous state triples (pointer, id, ?)
    uint prevStateCount,         // param_4: number of previous state entries
    int packingContext,          // param_5: some context/allocator (e.g. for vertex packing)
    uint filterFlags,            // param_6: filter flags
    undefined4 sourceIdentifier // param_7: source ID (e.g. network slot)
) {
    uint* puVar1;
    char cVar2;
    uint* puVar3;
    uint uVar4;
    int* piVar5;
    undefined4* puVar6; // output buffer pointer (packet)
    size_t sVar7;
    undefined4 uVar8;
    int iVar9;
    uint uVar10;
    void* pvVar11;
    int iVar12;
    uint uVar13;
    undefined4* puVar14;
    void* _Dst;
    size_t* psVar15;
    undefined4* puVar16;
    bool bVar17;
    bool bVar18;
    uint* puStack_2b0; // reusable counter/pointer
    void* local_2a8;   // custom pointer
    undefined4 uStack_2a4; // temporary
    uint* local_2a0;   // pointer into output buffer
    void* pvStack_29c; // temporary
    int local_298;     // vertex/index count accumulator
    uint local_294;    // object index
    uint local_290;    // current object pointer
    uint local_28c;    // part index (for skins/bones)
    int* local_288;    // loop counter
    uint local_284;    // size accumulator for bones
    uint uStack_280;   // temporary size
    uint local_27c;    // count of something (skins?)
    uint local_278;    // count of another thing
    uint local_274;    // loop counter
    uint local_270;    // unique object ID count
    int local_26c;     // object instance counter
    uint local_268;    // temporary size/pointer for bone data
    void* local_264;   // bone data size accumulator
    uint local_260;    // temporary
    uint uStack_25c;   // temp
    uint uStack_258;   // temp
    uint uStack_254;   // temp
    undefined4 local_250; // temp for virtual call outcome
    undefined4 uStack_24c; // temp
    int iStack_240;
    undefined1 auStack_230[16]; // temp buffer for virtual call
    size_t sStack_220;
    int aiStack_218[3]; // array of object pointers (used as list of unique IDs)
    undefined1 local_20c[520]; // bigger scratch buffer (0x208 = 520 bytes)
    
    // --- Initialization ---
    pvVar11 = nullptr;
    local_298 = 0;
    local_294 = 0;
    local_27c = 0;
    local_2a0 = nullptr;
    local_26c = 0;
    local_290 = 0;
    local_284 = 0;
    local_264 = nullptr;
    local_278 = 0;
    local_270 = 0;
    aiStack_218[2] = 0;
    memset(local_20c, 0, 0x1fc); // clear scratch
    local_28c = 0;
    
    if (objectCount == 0) {
        goto allocate_empty;
    }
    
    // First pass: compute sizes and collect unique object IDs
    local_260 = objectArray[local_28c]; // get object pointer
    iVar9 = *(int*)(local_260 + 0x34); // object's vertex count (or instance count)
    local_298 = local_298 + iVar9; // total vertices
    if (iVar9 != 0) {
        iVar12 = *(int*)(local_260 + 0x50); // vertex data array base
        local_274 = iVar9;
        do {
            // Check vertex data flag and if part is transformable
            if ((*(char*)(iVar12 + 4) == '\x01') &&
                (local_294 = local_294 + 1, *(char*)(iVar12 + 6) == '\0')) {
                local_27c = local_27c + 1;
            }
            if ((packingContext != 0) && (*(ushort*)(iVar12 + 0x2c) != 0)) {
                // Bone/packing info present
                cVar2 = *(char*)(iVar12 + 6);
                bVar17 = (*(uint*)(iVar12 + 8) & 0x4000) == 0x4000; // flag: has bones
                bVar18 = cVar2 == '\0';
                uStack_2a4 = (void*)CONCAT13(bVar18, (undefined3)uStack_2a4);
                iVar9 = 0;
                if (cVar2 == '\0') {
                    iVar9 = (!bVar17) * 8 + 0xc; // size per bone influence
                }
                else if ((byte)(cVar2 - 1U) < 4) {
                    iVar9 = ((-(uint)bVar17 & 0xfffffff0) + 0x20); // size for skinned
                }
                local_268 = (uint)*(ushort*)(iVar12 + 0x2c); // number of bones
                local_2a8 = nullptr;
                if (local_268 != 0) {
                    local_288 = *(int**)(iVar12 + 0x90); // bone weight array
                    do {
                        uVar4 = 0;
                        bVar17 = false;
                        if (filterFlags != 0) {
                            // check if this bone is in filter list
                            do {
                                if (*local_288 == *(int*)(packingContext + uVar4 * 8)) {
                                    if (!bVar18) {
                                        local_2a0 = (uint*)((int)local_2a0 +
                                            ((uint)*(ushort*)(iVar12 + 0x38) * iVar9 + 0x7f & 0xffffff80));
                                    }
                                    bVar17 = true;
                                }
                                uVar4 = uVar4 + 1;
                            } while (uVar4 < filterFlags);
                            if (bVar17) {
                                if (bVar18) {
                                    uVar4 = 0;
                                    if (local_270 == 0) goto check_id_list;
                                    goto search_id_list;
                                }
                                break;
                            }
                        }
                        local_288 = local_288 + 4;
                        local_2a8 = (void*)((int)local_2a8 + 1);
                    } while ((int)local_2a8 < (int)local_268);
                }
            }
            goto after_bone_check;
        } while (false); // Actually a loop with goto, restructuring
        // ... (the original has complex control flow; simplified)
    }
    goto after_object_loop;

    // Unique ID list management (based on offset 100 of object)
    search_id_list:
    uVar4 = 0;
    while (uVar4 < local_270) {
        if (*(int*)(local_20c + uVar4 * 4) == *(int*)(iVar12 + 100)) break;
        uVar4++;
    }
check_id_list:
    if (uVar4 == local_270) {
        *(undefined4*)(local_20c + local_270 * 4) = *(undefined4*)(iVar12 + 100);
        local_270 = local_270 + 1;
    }
after_bone_check:
    iVar12 = iVar12 + 0xb0; // next vertex slot (each 0xB0 bytes)
    local_274 = local_274 - 1;
    if (local_274 != 0) goto bone_check_loop; // loop back

    // After processing all vertices of one object:
after_object_loop:
    // If object has a flag (offset 0x24 bit 2), set some bone count
    if ((*(byte*)(local_260 + 0x24) & 4) != 0) {
        local_26c = 4;
    }
    local_290 = local_290 + *(ushort*)(local_260 + 0x44); // accumulate part counts
    uVar4 = (uint)*(ushort*)(local_260 + 0x3c); // number of something (skins?)
    local_284 = local_284 + *(ushort*)(local_260 + 0x46); // accumulate bone/weight counts
    if (uVar4 != 0) {
        piVar5 = (int*)(*(int*)(local_260 + 0x68) + 4); // array of part data
        do {
            if ((*(byte*)((int)piVar5 + 7) & 1) != 0) {
                pvVar11 = (void*)((int)pvVar11 + (*piVar5 * 0x14 + 0x7fU & 0xffffff80) * 2);
            }
            piVar5 = piVar5 + 4;
            uVar4 = uVar4 - 1;
            local_264 = pvVar11;
        } while (uVar4 != 0);
    }
    uVar4 = (uint)*(ushort*)(local_260 + 0x3e); // number of something else (bones?)
    if (uVar4 != 0) {
        piVar5 = *(int**)(local_260 + 0x6c); // array of bone data
        do {
            if (*(char*)((int)piVar5 + 0xb) == '\x01') {
                local_278 = local_278 + (*piVar5 + 0x7fU & 0xffffff80) * 2;
            }
            piVar5 = piVar5 + 4;
            uVar4 = uVar4 - 1;
        } while (uVar4 != 0);
    }
    local_28c = local_28c + 1;
    if (objectCount <= local_28c) goto allocate_empty;
    goto continue_first_pass;

// Jump targets for clarity
bone_check_loop: // from earlier goto
    if ((*(char*)(iVar12 + 4) == '\x01') &&
        (local_294 = local_294 + 1, *(char*)(iVar12 + 6) == '\0')) {
        local_27c = local_27c + 1;
    }
    // ... rest of bone check
    if ((packingContext != 0) && (*(ushort*)(iVar12 + 0x2c) != 0)) {
        // ... as above
    }
    goto after_bone_check_loop;

continue_first_pass:
    local_260 = objectArray[local_28c];
    iVar9 = *(int*)(local_260 + 0x34);
    local_298 = local_298 + iVar9;
    if (iVar9 != 0) {
        iVar12 = *(int*)(local_260 + 0x50);
        local_274 = iVar9;
        goto bone_check_loop;
    }
    goto after_object_loop;

// After first pass, allocate the output buffer
allocate_empty:
    // Compute total sizes
    uVar4 = local_270;
    iVar9 = 0;
    uVar13 = 0;
    if (local_270 != 0) {
        do {
            puVar16 = *(undefined4**)(local_20c + uVar13 * 4);
            if (*(char*)(puVar16 + 7) == '\0') {
                iVar12 = puVar16[5]; // inline data size
            } else {
                (**(code**)(*(int*)*puVar16 + 0x34))((int*)*puVar16, &local_250);
                iVar12 = iStack_240; // size from virtual
            }
            uVar13++;
            iVar9 = iVar9 + iVar12;
        } while (uVar13 < uVar4);
    }
    local_28c = local_290 * 0x50; // skin data size
    local_274 = local_298 * 0xb0; // vertex data size (0xB0 per vertex)
    local_268 = local_298 * 0x80; // transform data size (0x80 per)
    if (local_294 == 0) {
        local_288 = nullptr;
    } else {
        local_288 = (int*)(local_298 << 5); // some temp index
    }
    pvStack_29c = (void*)(local_270 * 0x28); // size of unique ID data blocks
    uStack_258 = (int)pvStack_29c + 0x7f;
    local_294 = local_284 * 0x68 + 0x7f;
    uStack_280 = local_278 + 0x7f;
    local_260 = local_27c * 0x40;
    local_27c = local_28c + 0x7f;
    local_278 = local_268 + 0x7f;
    uStack_25c = (int)local_264 + 0x7f;
    uStack_254 = iVar9 + 0x7f;
    
    // Memory allocation (using function pointer from global)
    puVar6 = (undefined4*)(**(code**)*DAT_01205870)(
        (uStack_258 & 0xffffff80) +
        (uStack_254 & 0xffffff80) + (uStack_25c & 0xffffff80) +
        (local_274 + 0x13f & 0xffffff80) +
        (((int)local_288 + 0x7fU & 0xffffff80) + (local_260 + 0x7f & 0xffffff80)) * 2 +
        ((int)local_2a0 + 0x7fU & 0xffffff80) + local_268 +
        (local_27c & 0xffffff80) + (uStack_280 & 0xffffff80) +
        (local_294 & 0xffffff80),
        &DAT_0110b8f0); // alignment/pool identifier
    
    // Copy header from first object (0x30 dwords)
    puVar16 = (undefined4*)*objectArray;
    puVar14 = puVar6;
    for (iVar9 = 0x30; iVar9 != 0; iVar9--) {
        *puVar14 = *puVar16;
        puVar16++;
        puVar14++;
    }
    
    // Setup output buffer fields
    puVar6[9] = puVar6[9] | local_274 | 2; // flag + vertex data offset
    puVar6[0x1d] = 0;
    *(undefined1*)((int)puVar6 + 0x2d) = 0;
    puVar6[0xc] = 0;
    *(undefined1*)((int)puVar6 + 0x2e) = 0;
    *(undefined2*)(puVar6 + 0xf) = 0;
    *(undefined2*)((int)puVar6 + 0x3e) = 0;
    *(undefined2*)(puVar6 + 0x10) = 0;
    *(undefined2*)((int)puVar6 + 0x42) = 0;
    puVar6[0x1a] = 0;
    puVar6[0x1b] = 0;
    puVar6[0x25] = 0;
    local_26c = 0;
    puVar6[0x24] = local_278; // bone data size
    puVar6[0x14] = puVar6 + 0x30; // pointer after header (base for vertex data)
    uVar4 = (int)puVar6 + local_27c + 0x13f & 0xffffff80;
    puVar6[0x19] = sourceIdentifier;
    puVar6[0x15] = uVar4; // transform data offset
    uVar4 = uVar4 + (uStack_280 & 0xffffff80);
    puVar6[0x16] = -(uint)(local_290 != 0) & uVar4; // skin data offset (conditional)
    uVar13 = local_290 + 0x7f & 0xffffff80;
    uVar4 = uVar4 + uVar13;
    uVar13 = uVar4 + uVar13;
    puVar6[0x17] = -(uint)(local_290 != 0) & uVar4; // second skin offset
    uVar4 = -(uint)(local_268 != 0) & uVar13;
    uVar10 = local_268 + 0x7f & 0xffffff80;
    uVar13 = uVar13 + uVar10;
    local_270 = -(uint)(local_268 != 0) & uVar13;
    uVar13 = uVar13 + uVar10;
    pvVar11 = (void*)(-(uint)(local_294 != 0) & uVar13);
    uVar13 = uVar13 + (local_284 & 0xffffff80);
    _Dst = (void*)(-(uint)(puStack_2b0 != (uint*)0x0) & uVar13);
    uVar13 = uVar13 + ((uint)pvStack_29c & 0xffffff80);
    puVar6[0xd] = local_2a0; // some pointer
    *(short*)(puVar6 + 0x11) = (short)local_298; // vertex count
    *(short*)((int)puVar6 + 0x46) = (short)local_28c; // skin part count
    uStack_24c = 0;
    uStack_280 = -(uint)((short)local_298 != 0) & uVar13;
    local_250 = 0;
    uStack_254 = 0;
    uStack_258 = 0;
    uVar13 = uVar13 + ((uint)local_264 & 0xffffff80);
    pvStack_29c = (void*)(-(uint)((short)local_28c != 0) & uVar13);
    uVar13 = uVar13 + ((uint)local_288 & 0xffffff80);
    local_264 = (void*)(-(uint)(uStack_2a4 != (void*)0x0) & uVar13);
    local_2a0 = (uint*)(uVar13 + (local_260 & 0xffffff80));
    local_284 = (int)local_2a0 + (uStack_25c & 0xffffff80);
    local_268 = uVar4;
    
    // Initialize sub-buffers if needed
    if ((short)local_298 != 0) {
        memset(pvVar11, 0, local_294);
        puVar6[0x20] = pvVar11; // bone weight data base
        puVar6[0x21] = (void*)((int)pvVar11 + (uint)*(ushort*)(puVar6 + 0x11) * 0x28);
    }
    if (*(short*)((int)puVar6 + 0x46) != 0) {
        memset(_Dst, 0, (size_t)puStack_2b0);
        puVar6[0x22] = _Dst; // bone index data base
        puVar6[0x23] = (void*)((uint)*(ushort*)((int)puVar6 + 0x46) * 0x34 + (int)_Dst);
    }
    pvVar11 = local_264;
    if (puVar6[0x24] != 0) {
        memset(local_264, 0, (size_t)uStack_2a4);
        puVar6[0x25] = pvVar11; // skin data base
    }
    
    // Second pass: fill output buffer with data from objects
    puStack_2b0 = (uint*)0x0;
    if (local_278 != 0) {
        local_2a8 = (void*)0x0;
        do {
            puVar16 = (undefined4*)aiStack_218[(int)puStack_2b0]; // object from unique list
            // Get data size and data pointer
            if (*(char*)(puVar16 + 7) == '\0') {
                sVar7 = puVar16[5]; // inline size
                pvVar11 = (void*)puVar16[4]; // inline data
                *(undefined1*)((int)puVar16 + 0x1d) = 1;
            } else {
                // Virtual call to get data
                uStack_2a4 = (void*)0x0;
                (**(code**)(*(int*)*puVar16 + 0x2c))((int*)*puVar16, 0, 0, &uStack_2a4, 0x10);
                pvVar11 = uStack_2a4;
            }
            // Copy data and compress/transform
            memcpy(local_2a0, pvVar11, sVar7);
            FUN_0060b620(sVar7, local_2a0, puVar6[0x25] + (int)local_2a8, 2);
            local_2a0 = (uint*)((int)local_2a0 + sVar7);
            // Release data if needed
            if (*(char*)(puVar16 + 7) == '\0') {
                *(undefined1*)((int)puVar16 + 0x1d) = 0;
            } else {
                (**(code**)(*(int*)*puVar16 + 0x30))((int*)*puVar16);
            }
            local_2a8 = (void*)((int)local_2a8 + 0x28);
            puStack_2b0 = (uint*)((int)puStack_2b0 + 1);
        } while (puStack_2b0 < local_278);
    }
    
    // Reset counters for main object loop
    local_28c = 0;
    local_298 = 0;
    local_294 = 0;
    
    if (objectCount != 0) {
        do {
            local_290 = objectArray[local_294]; // current object
            uVar4 = local_290;
            local_288 = (int*)0x0;
            local_274 = uVar4;
            
            // Process skins (offset 0x3c count, offset 0x68 list)
            if (*(short*)(uVar4 + 0x3c) != 0) {
                puStack_2b0 = (uint*)(local_28c * 0x28);
                local_2a8 = (void*)0x0;
                do {
                    iVar9 = *(int*)(uVar4 + 0x68) + (int)local_2a8;
                    if ((*(byte*)(iVar9 + 0xb) & 1) != 0) {
                        uVar4 = *(int*)(iVar9 + 4) * 0x14 + 0x7fU & 0xffffff80;
                        piVar5 = puVar6 + 0x20;
                        uStack_2a4 = (void*)0x2;
                        do {
                            FUN_0060b620(uVar4, uStack_280, *piVar5 + (int)puStack_2b0, 2);
                            uStack_280 = uStack_280 + uVar4;
                            piVar5++;
                            uStack_2a4 = (void*)((int)uStack_2a4 - 1);
                        } while (uStack_2a4 != (void*)0x0);
                        local_28c++;
                        puStack_2b0 = (uint*)((int)puStack_2b0 + 0x28);
                        uStack_2a4 = (void*)0x0;
                        uVar4 = local_274;
                    }
                    local_2a8 = (void*)((int)local_2a8 + 0x10);
                    local_288 = (int*)((int)local_288 + 1);
                } while (local_288 < (uint)*(ushort*)(uVar4 + 0x3c));
            }
            
            // Process bones (offset 0x3e count, offset 0x6c list)
            local_27c = 0;
            if (*(short*)(uVar4 + 0x3e) != 0) {
                puStack_2b0 = (uint*)(local_298 * 0x34);
                local_2a8 = (void*)0x0;
                do {
                    psVar15 = (size_t*)(*(int*)(uVar4 + 0x6c) + (int)local_2a8);
                    if (*(char*)((int)psVar15 + 0xb) == '\x01') {
                        // Find bone skin data source
                        uVar13 = 0;
                        uStack_2a4 = (void*)0x0;
                        if (*(uint*)(uVar4 + 0x34) != 0) {
                            iVar9 = *(int*)(uVar4 + 0x50);
                            do {
                                if (*(int*)(iVar9 + 0x70) != -1) {
                                    uStack_2a4 = *(void**)(iVar9 + 0x88);
                                    break;
                                }
                                uVar13++;
                                iVar9 = iVar9 + 0xb0;
                            } while (uVar13 < *(uint*)(uVar4 + 0x34));
                        }
                        sVar7 = *psVar15;
                        piVar5 = puVar6 + 0x22;
                        local_288 = (int*)0x2;
                        do {
                            memcpy(pvStack_29c, uStack_2a4, sVar7);
                            FUN_0060c080(psVar15[1], pvStack_29c, *piVar5 + (int)puStack_2b0, 0x12);
                            sVar7 = *psVar15;
                            pvStack_29c = (void*)((int)pvStack_29c + (sVar7 + 0x7f & 0xffffff80));
                            piVar5++;
                            local_288 = (int*)((int)local_288 - 1);
                        } while (local_288 != (int*)0x0);
                        local_298++;
                        puStack_2b0 = (uint*)((int)puStack_2b0 + 0x34);
                        uVar4 = local_274;
                    }
                    local_2a8 = (void*)((int)local_2a8 + 0x10);
                    local_27c++;
                } while (local_27c < *(ushort*)(uVar4 + 0x3e));
            }
            local_294++;
        } while (local_294 < objectCount);
    }
    
    // Third pass: copy object instance data (vertices and transforms) into output
    local_2a0 = prevStateList; // reuse as pointer
    local_288 = (int*)0x0;
    local_28c = 0;
    local_298 = 0;
    local_294 = 0;
    if (objectCount != 0) {
        do {
            local_290 = objectArray[local_294]; // current object
            uVar4 = *(uint*)(local_290 + 0x34); // vertex count
            uStack_2a4 = (void*)(local_26c * 0x80 + puVar6[0x15]); // transform destination
            pvVar11 = (void*)(local_26c * 0xb0 + puVar6[0x14]); // vertex destination
            memcpy(pvVar11, *(void**)(local_290 + 0x50), uVar4 * 0xb0); // copy vertices
            memcpy(uStack_2a4, *(void**)(local_290 + 0x54), uVar4 << 7); // copy transforms
            local_26c = local_26c + uVar4;
            FUN_004bd160(local_290 + 0x10); // post-process function
            
            if (uVar4 != 0) {
                puStack_2b0 = (uint*)((int)pvVar11 + 8); // vertex data after some offset
                uStack_25c = -(int)pvVar11 - 8;
                local_2a8 = uStack_2a4;
                local_274 = uVar4;
                do {
                    uVar4 = DAT_00e2b1a4; // global constant (likely 0x7F or similar)
                    // Set vertex flags and bone references
                    *puStack_2b0 = *puStack_2b0 | 0x402; // flags
                    puStack_2b0[0x15] = 0;
                    puStack_2b0[0x14] = 0;
                    puStack_2b0[0x12] = local_290; // object pointer
                    puStack_2b0[0x29] = uVar4;
                    puStack_2b0[0x28] = uVar4;
                    puStack_2b0[0x27] = uVar4;
                    puStack_2b0[0x26] = uVar4;
                    pvVar11 = (void*)((int)puStack_2b0 + *(int*)(local_290 + 0x50) + uStack_25c);
                    puStack_2b0[6] = (uint)local_2a8; // pointer to transform data
                    puVar1 = puStack_2b0 - 2;
                    // Lock and increment reference count for bone weights (global table lookup)
                    for (piVar5 = *(int**)(DAT_012054ac + (puStack_2b0[1] & 0x1fff) * 4);
                         piVar5 != (int*)0x0; piVar5 = (int*)piVar5[4]) {
                        if (piVar5[3] == puStack_2b0[1]) {
                            if (piVar5 != (int*)0x0) {
                                LOCK();
                                *piVar5 = *piVar5 + 1;
                                UNLOCK();
                            }
                            break;
                        }
                    }
                    // If vertex is dynamic (flag at +6), allocate bone influence buffers
                    if (*(char*)((int)pvVar11 + 6) == '\0') {
                        puStack_2b0[0x1c] = local_268;
                        local_268 = local_268 + 0x40; // allocate 0x40 bytes
                        puVar3 = (uint*)puStack_2b0[0x1c];
                        *puVar3 = uVar4;
                        puVar3[1] = 0;
                        puVar3[2] = 0;
                        puVar3[3] = 0;
                        puVar3[4] = 0;
                        puVar3[5] = uVar4;
                        puVar3[6] = 0;
                        puVar3[7] = 0;
                        puVar3[8] = 0;
                        puVar3[9] = 0;
                        puVar3[10] = uVar4;
                        puVar3[0xb] = 0;
                        puVar3[0xc] = 0;
                        puVar3[0xd] = 0;
                        puVar3[0xe] = 0;
                        puVar3[0xf] = uVar4;
                        puStack_2b0[0x1d] = local_270;
                        local_270 = local_270 + 0x40; // allocate another 0x40
                        puVar3 = (uint*)puStack_2b0[0x1d];
                        *puVar3 = uVar4;
                        puVar3[1] = 0;
                        puVar3[2] = 0;
                        puVar3[3] = 0;
                        puVar3[4] = 0;
                        puVar3[5] = uVar4;
                        puVar3[6] = 0;
                        puVar3[7] = 0;
                        puVar3[8] = 0;
                        puVar3[9] = 0;
                        puVar3[10] = uVar4;
                        puVar3[0xb] = 0;
                        puVar3[0xc] = 0;
                        puVar3[0xd] = 0;
                        puVar3[0xe] = 0;
                        puVar3[0xf] = uVar4;
                    }
                    pvStack_29c = pvVar11;
                    // If there is a previous state list, run delta packing
                    if ((local_2a0 != (uint*)0x0) && ((void*)*local_2a0 == pvVar11)) {
                        FUN_0045a100(puVar1, local_2a0[1]);
                        local_288 = (int*)((int)local_288 + 1);
                        if (local_288 < prevStateCount) {
                            local_2a0 = local_2a0 + 3;
                        } else {
                            local_2a0 = (uint*)0x0;
                        }
                    }
                    // Link vertex to object packet
                    puStack_2b0[0x12] = (uint)puVar6;
                    iVar9 = *(int*)((int)pvVar11 + 0x70);
                    if (*(int*)((int)pvVar11 + 0x68) == -1) {
                        puStack_2b0[0x18] = 0;
                    } else {
                        iVar12 = (*(int*)((int)pvVar11 + 0x68) + local_28c) * 0x28;
                        puStack_2b0[0x17] = puVar6[0x20] + iVar12;
                        puStack_2b0[0x18] = puVar6[0x21] + iVar12;
                    }
                    if (iVar9 == -1) {
                        puStack_2b0[0x1a] = 0;
                        puStack_2b0[0x1b] = 0;
                    } else {
                        iVar9 = (iVar9 + local_298) * 0x34;
                        puStack_2b0[0x1a] = puVar6[0x22] + iVar9;
                        puStack_2b0[0x1b] = puVar6[0x23] + iVar9;
                    }
                    // Process packing (bones/skin) if needed
                    if ((((short)puStack_2b0[9] != 0) && (packingContext != 0)) &&
                        (iVar9 = FUN_00459e90(packingContext), iVar9 != 0)) {
                        uVar4 = *puStack_2b0;
                        if (*(char*)((int)puStack_2b0 - 2) == '\0') {
                            // Find matching unique ID
                            puVar16 = (undefined4*)0x0;
                            uVar13 = 0;
                            if (local_278 != 0) {
                                do {
                                    if (aiStack_218[uVar13] == *(int*)((int)pvStack_29c + 100)) {
                                        puVar16 = (undefined4*)(puVar6[0x25] + uVar13 * 0x28);
                                        break;
                                    }
                                    uVar13++;
                                } while (uVar13 < local_278);
                            }
                            local_260 = (uint)*(ushort*)((int)puStack_2b0 + 0x32);
                            puStack_2b0[0x17] = (uint)puVar16;
                            // Get data pointer for bone weights
                            if (*(char*)(puVar16 + 7) == '\0') {
                                pvVar11 = (void*)puVar16[4];
                                *(undefined1*)((int)puVar16 + 0x1d) = 1;
                            } else {
                                uVar8 = 0;
                                uStack_2a4 = (void*)0x0;
                                if (*(char*)(puVar16 + 3) != '\0') {
                                    uVar8 = 0x3000;
                                }
                                (**(code**)(*(int*)*puVar16 + 0x2c))((int*)*puVar16, 0, 0, &uStack_2a4, uVar8);
                                pvVar11 = uStack_2a4;
                            }
                            // Choose between two packing functions based on flag
                            if ((uVar4 & 0x4000) == 0x4000) {
                                puStack_2b0[0x1f] = (uint)((int)pvVar11 + local_260 * 0xc);
                                FUN_00459ee0(pvStack_29c, filterFlags, packingContext, puVar1);
                                FUN_004595d0();
                            } else {
                                puStack_2b0[0x1f] = (uint)((int)pvVar11 + local_260 * 0x14);
                                FUN_00459ee0(pvStack_29c, filterFlags, packingContext, puVar1);
                                FUN_004594f0();
                            }
                            // Release data
                            if (*(char*)(puVar16 + 7) == '\0') {
                                *(undefined1*)((int)puVar16 + 0x1d) = 0;
                            } else {
                                (**(code**)(*(int*)*puVar16 + 0x30))((int*)*puVar16);
                            }
                        } else {
                            uVar4 = puStack_2b0[0x1f];
                            puStack_2b0[0x1f] = local_284;
                            iVar9 = FUN_00459ee0(pvStack_29c, filterFlags, packingContext, puVar1);
                            if (iVar9 == 0) {
                                puStack_2b0[0x1f] = uVar4;
                            } else {
                                local_284 = local_284 + (iVar9 + 0x7fU & 0xffffff80);
                            }
                        }
                    }
                    // Advance to next vertex
                    puStack_2b0 = puStack_2b0 + 0x2c;
                    local_2a8 = (void*)((int)local_2a8 + 0x80);
                    local_274--;
                } while (local_274 != 0);
            }
            // Update part counters
            local_28c = local_28c + *(ushort*)(local_290 + 0x44);
            local_298 = local_298 + (uint)*(ushort*)(local_290 + 0x46);
            local_294++;
        } while (local_294 < objectCount);
    }
    
    // Final output buffer setup
    puVar6[4] = uStack_258; // final size of packets
    puVar6[5] = uStack_254;
    puVar6[6] = local_250;
    puVar6[7] = uStack_24c;
    
    if (*(short*)(puVar6 + 0x11) != 0) {
        FUN_00459800(); // post-process function (likely compression/endian)
    }
    
    return puVar6; // pointer to the built packet buffer
}