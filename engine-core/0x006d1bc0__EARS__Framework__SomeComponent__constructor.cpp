// FUNC_NAME: EARS::Framework::SomeComponent::constructor
void __fastcall EARS::Framework::SomeComponent::constructor(void* this)
{
    // offset +0xD8: pointer to internal buffer/resource
    int* internalBuffer = *(int**)((char*)this + 0xD8);

    // set vtable pointers (standard pattern for EA EARS constructors)
    *(int**)this = (int*)&PTR_FUN_00d5f360;      // +0x00: main vtable
    *(int**)((char*)this + 8) = (int*)&PTR_LAB_00d5f358; // +0x08: secondary vtable

    // if a previous buffer exists, release it via memory manager
    if (internalBuffer != 0)
    {
        void* memoryManager = (void*)FUN_009c8f80(); // get memory manager instance
        if (memoryManager != 0)
        {
            // call vtable[1] (offset +4) – likely a deallocate method
            (**(void (__stdcall**)(void*, uint))memoryManager)(internalBuffer, 0xA0);
        }
    }

    // check debug flag; if set, log message (type 8)
    if (FUN_0089c630() != 0)
    {
        FUN_006915c0(8);
    }

    // additional common initialization
    FUN_00473a60();
}