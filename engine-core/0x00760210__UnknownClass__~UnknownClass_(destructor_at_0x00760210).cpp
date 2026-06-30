// FUNC_NAME: UnknownClass::~UnknownClass (destructor at 0x00760210)

void __thiscall UnknownClass::~UnknownClass(void *this)
{
    // Set vtable to object's normal function table
    *(int **)this = (int *)&PTR_FUN_00d653ec; // vtable pointer

    // Release owned pointers at specific offsets
    if (*(void **)((char *)this + 0x20) != 0) // offset +0x20 (param_1[8])
    {
        releasePtr((int **)((char *)this + 0x20));
    }
    if (*(void **)((char *)this + 0x10) != 0) // offset +0x10 (param_1[4])
    {
        releasePtr((int **)((char *)this + 0x10));
    }
    if (*(void **)((char *)this + 0x04) != 0) // offset +0x04 (param_1[1])
    {
        releasePtr((int **)((char *)this + 0x04));
    }

    // Finalize: vtable points to purecall to mark destruction
    *(int **)this = (int *)&PTR___purecall_00e407a4;
}