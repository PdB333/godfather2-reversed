// FUNC_NAME: hashStringToUint32
void hashStringToUint32(int *output, int input)
{
    // Four 32-bit blocks extracted from the input by an internal helper
    uint32_t block0, block1, block2, block3;
    // FUN_004d9500 takes the input (e.g. a string pointer) and fills the four local variables
    FUN_004d9500(input, &block0, &block1, &block2, &block3);
    // Polynomial hash using base 33 (common EA djb2-style hash)
    *output = ((block0 * 0x21 + block1) * 0x21 + block2) * 0x21 + block3;
}