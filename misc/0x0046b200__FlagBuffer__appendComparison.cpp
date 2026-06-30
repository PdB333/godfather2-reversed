// FUNC_NAME: FlagBuffer::appendComparison
int FlagBuffer::appendComparison(int param_1) // __thiscall, this in ecx, param_1 is the object pointer
{
    int* bufferPtr; // puVar1 - pointer to current position in buffer
    int value1; // iVar2
    int value2; // iVar3

    // Get two values from some source (likely network state or flags)
    value1 = getFlagValue(1); // FUN_0046af90(1)
    value2 = getFlagValue(2); // FUN_0046af90(2)

    // +0x08 is pointer to a write buffer (probably a stream of uint32 pairs)
    bufferPtr = *(int**)(param_1 + 8);

    // Always set the first element to 1 (flag indicating this entry is valid)
    bufferPtr[0] = 1;

    // Second element is 1 if both values are equal, else 0
    if (value1 == value2) {
        bufferPtr[1] = 1;
    } else {
        bufferPtr[1] = 0;
    }

    // Advance the buffer pointer by 8 bytes (two ints)
    *(int**)(param_1 + 8) = bufferPtr + 2;

    return 1; // Always returns 1 (success)
}