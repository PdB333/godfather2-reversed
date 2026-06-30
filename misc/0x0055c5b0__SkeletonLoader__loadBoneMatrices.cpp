// FUNC_NAME: SkeletonLoader::loadBoneMatrices
void __thiscall SkeletonLoader::loadBoneMatrices(SkeletonLoaderContext* thisContext) {
    BoneNode* currentNode;
    int nodeType;
    int* boneOut;
    int iVar6;
    int* piVar4;
    BoneNode** ppuVar5;
    BoneNode** ppuVar7;
    bool bVar8;
    // Iterator state
    char iterationMode; // local_64 – 0 = linked list iteration, 1 = array iteration
    int arrayBase;      // local_60 – base pointer for array mode
    int* arrayPtr;      // local_5c – current ptr in array mode
    uint arrayIndex;    // local_58 – current index (array or linked list position)
    uint arrayCount;    // local_54 – total count
    int* local_50;      // local_50 – current node data pointer
    short field_6;      // local_4c? Actually local_4c is used as short index
    int nodeData;       // local_48
    BoneNode** local_8; // local_8 – current linked list node pointer

    // Initialize iterator – likely sets up tree traversal
    FUN_00546960();
    // Initialize with some magic number (0x7f1d424f)
    FUN_0043aff0(thisContext, 0x7f1d424f);

    ppuVar7 = local_8;
    iVar6 = DAT_00e2b1a4; // global constant (possibly identity rotation or zero)

    do {
        // Determine if iteration should continue
        if (iterationMode == '\0') {
            bVar8 = *ppuVar7 == (BoneNode*)0x0; // linked list end
        } else {
            bVar8 = arrayIndex == arrayCount; // array end
        }
        if (bVar8) {
            return;
        }

        // Select pointer to current node's data
        if (iterationMode == '\0') {
            ppuVar5 = ppuVar7; // linked list node
        } else {
            ppuVar5 = &local_50; // array element
        }

        // Determine node type: check if short at offset 6 equals 0x25e3 (magic number)
        if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
            // Special node type – use pointer stored at offset 4 (second pointer)
            nodeType = (int)(uint)*(ushort*)(ppuVar5 + 1); // extract type from second word?
        } else {
            nodeType = (int)ppuVar5[1]; // normal – second pointer is the type
        }

        switch(nodeType) {
        case 0: // Bone type 0 – write matrix at offset 0x00 of output buffer
            // Determine the source of bone data (handle magic type)
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0; // fallback pointer
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5); // base + offset
                }
            } else {
                ppuVar5 = ppuVar5 + 2; // skip type field
            }
            // Write 4 values to the output buffer (matrix row? or transform)
            piVar4 = *(int**)(thisContext + 8); // output buffer base
            *piVar4 = (int)*ppuVar5;
            piVar4[1] = (int)ppuVar5[1];
            piVar4[2] = (int)ppuVar5[2];
            piVar4[3] = iVar6; // global constant
            goto switch_default;

        case 1: // Bone type 1 – write at offset 0x30
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            piVar4 = (int*)(*(int*)(thisContext + 8) + 0x30);
            goto LAB_0055c6ab;

        case 2: // Bone type 2 – write at offset 0x60
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            piVar4 = (int*)(*(int*)(thisContext + 8) + 0x60);
            goto LAB_0055c6ab;

        case 3: // Bone type 3 – write at offset 0x90
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            piVar4 = (int*)(*(int*)(thisContext + 8) + 0x90);
            // Fall through to LAB_0055c6ab

