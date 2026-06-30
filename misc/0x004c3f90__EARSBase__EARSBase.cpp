// FUNC_NAME: EARSBase::EARSBase
void __thiscall EARSBase::EARSBase(EARSBase *this)
{
    // Set primary vtable pointer (offset +0x00)
    *(void **)this = &PTR___purecall_00e362c8;

    // Set secondary vtable/interface pointer (offset +0x04)
    *(void **)((char *)this + 4) = &PTR_LAB_00e362b8;

    // Overwrite secondary pointer (offset +0x04) with another vtable
    // This likely resolves virtual inheritance or interface thunk
    *(void **)((char *)this + 4) = &PTR_LAB_00e362e4;

    // Initialize a flag or counter to 1 (offset +0x08)
    *(int *)((char *)this + 8) = 1;
}