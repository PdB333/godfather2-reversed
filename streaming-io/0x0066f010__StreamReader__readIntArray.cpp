// FUNC_NAME: StreamReader::readIntArray
void __thiscall StreamReader::readIntArray(int *this, int *buffer, int count, int contextId)
{
    int i;
    for (i = 0; i < count; i++)
    {
        // Call virtual function at vtable offset 0xC, presumably getNextValue(contextId, 0)
        buffer[i] = (*(int (__thiscall **)(int, int, int))(*(int *)this + 0xC))(contextId, 0);
    }
}