LAB_0055c6ab:
            // Common write for cases 1,2,3
            *piVar4 = (int)*ppuVar5;
            piVar4[1] = (int)ppuVar5[1];
            piVar4[2] = (int)ppuVar5[2];
            piVar4[3] = iVar6;
            goto switch_default;

        case 4: // Bone type 4 – write at offset 0x10, then init child list at 0x20
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            {
                int* outBuf = *(int**)(thisContext + 8);
                outBuf[0x10/4] = (int)*ppuVar5;
                outBuf[0x14/4] = (int)ppuVar5[1];
                outBuf[0x18/4] = (int)ppuVar5[2];
                outBuf[0x1c/4] = iVar6;
                iVar6 = *(int*)(thisContext + 8) + 0x20; // set up child list pointer to call FUN_00546cb0
            }
            break;

        case 5: // Bone type 5 – write at offset 0x40, init child list at 0x50
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            {
                int* outBuf = *(int**)(thisContext + 8);
                outBuf[0x40/4] = (int)*ppuVar5;
                outBuf[0x44/4] = (int)ppuVar5[1];
                outBuf[0x48/4] = (int)ppuVar5[2];
                outBuf[0x4c/4] = iVar6;
                iVar6 = *(int*)(thisContext + 8) + 0x50;
            }
            break;

        case 6: // Bone type 6 – write at offset 0x70, init child list at 0x80
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            {
                int* outBuf = *(int**)(thisContext + 8);
                outBuf[0x70/4] = (int)*ppuVar5;
                outBuf[0x74/4] = (int)ppuVar5[1];
                outBuf[0x78/4] = (int)ppuVar5[2];
                outBuf[0x7c/4] = iVar6;
                iVar6 = *(int*)(thisContext + 8) + 0x80;
            }
            break;

        case 7: // Bone type 7 – write at offset 0xa0, init child list at 0xb0
            if (iterationMode == '\0') {
                ppuVar5 = ppuVar7;
            } else {
                ppuVar5 = &local_50;
            }
            if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
                if (*ppuVar5 == (BoneNode*)0x0) {
                    ppuVar5 = (BoneNode**)&DAT_00e2e5d0;
                } else {
                    ppuVar5 = (BoneNode**)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            } else {
                ppuVar5 = ppuVar5 + 2;
            }
            {
                int* outBuf = *(int**)(thisContext + 8);
                outBuf[0xa0/4] = (int)*ppuVar5;
                outBuf[0xa4/4] = (int)ppuVar5[1];
                outBuf[0xa8/4] = (int)ppuVar5[2];
                outBuf[0xac/4] = iVar6;
                iVar6 = *(int*)(thisContext + 8) + 0xb0;
            }
            break;

        default:
            goto switch_default;
        }

        // After writing the bone matrix, call FUN_00546cb0 on the child list pointer (iVar6)
        // This likely initializes an empty child list for the bone
        FUN_00546cb0(iVar6);
        iVar6 = DAT_00e2b1a4; // reset iVar6 to the global constant

switch_default:
        // Advance iterator
        if (iterationMode == '\0') {
            // Linked list mode: move to next node using the offset stored in *ppuVar7
            if ((int)arrayIndex < 0) {
                local_8 = (BoneNode**)((int)ppuVar7 + (int)*ppuVar7); // forward link
                FUN_0043b140(); // some iterator function?
                ppuVar7 = local_8;
            } else if ((int)arrayIndex < (int)(arrayCount - 1)) {
                arrayIndex = arrayIndex + 1;
                local_8 = (BoneNode**)((int)ppuVar7 + (int)*ppuVar7); // next
                ppuVar7 = (BoneNode**)((int)ppuVar7 + (int)*ppuVar7);
            } else {
                local_8 = (BoneNode**)&DAT_01163cf8; // end sentinel
                ppuVar7 = (BoneNode**)&DAT_01163cf8;
            }
        } else {
            // Array mode: advance index
            arrayIndex = arrayIndex + 1;
            if (arrayIndex != arrayCount) {
                field_6 = (short)arrayIndex;
                // Check bit in bitmask to see if node is present
                if ((*(byte*)((arrayIndex >> 3) + arrayBase) & (byte)(1 << ((byte)arrayIndex & 7))) == 0) {
                    // Node present: get data from array
                    local_48 = *arrayPtr;
                    local_50 = arrayPtr; // set current node to this array element
                    arrayPtr = arrayPtr + 1;
                } else {
                    // Node missing: set current node to null
                    local_50 = (int*)0x0;
                    local_48 = 0;
                }
            }
        }
    } while(true);
}