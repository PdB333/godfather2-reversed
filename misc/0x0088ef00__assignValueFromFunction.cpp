// FUNC_NAME: assignValueFromFunction
uint32_t* __fastcall assignValueFromFunction(uint32_t* ptr)
{
    uint32_t result = transformValue(*ptr);
    *ptr = result;
    return ptr;
}