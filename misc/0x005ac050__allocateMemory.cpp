// FUNC_NAME: allocateMemory
void allocateMemory(void)
{
    // Call memory allocation function with size 0x5C (92 bytes) and flags=0
    // Function pointer stored at 0x0119caf0
    (*DAT_0119caf0)(0x5c, 0);
    return;
}