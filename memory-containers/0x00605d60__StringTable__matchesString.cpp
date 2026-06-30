// FUNC_NAME: StringTable::matchesString
bool __fastcall StringTable::matchesString(char *str, uint index)
{
    bool result = false;
    // Class layout (this in ESI):
    // +0x0c: char (*strings)[8]  // pointer to array of 8-byte strings
    // +0x14: uint count          // number of strings in array
    if (index < *(uint *)((char *)this + 0x14))
    {
        char *tableStr = (char *)(*(int *)((char *)this + 0x0c) + index * 8);
        if ((str != nullptr) && (tableStr != nullptr))
        {
            int cmp = __stricmp(str, tableStr);
            return cmp == 0;
        }
        result = tableStr <= str;
        if (tableStr < str)
        {
            return false;
        }
    }
    return result;
}