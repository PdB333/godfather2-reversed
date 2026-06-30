// FUNC_NAME: nullCheckAndCall
// Address: 0x006aba10
// Role: Returns result of internal function if input pointer is non-null, otherwise returns 0.
unsigned char nullCheckAndCall(int* ptr)
{
    if (ptr != nullptr)
    {
        return FUN_006ab960(); // internal function returning unsigned char
    }
    return 0;
}