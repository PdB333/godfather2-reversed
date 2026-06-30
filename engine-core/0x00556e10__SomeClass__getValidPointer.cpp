// FUNC_NAME: SomeClass::getValidPointer
// Function address: 0x00556e10
// Returns a pointer from this+0x40 if it is non-null and its associated name string is non-empty.
// Uses a global resource manager (DAT_0113dfc8) to retrieve the name string.
void* SomeClass::getValidPointer()
{
    void* data = *(void**)(this + 0x40); // +0x40: pointer to resource data
    if (data != nullptr)
    {
        // Get the string table from the global resource manager
        // *DAT_0113dfc8 is a vtable pointer; offset 0x14 returns a string table instance
        StringTable* stringTable = (*(StringTable*(*)())(*(int*)DAT_0113dfc8 + 0x14))();
        // Get the string associated with this data (offset 0x10 on stringTable)
        const char* str = (*(const char*(*)(void*))(*(int*)stringTable + 0x10))(data);
        // Convert the string to a C-string (e.g., from wide char)
        char buffer[256];
        char* cstr = FUN_00ab06f0(buffer, str);
        if (*cstr == '\0')
        {
            return nullptr;
        }
    }
    return data;
}