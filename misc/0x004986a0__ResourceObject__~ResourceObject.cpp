// FUNC_NAME: ResourceObject::~ResourceObject
void __fastcall ResourceObject::~ResourceObject(int thisPtr)
{
    // Free resource at offset +0x10 (always allocated)
    MemFree(*(void **)(thisPtr + 0x10));
    // Free optional resource at offset +0x4 if present
    if (*(int *)(thisPtr + 0x4) != 0) {
        MemFree(*(void **)(thisPtr + 0x4));
    }
}