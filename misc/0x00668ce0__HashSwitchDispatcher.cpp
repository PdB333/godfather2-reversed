// FUNC_NAME: HashSwitchDispatcher
void HashSwitchDispatcher(int* inputA, int* inputB, int* output)
{
    int sizeA = inputA[0];                // +0x00: size of first buffer
    int sizeB = inputB[0];                // +0x00: size of second buffer
    uint unequalFlag = (uint)(inputA[2] != inputB[2]); // +0x08: compare keys

    int minSize = sizeA;
    if (sizeB <= sizeA) {
        minSize = sizeB;
    }

    if (minSize > 0x15d) {
        // Large input (> 349)
        FUN_0066aa30(inputB, output);
        output[2] = (int)unequalFlag;
        return;
    }

    minSize = sizeA;
    if (sizeB <= sizeA) {
        minSize = sizeB;
    }
    if (minSize > 0x6c) {
        // Medium input (> 108, <= 349)
        FUN_00667ee0(inputB, output);
        output[2] = (int)unequalFlag;
        return;
    }

    int totalSize = sizeA + 1 + sizeB;
    if (totalSize < 0x200) {
        // Combined sizes fit within 512
        if (sizeB <= sizeA) {
            sizeA = sizeB;
        }
        if (sizeA < 0x101) {
            // Small input (< 257)
            FUN_006651b0(inputB, output, totalSize);
            output[2] = (int)unequalFlag;
            return;
        }
    }

    // Fallback default
    FUN_0066c2f0(inputA, inputB, output, totalSize);
    output[2] = (int)unequalFlag;
}