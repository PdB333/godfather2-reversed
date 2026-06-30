// FUNC_NAME: destructor_with_free_at_offset_0x2C
void __thiscall FUN_005cd720(void *this)
{
    // Set vtable pointer to a purecall table (likely after destruction)
    *(void **)this = &PTR___purecall_00e3edb4;

    // If there is an allocated buffer at offset 0x2C (0xB * 4), free it
    if (*(void **)((char *)this + 0x2C) != nullptr)
    {
        // Call a global deallocation function (e.g., operator delete or free)
        ((void (*)(void *))DAT_0119caf4)(*(void **)((char *)this + 0x2C));
    }

    // Clear the pointer
    *(void **)((char *)this + 0x2C) = nullptr;
}