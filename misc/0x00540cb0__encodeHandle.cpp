// FUNC_NAME: encodeHandle
uint encodeHandle(uint index)
{
    return (index >> 2) | 0xc0000000;
}