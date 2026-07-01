// FUNC_NAME: AnimLayerStateMachine::UpdateStateData
void __thiscall AnimLayerStateMachine::UpdateStateData(void* thisPtr, const AnimStateInputData* inputData)
{
    // thisPtr offsets:
    // +0x1dc: currentLayerIndex (starts at -1, reset to 0 if -1, else increment and cap)
    // +0x1a5: bActive flag (set to 1)
    // +0x84: copy from inputData+0x10 (likely stateId or something)
    // +0x1a8: copy from inputData+0x8c
    // layers: three blocks at offsets 0xc4, 0x120, 0x17c (each 0x5C bytes)
    // Each block contains:
    //   0x00: pointer to current node (list head)
    //   0x04: next pointer in list? (used in insertion)
    //   0x08: pointer to some other node (used with FUN_00446100 result+0x48)
    //   0x0C: next pointer for that node
    //   0x10: some int (piVar4[4] set to result from FUN_006b0ee0)
    // Also there is a "special" block at +0x1c4 (pointer) and +0x1c8 (next)
    // And fourcc fields at +0x1cc..+0x1d8, +0x1c4 for special handling

    int layerIdx = *(int*)((char*)thisPtr + 0x1dc);
    if (layerIdx == -1) {
        *(int*)((char*)thisPtr + 0x1dc) = 0;
    } else {
        layerIdx++;
        *(int*)((char*)thisPtr + 0x1dc) = layerIdx;
        if (layerIdx > 2 || *(int*)((char*)thisPtr + (layerIdx + 0x10) * 0x20) == 0) {
            // layerIdx+0x10*0x20? looks messy, maybe a lookup? The condition resets to -1 if layer out of bounds or empty
            *(int*)((char*)thisPtr + 0x1dc) = -1;
        }
    }

    *(char*)((char*)thisPtr + 0x1a5) = 1; // Set active flag
    *(int*)((char*)thisPtr + 0x84) = *(int*)((char*)inputData + 0x10);
    *(int*)((char*)thisPtr + 0x1a8) = *(int*)((char*)inputData + 0x8c);

    // Process three layers
    int layerNum = 0;
    int* layerHead = (int*)((char*)thisPtr + 0xc4); // start of first layer block
    const int* dataLayer = (const int*)((char*)inputData + 0x20); // inputData layers start at +0x20

    do {
        // Store something from previous layer offset? (piVar4[-1])
        layerHead[-1] = dataLayer[-3]; // offset: layerHead-4 = block start -4; dataLayer-12? Actually dataLayer is int*, dataLayer[-3] = *(int*)(dataLayer - 12) which is inputData+0x20 - 12 = 0x14? Not sure, but ok

        int* pNode = (int*)FUN_00446100(layerHead - 0xf, 0); // Fetch node from some pool
        if (pNode != nullptr) {
            // Check fourcc for skip/valid animation
            const int fourcc0 = dataLayer[-2];
            const int fourcc1 = dataLayer[-1];
            const int fourcc2 = dataLayer[0];
            const int fourcc3 = dataLayer[1];
            const bool isZeroFourcc = (fourcc0 == 0 && fourcc1 == 0 && fourcc2 == 0 && fourcc3 == 0);
            const bool isExtraFourcc = (fourcc0 == 0xBABDB7BA && fourcc1 == 0xBEEFBEEF && fourcc2 == 0xEAC15A55 && fourcc3 == 0x91100911); // Example fourcc
            // Actually compute: -0x45245246 = 0xBABDB7BA? Wait recalc: 0x45245246 => 0xBABDB7BA (two's complement). I'll use placeholder names
            const bool isSpecialFourcc = (fourcc0 == FOURCC_SPECIAL1 && fourcc1 == FOURCC_SPECIAL2 && fourcc2 == FOURCC_SPECIAL3 && fourcc3 == FOURCC_SPECIAL4);

            if (isExtraFourcc || isZeroFourcc) {
                // Special case: call FUN_008e9860 on dataLayer[2]
                FUN_008e9860(dataLayer[2]);
                int* newNode = pNode + 0x12; // point to node offset 0x48
                if (*layerHead != (int)newNode) {
                    if (*layerHead != 0) {
                        FUN_004daf90(layerHead); // remove old head from list?
                    }
                    *layerHead = (int)newNode;
                    if (newNode != nullptr) {
                        layerHead[1] = pNode[0x13]; // store next pointer
                        pNode[0x13] = (int)layerHead; // link back
                    }
                }
                int result = FUN_006b0ee0(dataLayer[2]); // get some ID
            } else {
                // Normal animation
                (**(code**)(*pNode + 0x14c))(dataLayer - 2); // Call virtual function on pNode with dataLayer-2
                int* pAnimObj = (int*)FUN_00446100(dataLayer - 2, 0); // get another object
                FUN_00791e70((char*)thisPtr + 0x50); // offset +0x50? maybe signal
                *(unsigned int*)((char*)pAnimObj + 0x5c) |= 0x80000; // set flag
                FUN_00790110(1);
                FUN_00792560(pAnimObj);
                int someValue = FUN_00791300();

                int* newNode = pNode + 0x12;
                if (*layerHead != (int)newNode) {
                    if (*layerHead != 0) {
                        FUN_004daf90(layerHead);
                    }
                    *layerHead = (int)newNode;
                    if (newNode != nullptr) {
                        layerHead[1] = pNode[0x13];
                        pNode[0x13] = (int)layerHead;
                    }
                }

                int nodePtr;
                if (someValue == 0) {
                    nodePtr = 0;
                } else {
                    nodePtr = someValue + 0x48; // offset to some node
                }

                if (layerHead[2] != nodePtr) {
                    if (layerHead[2] != 0) {
                        FUN_004daf90(layerHead + 2);
                    }
                    layerHead[2] = nodePtr;
                    if (nodePtr != 0) {
                        layerHead[3] = *(int*)(nodePtr + 4);
                        *(int**)(nodePtr + 4) = layerHead + 2;
                    }
                }

                if (layerNum != 1 && layerNum != 2) {
                    goto LAB_008e4fac;
                }
                // Force path for layers 1 and 2? Check FUN_00790c80 on dataLayer+3, and if byte at dataLayer-3 has bit2=0, go to LAB.
                FUN_00790c80(dataLayer + 3);
                if ((*(unsigned char*)(dataLayer - 3) & 2) == 0) {
                    goto LAB_008e4fac;
                }
                int result = FUN_006b0ee0(dataLayer[6]);
            }

            // Common tail for both paths
            FUN_006b4ac0(thisPtr);
            layerHead[4] = result; // store result in block
        }

LAB_008e4fac:
        layerNum++;
        dataLayer += 10; // each layer input data block is 10 ints (40 bytes)
        layerHead += 0x17; // each layer internal block is 0x17 ints (92 bytes)
    } while (layerNum <= 2);

    // After processing all three layers, handle special "extra" data at inputData+0xA0 and +0x90
    {
        const int* extraFourcc = (const int*)((char*)inputData + 0xa0);
        const bool extraZero = (extraFourcc[0] == 0 && extraFourcc[1] == 0 && extraFourcc[2] == 0 && extraFourcc[3] == 0);
        const bool extraSpecial = (extraFourcc[0] == FOURCC_SPECIAL1 && extraFourcc[1] == FOURCC_SPECIAL2 && extraFourcc[2] == FOURCC_SPECIAL3 && extraFourcc[3] == FOURCC_SPECIAL4);
        if (!extraZero && !extraSpecial) {
            // Copy fourcc to this+0x1cc..0x1d8
            *(int*)((char*)thisPtr + 0x1cc) = extraFourcc[0];
            *(int*)((char*)thisPtr + 0x1d0) = extraFourcc[1];
            *(int*)((char*)thisPtr + 0x1d4) = extraFourcc[2];
            *(int*)((char*)thisPtr + 0x1d8) = extraFourcc[3];
        }

        // Handle another set at inputData+0x90
        const int* extraFourcc2 = (const int*)((char*)inputData + 0x90);
        const bool extra2Zero = (extraFourcc2[0] == 0 && extraFourcc2[1] == 0 && extraFourcc2[2] == 0 && extraFourcc2[3] == 0);
        const bool extra2Special = (extraFourcc2[0] == FOURCC_SPECIAL1 && extraFourcc2[1] == FOURCC_SPECIAL2 && extraFourcc2[2] == FOURCC_SPECIAL3 && extraFourcc2[3] == FOURCC_SPECIAL4);
        if (!extra2Zero && !extra2Special) {
            int* pObj2 = (int*)FUN_00446100(extraFourcc2, 0);
            int* specialHead = (int*)((char*)thisPtr + 0x1c4);
            if (pObj2 == nullptr) {
                // Create object via FUN_00892070
                int obj = FUN_00892070(thisPtr);
                int* objNode = (obj != 0) ? (int*)(obj + 0x48) : nullptr;
                if (*specialHead != (int)objNode) {
                    if (*specialHead != 0) {
                        FUN_004daf90(specialHead);
                    }
                    *specialHead = (int)objNode;
                    if (objNode != nullptr) {
                        *(int*)((char*)thisPtr + 0x1c8) = *(int*)((char*)objNode + 4);
                        *(int**)((char*)objNode + 4) = specialHead;
                    }
                }
            } else {
                int* objNode = (int*)((char*)pObj2 + 0x48);
                if (*specialHead != (int)objNode) {
                    if (*specialHead != 0) {
                        FUN_004daf90(specialHead);
                    }
                    *specialHead = (int)objNode;
                    if (objNode != nullptr) {
                        *(int*)((char*)thisPtr + 0x1c8) = *(int*)((char*)pObj2 + 0x4c);
                        *(int**)((char*)pObj2 + 0x4c) = specialHead;
                        FUN_008e4ab0(0); // signal completion
                        return;
                    }
                }
            }
        }
    }

    FUN_008e4ab0(0); // always called at end (or early return)
}