// FUNC_NAME: EARSObject::releaseAndNullResource
void __fastcall EARSObject::releaseAndNullResource(int this)
{
    if (*(int *)(this + 0x8c) != 0) {
        FUN_009c8eb0(*(int *)(this + 0x8c));  // releaseResource (likely decrement refcount or free)
        *(int *)(this + 0x8c) = 0;            // clear resource pointer at +0x8c
    }
    return;
}