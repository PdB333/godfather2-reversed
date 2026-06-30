// FUNC_NAME: floatToDoubleWrapper
void floatToDoubleWrapper(float inputValue)
{
    // Call the underlying double-precision math function (address 0x00b9c2a0)
    FUN_00b9c2a0(static_cast<double>(inputValue));
    return;
}