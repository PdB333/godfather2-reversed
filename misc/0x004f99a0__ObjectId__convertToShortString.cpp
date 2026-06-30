// FUNC_NAME: ObjectId::convertToShortString
void __thiscall ObjectId::convertToShortString(void *this, int flags)
{
    char shortString[12];
    FUN_00414aa0(); // global initialization (e.g. singleton check)
    char *guidBytes = *(char **)((char *)this + 0x24) + 0x40; // offset +0x24: pointer to GUID data, +0x40: offset to binary GUID bytes
    FUN_0056b420(guidBytes, shortString, flags); // binary GUID to short string (12 chars)
    return;
}