// FUNC_NAME: RefCounted::release
void __fastcall RefCounted::release(RefCounted* this)
{
    int* refCount = (int*)((char*)this + 0x54); // +0x54: reference count
    *refCount = *refCount - 1;
    if (*refCount == 0) {
        // Cleanup function at 0x005c1b40
        FUN_005c1b40();
        // Clear bit 1 (0x2) in flags at +0x50
        *(uint32_t*)((char*)this + 0x50) &= ~0x2;
    }
}