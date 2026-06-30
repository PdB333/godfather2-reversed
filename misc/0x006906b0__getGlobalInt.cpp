// FUNC_NAME: getGlobalInt
unsigned int getGlobalInt(void)
{
    // Returns the value of global variable at 0x01129bc0
    return *(unsigned int*)0x01129bc0;
}