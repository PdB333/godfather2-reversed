// FUNC_NAME: BigInt::scalarMultiply
int __thiscall BigInt::scalarMultiply(BigInt *thisResult, BigInt *input, int scalar)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t *puVar8;
    uint64_t uVar9;
    uint32_t *local_18;
    int local_14;
    int local_10;

    // Calculate new size: input->numLimbs * 2 + 1
    iVar3 = input->numLimbs * 2 + 1;
    if ((iVar3 < 0x200) && (input->numLimbs < 0x100)) {
        // Use fast path (small numbers)
        iVar3 = FUN_00664fa0(thisResult, input, scalar);
        return iVar3;
    }

    // Check if new size fits in capacity or some condition FIXME
    if ((iVar3 <= thisResult->capacity) || (iVar4 = FUN_00667740(), iVar4 == 0)) {
        thisResult->numLimbs = iVar3;
        iVar3 = input->numLimbs;
        local_10 = 0;
        if (0 < iVar3) {
            do {
                puVar8 = (uint32_t *)(thisResult->limbs + local_10);
                uVar1 = *puVar8; // Not used? Actually it's the start limb
                local_18 = input->limbs;
                uVar7 = 0; // carry
                local_14 = 0;
                if (0 < iVar3) {
                    do {
                        // Multiply input limb by scalar and add product with carry
                        uVar9 = __allmul(*local_18, 0, (uVar1 * scalar) & 0xFFFFFFF, 0);
                        uVar2 = *puVar8;
                        uVar5 = (uint32_t)uVar9 + uVar2;
                        uVar6 = uVar5 + uVar7;
                        local_18++;
                        *puVar8 = uVar6 & 0xFFFFFFF; // keep 28 bits
                        uVar7 = (uVar6 >> 0x1c) | 
                                ((uint32_t)((uint64_t)uVar9 >> 32) + (uint32_t)((uint32_t)uVar9 + uVar2 < uVar2) + (uint32_t)(uVar5 + uVar7 < uVar5)) * 0x10;
                        local_14++;
                        puVar8++;
                    } while (local_14 < input->numLimbs);

                    // Propagate remaining carry
                    for (; uVar7 != 0; uVar7 >>= 0x1c) {
                        *puVar8 = *puVar8 + uVar7;
                        uVar7 = *puVar8;
                        *puVar8 = *puVar8 & 0xFFFFFFF;
                        puVar8++;
                    }
                }
                iVar3 = input->numLimbs;
                local_10++;
            } while (local_10 < iVar3);
        }

        // Trim leading zeros
        iVar3 = thisResult->numLimbs;
        if (0 < iVar3) {
            do {
                if (*(thisResult->limbs + thisResult->numLimbs - 1) != 0) break;
                iVar3 = thisResult->numLimbs - 1;
                thisResult->numLimbs = iVar3;
            } while (0 < iVar3);
            iVar3 = thisResult->numLimbs;
        }

        if (iVar3 == 0) {
            thisResult->sign = 0;
        }

        // Post-processing: possibly free old limbs, then convert to a standard form?
        FUN_0066a4d0(input->numLimbs);
        iVar3 = FUN_00665c30();
        if (iVar3 != -1) {
            iVar3 = FUN_0066c8d0(thisResult);
            return iVar3;
        }
        iVar4 = 0;
    }
    return iVar4;
}