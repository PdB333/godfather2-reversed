// FUNC_NAME: MathUtils::generateWindowKernel
void __cdecl GenerateWindowKernel(int inputLen, float centerScale, int maxIndex, float weightScale, int windowType, int* outLowerBound, int* outUpperBound, float* outWeights, float sigma)
{
    float* pfVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;

    // Step 1: Compute the central value after scaling by (inputLen + 0.5)
    float base = (float)(inputLen + (int)0.5f) * centerScale; // DAT_00e2cd54 is 0.5
    // Compute lower bound of the window, clamped to 0
    float lowerFloat = (base - sigma) + 0.5f; // in_XMM2_Da is sigma
    if (lowerFloat < 0.0f) {
        lowerFloat = 0.0f;
    }
    int lower = (int)lowerFloat;

    // Compute upper bound, clamped to maxIndex
    float upperFloat = base + sigma + 0.5f;
    if ((float)maxIndex <= upperFloat) {
        upperFloat = (float)maxIndex;
    }
    int upper = (int)upperFloat;

    int kernelLength = upper - lower;
    float sumWeights = 0.0f;
    int index = lower;
    float fVar10_local = 0.5f; // DAT_00e2cd54
    float fVar11_local = 1.0f; // DAT_00e2b1a4  (normalization factor, may be changed later)
    pfVar1 = outWeights;

    do {
        if (upper <= index) {
            // Normalize the kernel if sum is non-zero
            if (sumWeights != 0.0f) {
                fVar11_local = 1.0f / sumWeights; // Actually fVar11_local = fVar11_local / sumWeights, but fVar11_local is 1.0 initially
            }
            // Apply normalization to output buffer (unrolled for length > 3)
            int i = 0;
            if (3 < kernelLength) {
                pfVar1 = outWeights + 2;
                int loopCount = ((kernelLength - 4) / 4) + 1;
                i = loopCount * 4;
                do {
                    pfVar1[-2] = pfVar1[-2] * fVar11_local;
                    pfVar1[-1] = fVar11_local * pfVar1[-1];
                    *pfVar1 = *pfVar1 * fVar11_local;
                    pfVar1[1] = pfVar1[1] * fVar11_local;
                    pfVar1 += 4;
                    loopCount--;
                } while (loopCount != 0);
            }
            for (; i < kernelLength; i++) {
                outWeights[i] = fVar11_local * outWeights[i];
            }
            *outUpperBound = upper;
            *outLowerBound = lower;
            return;
        }

        // Compute distance from center, scaled by weightScale
        fVar8 = (((float)index - base) + fVar10_local) * weightScale;
        // Determine weight based on windowType
        if (windowType < 1) {
            fVar9 = 0.0f;
        } else if (windowType < 3) {
            // Triangular window with clipped support
            if ((fVar8 < 0.0001f) || (fVar10_local <= fVar8)) { // DAT_00e44718 is small epsilon
                fVar9 = 0.0f;
            } else {
                fVar9 = 1.0f - fVar8 / fVar10_local;
            }
        } else if (windowType == 3) {
            // Gaussian or other window computed by helper
            fVar8 = ComputeWindowFunction(fVar8); // FUN_0061c7c0
            fVar9 = fVar8;
            fVar10_local = 0.5f; // Reinitialize local copies from globals
            fVar11_local = 1.0f;
        } else {
            fVar9 = 0.0f;
        }

        *pfVar1 = fVar9;
        index++;
        sumWeights += fVar9;
        pfVar1++;
    } while (true);
}