// FUNC_NAME: Array::Array
void __fastcall Array::Array(int thisPtr)
{
    // +0x4: pointer to data buffer
    // +0x8: capacity (number of elements)
    // +0xC: current count (initialized to 0)
    FUN_00887870(*(int *)(thisPtr + 4), *(int *)(thisPtr + 8));
    *(int *)(thisPtr + 0xC) = 0;
    if (1 < *(unsigned int *)(thisPtr + 8)) {
        FUN_009c8f10(*(int *)(thisPtr + 4));
    }
}