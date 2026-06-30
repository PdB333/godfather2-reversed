// FUNC_NAME: getGlobalArrayElement
// Function at 0x0067bf20: reads a DWORD from a global array at DAT_01129808 indexed by param_1.
// Returns the element at the given index.
uint32_t getGlobalArrayElement(int index)
{
    return *(uint32_t*)(DAT_01129808 + index * 4);
}