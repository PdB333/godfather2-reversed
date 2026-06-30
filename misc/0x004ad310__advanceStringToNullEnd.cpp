// FUNC_NAME: advanceStringToNullEnd
void __fastcall advanceStringToNullEnd(void* context, const char* str)
{
    while (*str)
        ++str; // advance to null terminator
    FUN_004ae6f0(context, str); // call downstream function with context and end pointer
}