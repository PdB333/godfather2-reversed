// FUNC_NAME: DecompressStream
// Function address: 0x00662a30
// Role: Decompression routine (likely LZ77/Huffman) used in EARS engine.
// Parameters:
//   streamContext - pointer to structure with: +0x00: size, +0x0C: data pointer? (offset 3*4)
//   compressedInput - pointer to compressed data
//   decompressedOutput - pointer to output buffer
//   mode - some mode/parameter (e.g., window size index?)
// Returns: 0 on success, 1 on allocation error, 0xD on other errors.

int DecompressStream(int *streamContext, void *compressedInput, void *decompressedOutput, int *mode) {
    bool bVar1;
    int iVar2;
    int iVar3;
    void *pvVar4;
    uint uVar5;
    int iVar6;
    undefined4 uVar7;
    int iVar8;
    undefined4 *puVar9;
    uint uVar10;
    uint local_4c;
    int local_44;
    void *local_40;
    void *local_3c;
    uint local_38;
    int local_34[3];
    void *local_28;
    undefined4 local_24[9];

    // Allocate buffer for decompression state (size = 0x40)
    local_28 = calloc(4, 0x40);
    if (local_28 == (void *)0x0) {
        iVar3 = 0;
        while ((DAT_00e2747c)[iVar3 * 2] != -2) {
            iVar3 = iVar3 + 1;
            if (2 < iVar3) {
                return 1;
            }
        }
        // Fallthrough to error return
        return *(undefined4 *)(&UNK_00e27480 + iVar3 * 8);
    }

    local_34[0] = 0;
    local_34[1] = 0x40;
    local_34[2] = 0;

    // Calculate allocation size based on mode
    iVar2 = FUN_00665720(*mode * 0x38); // Likely allocates temporary space
    if (iVar2 == 0) {
        // Initialize bitstream reader
        iVar2 = FUN_00665d70(local_34, mode, local_34, 0);
    }
    if (iVar2 != 0) {
        FUN_00665b40(); // Cleanup
        iVar3 = 0;
        while (iVar2 != (DAT_00e2747c)[iVar3 * 2]) {
            iVar3 = iVar3 + 1;
            if (2 < iVar3) {
                return 1;
            }
        }
        return *(undefined4 *)(&UNK_00e27480 + iVar3 * 8);
    }

    iVar3 = 0;
    do {
        pvVar4 = malloc(0x20);
        if (pvVar4 == (void *)0x0) {
            goto LAB_00662b2b; // allocation failure
        } else {
            iVar2 = FUN_00667820(pvVar4, (int)pvVar4 + 0x10, 0); // Initialize node
            if (iVar2 != 0) {
                free(pvVar4);
                goto LAB_00662b2b;
            }
        }
        local_24[iVar3] = (int)pvVar4;
        if (pvVar4 == (void *)0x0) {
            iVar2 = 0;
            if (0 < iVar3) {
                do {
                    pvVar4 = (void *)local_24[iVar2];
                    if (pvVar4 != (void *)0x0) {
                        FUN_00665b80(pvVar4, (int)pvVar4 + 0x10, 0);
                        free(pvVar4);
                    }
                    iVar2 = iVar2 + 1;
                } while (iVar2 < iVar3);
            }
            pvVar4 = local_28;
            if (local_28 != (void *)0x0) {
                memset(local_28, 0, local_34[0] * 4);
                free(pvVar4);
            }
            return 0xD;
        }
        iVar3 = iVar3 + 1;
    } while (iVar3 < 8);

    // Allocate an extra node for temporary use
    local_3c = malloc(0x20);
    local_40 = local_3c;
    if (local_3c == (void *)0x0) {
        goto LAB_00662b76;
    } else {
        iVar3 = FUN_00667820(local_3c, (int)local_3c + 0x10, 0);
        if (iVar3 != 0) {
            free(local_3c);
            goto LAB_00662b76;
        }

        // Initialize Huffman trees or LZ77 structures
        iVar3 = FUN_006624a0(compressedInput, local_24[0], local_34); // Copy/transform?
        if (((iVar3 == 0) && (iVar3 = FUN_006624a0(local_24[0], local_24[0], local_34), iVar3 == 0)) &&
            (iVar3 = FUN_006624a0(local_24[0], local_24[0], local_34), iVar3 == 0)) {
            iVar3 = 9;
            puVar9 = local_24;
            do {
                iVar2 = FUN_006626f0(*puVar9, compressedInput, puVar9[1], mode, local_34); // Decode
                if (iVar2 != 0) goto LAB_00662b7a;
                iVar3 = iVar3 + 1;
                puVar9 = puVar9 + 1;
            } while (iVar3 < 0x10);

            // Main decompression loop
            iVar3 = FUN_00665ce0(); // Check for end-of-stream?
            if ((iVar3 == 0) && (iVar3 = FUN_00665ce0(), iVar3 == 0)) {
                iVar3 = 0;
                local_44 = 1; // Represents bit count or length
                iVar2 = *streamContext + -1; // Size minus one?
                bVar1 = true; // First bit flag?
                uVar10 = 0; // Bit buffer

                do {
                    do {
                        iVar8 = 0;
                        local_4c = 0;
                        do {
                            local_44 = local_44 + -1;
                            if (local_44 == 0) {
                                if (iVar2 == -1) {
                                    if (((iVar3 != 2) || (iVar8 < 1)) || (iVar3 = 0, iVar8 < 1))
                                        goto LAB_00662f1a;
                                    goto LAB_00662e81;
                                }
                                uVar10 = *(uint *)(streamContext[3] + iVar2 * 4); // Read next word
                                iVar2 = iVar2 + -1;
                                local_44 = 0x1c; // 28 bits remaining?
                            }
                            local_38 = uVar10 * 2;
                            uVar5 = uVar10 >> 0x1b & 1; // Extract MSB
                            uVar10 = local_38; // Shift left by 1
                            if (iVar3 == 0) {
                                if (uVar5 == 0) continue;
                            } else if ((iVar3 == 1) && (uVar5 == 0)) {
                                iVar6 = FUN_006624a0(decompressedOutput, decompressedOutput, local_34);
                                uVar10 = local_38;
                                if (iVar6 != 0) goto LAB_00662b7a;
                                continue;
                            }
                            iVar8 = iVar8 + 1;
                            iVar3 = 2;
                            local_4c = local_4c | uVar5 << (4U - (char)iVar8 & 0x1f);
                        } while (iVar8 != 4);

                        if (!bVar1) {
                            iVar3 = 0;
                            do {
                                iVar8 = FUN_006624a0(decompressedOutput, decompressedOutput, local_34);
                                if (iVar8 != 0) goto LAB_00662b7a;
                                iVar3 = iVar3 + 1;
                            } while (iVar3 < 4);
                            iVar3 = FUN_006626f0(decompressedOutput, (&local_44)[local_4c], decompressedOutput, mode, local_34);
                            if (iVar3 != 0) break;
                            iVar3 = 1;
                            uVar10 = local_38;
                            continue;
                        }
                        iVar3 = FUN_00665ce0();
                        if ((iVar3 != 0) || (iVar3 = FUN_00665ce0(), iVar3 != 0)) break;
                        iVar3 = 1;
                        bVar1 = false;
                        uVar10 = local_38;
                    } while( true );
                }
            }
        }
    }

LAB_00662b7a:
    uVar7 = 0xD; // Error code

LAB_00662b7f:
    // Cleanup: free temporary nodes
    pvVar4 = local_3c;
    if (local_3c != (void *)0x0) {
        FUN_00665b80(local_3c, (int)local_3c + 0x10, 0);
        free(pvVar4);
    }
    iVar3 = 0;
    do {
        pvVar4 = (void *)local_24[iVar3];
        if (pvVar4 != (void *)0x0) {
            FUN_00665b80(pvVar4, (int)pvVar4 + 0x10, 0);
            free(pvVar4);
        }
        pvVar4 = local_28;
        iVar3 = iVar3 + 1;
    } while (iVar3 < 8);
    if (local_28 != (void *)0x0) {
        memset(local_28, 0, local_34[0] * 4);
        free(pvVar4);
    }
    return uVar7;

    // Additional loop for handling continuation
    while (iVar3 = iVar3 + 1, iVar3 < iVar8) {
    LAB_00662e81:
        if ((!bVar1) && (iVar2 = FUN_006624a0(decompressedOutput, decompressedOutput, local_34), iVar2 != 0))
            goto LAB_00662b7a;
        local_4c = local_4c * 2;
        if ((local_4c & 0x10) != 0) {
            if (bVar1) {
                iVar2 = FUN_00665ce0();
                if ((iVar2 != 0) || (iVar2 = FUN_00665ce0(), iVar2 != 0)) goto LAB_00662b7a;
                bVar1 = false;
            } else {
                iVar2 = FUN_006626f0(decompressedOutput, local_40, decompressedOutput, mode, local_34);
                if (iVar2 != 0) goto LAB_00662b7a;
            }
        }
    }

LAB_00662f1a:
    uVar7 = 0; // Success
    goto LAB_00662b7f;
}