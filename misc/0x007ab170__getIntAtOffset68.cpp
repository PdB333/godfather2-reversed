// FUNC_NAME: getIntAtOffset68
int __fastcall getIntAtOffset68(void* thisPtr)
{
    // Returns the 32-bit integer stored at offset 0x68 from the object's base.
    // This is a simple getter used by many callers throughout the codebase.
    return *(int*)((char*)thisPtr + 0x68);
}