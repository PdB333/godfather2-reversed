// FUNC_NAME: computeTwoOrThreeConstant
int computeTwoOrThreeConstant(void)
{
    // Call some function to get a value.
    int value = getSomeValue();

    // The original code uses unsigned comparison trick:
    // condition: (value == 2 || value == 3) yields 0, else yields 0xFFFFFFFF.
    // Then AND with constant and add base.
    // We'll implement the same logic clearly.
    // The magic constants: 0x1083145C and 0x9B587A1C.
    if (value == 2 || value == 3)
    {
        return 0x1083145C;
    }
    else
    {
        return 0xABDB8E78; // 0x9B587A1C + 0x1083145C
    }
}