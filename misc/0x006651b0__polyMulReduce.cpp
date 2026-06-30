// FUNC_NAME: polyMulReduce
// Function at 0x006651b0: Polynomial multiplication and reduction (CRC-like) for EA EARS checksum
// Multiplies two polynomial coefficient arrays (32-bit per coefficient) and reduces modulo a 28-bit polynomial.
// param_1[0] = count of coefficients in first polynomial
// param_1[3] = pointer to first coefficient array
// param_2[0] = count of coefficients in second polynomial
// param_2[3] = pointer to second coefficient array
// param_3[0] = (in/out) count of coefficients in output; param_3[1] = allocated capacity; param_3[3] = output array
// param_4 = expected output count (must be <= param_3[1])
// Returns 0 on success, non-zero on error.

int __thiscall polyMulReduce(int* param_1, int* param_2, int* param_3, int param_4)
{
    uint* puVar1;
    uint uVar2;
    undefined4* puVar3;
    uint uVar4;
    uint uVar5;
    int iVar6;
    uint uVar7;
    undefined4* puVar8;
    int iVar9;
    uint* puVar10;
    undefined8 uVar11;
    uint* local_1020;
    uint* local_101c;
    int local_1018;
    int local_1014;
    size_t local_1008;
    uint local_1004[1024];  // stack buffer for intermediate product (2*param_4 32-bit halves)
    undefined4 uStack_4;
    
    uStack_4 = 0x6651ba;
    // Check if result fits and initial condition passes
    if ((param_4 <= param_3[1]) || (iVar6 = FUN_00667740(), iVar6 == 0))
    {
        local_1008 = param_4 * 8;  // byte size of product (2 halves per coefficient)
        _memset(local_1004 + 1, 0, local_1008);
        local_1014 = *param_1;     // first polynomial degree count
        if (0 < local_1014)
        {
            puVar3 = (undefined4*)param_2[3];   // second polynomial coefficients
            local_101c = (uint*)param_1[3];     // first polynomial coefficients
            iVar6 = *param_2;                   // second polynomial count
            local_1020 = local_1004 + 1;        // destination accumulator (skip first uint)
            local_1018 = param_4;               // limit for inner loop
            do {
                local_1004[0] = *local_101c;    // current coefficient of first poly
                iVar9 = iVar6;
                if (local_1018 <= iVar6) {
                    iVar9 = local_1018;
                }
                puVar8 = puVar3;
                puVar10 = local_1020;
                if (0 < iVar9) {
                    do {
                        // Multiply and accumulate 64-bit result
                        uVar11 = __allmul(*puVar8, 0, local_1004[0], 0);
                        uVar2 = *puVar10;
                        *puVar10 = *puVar10 + (uint)uVar11;
                        puVar10[1] = puVar10[1] + (int)((ulonglong)uVar11 >> 0x20) +
                                     (uint)CARRY4(uVar2, (uint)uVar11);
                        iVar9 = iVar9 + -1;
                        puVar8 = puVar8 + 1;
                        puVar10 = puVar10 + 2;
                    } while (iVar9 != 0);
                }
                local_101c = local_101c + 1;
                local_1020 = local_1020 + 2;
                local_1018 = local_1018 + -1;
                local_1014 = local_1014 + -1;
            } while (local_1014 != 0);
        }
        // Reduction step: fold overflow from each 32-bit coefficient into the next,
        // keeping only 28 bits (mask 0xFFFFFFF)
        iVar6 = *param_3;
        puVar10 = (uint*)param_3[3];
        iVar9 = 1;
        *param_3 = param_4;  // set output count
        if (1 < param_4) {
            do {
                uVar4 = local_1004[iVar9 * 2];           // low 32 bits of coefficient iVar9
                uVar7 = (&local_1008)[iVar9 * 2] >> 0x1c | uVar4 << 4;  // high 4 bits from previous high
                puVar1 = local_1004 + iVar9 * 2U + 1;    // high 32 bits
                uVar2 = *puVar1;
                *puVar1 = *puVar1 + uVar7;               // add carried bits
                uVar5 = (&local_1008)[iVar9 * 2];
                local_1004[iVar9 * 2U + 2] =             // propagate carry to next low
                    local_1004[iVar9 * 2U + 2] + (uVar4 >> 0x1c) + (uint)CARRY4(uVar2, uVar7);
                *puVar10 = uVar5 & 0xfffffff;            // store 28-bit reduced coefficient
                iVar9 = iVar9 + 1;
                puVar10 = puVar10 + 1;
            } while (iVar9 < param_4);
        }
        // Handle last coefficient and zero out remaining output if original size was larger
        *puVar10 = *(uint*)((int)&local_1008 + local_1008) & 0xfffffff;
        if (iVar9 < iVar6) {
            for (iVar6 = iVar6 - iVar9; puVar10 = puVar10 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
                *puVar10 = 0;
            }
        }
        // Trim trailing zeros from output
        iVar6 = *param_3;
        if (0 < iVar6) {
            do {
                if (*(int*)(param_3[3] + -4 + *param_3 * 4) != 0) break;
                iVar6 = *param_3 + -1;
                *param_3 = iVar6;
            } while (0 < iVar6);
            iVar6 = *param_3;
        }
        if (iVar6 == 0) {
            param_3[2] = 0;  // some flag if output is zero
        }
        iVar6 = 0;
    }
    return iVar6;
}