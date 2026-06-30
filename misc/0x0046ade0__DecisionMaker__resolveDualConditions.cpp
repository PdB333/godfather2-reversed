// FUNC_NAME: DecisionMaker::resolveDualConditions

int DecisionMaker::resolveDualConditions()
{
    // Get two stat values from external function (indexed by 1 and 2)
    int stat1 = getStat(1);
    int stat2 = getStat(2);

    // Pointer to output buffer stored at this+0x08
    unsigned int* outputBuffer = *(unsigned int**)(this + 0x08);

    // Always set first flag to 1
    outputBuffer[0] = 1;

    // Set second flag based on equality of the two stats
    if (stat1 == stat2) {
        outputBuffer[1] = 1;
    } else {
        outputBuffer[1] = 0;
    }

    // Advance the buffer pointer by 8 bytes (two unsigned ints)
    *(unsigned int**)(this + 0x08) = outputBuffer + 2;

    return 1;
}