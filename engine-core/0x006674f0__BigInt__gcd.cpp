// FUNC_NAME: BigInt::gcd
// Function at 0x006674f0 - Computes the greatest common divisor of two big integers using Euclidean algorithm.
// Structure fields: +0x00 flags, +0x04 size (words), +0x08 reserved, +0x0C pointer to word array.

int BigInt::gcd(int *contextPtr, int *src, int *dst)
{
    uint64_t resultA_low; // local_18
    uint64_t resultA_high; // local_10
    uint64_t resultB_low; // local_28
    uint64_t resultB_high; // local_20
    int *workspace;
    int cmp;
    int sizeA, sizeB, minSize;
    unsigned int remSize;
    int err;

    if (*contextPtr == 0) {
        // Context flag zero: simple copy
        if (*src == 0) {
            // Source is zero: clear destination
            dst[2] = 0;
            *dst = 0;
            memset((void *)dst[3], 0, dst[1] * 4);
            return 0;
        }
        if (src == dst) {
            // Same pointer: just clear field
            goto done;
        }
    } else {
        if (*src != 0) {
            if (*contextPtr != 0) {
                // Allocate workspace for the Euclidean algorithm (4 64-byte blocks)
                workspace = (int *)calloc(4, 0x40);
                if (workspace == NULL) {
                    return -2;
                }
                // Initialize temporary big integer registers
                resultA_low = 0x4000000000;
                resultA_high = (uint64_t)workspace << 32; // store pointer in high part

                err = bigintInitContext(); // FUN_00665ce0
                if (err != 0) {
                    return err;
                }
                err = bigintSetup(); // FUN_006677e0
                if (err == 0) {
                    // Clear low bits of high parts
                    resultB_high &= 0xffffffff00000000;
                    resultA_high &= 0xffffffff00000000;

                    sizeA = bigintSize(); // FUN_00665c90
                    sizeB = bigintSize();
                    minSize = (sizeA < sizeB) ? sizeA : sizeB;

                    // Reduce initial values to the common size
                    if (minSize >= 1 &&
                        ((err = bigintModReduce(&resultA_low, minSize, &resultA_low, 0)) == 0) &&
                        ((err = bigintModReduce(&resultB_low, minSize, &resultB_low, 0)) == 0) &&
                        ((sizeA == minSize) ||
                         ((err = bigintModReduce(&resultA_low, sizeA - minSize, &resultA_low, 0)) == 0)) &&
                        ((sizeB == minSize) ||
                         ((err = bigintModReduce(&resultB_low, sizeB - minSize, &resultB_low, 0)) == 0)))
                    {
                        // Euclidean algorithm loop
                        while ((int)resultB_low != 0) {
                            cmp = bigintCompare(); // FUN_00665c30
                            uint64_t tempA_low = resultA_low;
                            uint64_t tempA_high = resultA_high;
                            if (cmp == 1) {
                                // Swap A and B
                                resultA_low = resultB_low;
                                resultA_high = resultB_high;
                                resultB_low = tempA_low;
                                resultB_high = tempA_high;
                            }
                            err = bigintSubtract(&resultB_low); // FUN_0066c8d0
                            if (err != 0) break;

                            remSize = bigintSize(&resultB_low, 0); // FUN_00665c90
                            err = bigintModReduce(&resultB_low, remSize); // FUN_00666300
                            if (err != 0) break;
                        }
                        // Finalize computation
                        err = bigintFinalize(minSize); // FUN_00668e40
                        if (err == 0) {
                            dst[2] = 0; // Clear field
                        }
                    }
                }
                bigintCleanup(); // FUN_00665b40
                bigintCleanup();
                return err;
            }
            // Fall through to simple path
        }
        if (contextPtr == dst) {
            goto done;
        }
    }
    // Simple path: initialize and clear
    err = bigintInitContext();
    if (err != 0) return err;

done:
    dst[2] = 0;
    return 0;
}