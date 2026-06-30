// FUNC_NAME: SomeObject::releaseChildObject
void __thiscall SomeObject::releaseChildObject(void)
{
    // +0x128: pointer to a dynamically allocated child object
    void* childObj = *(void**)(this + 0x128);
    if (childObj != 0)
    {
        // +0xb0: pointer to a sub-sub-object that needs cleanup via another function
        if (*(void**)((int)childObj + 0xb0) != 0)
        {
            FUN_004daf90((int)childObj + 0xb0);
        }
        // +0x9c: pointer to an object that has a destructor function pointer at +0xa8
        if (*(void**)((int)childObj + 0x9c) != 0)
        {
            // Call the destructor via the function pointer at +0xa8
            (**(code**)((int)childObj + 0xa8))(*(void**)((int)childObj + 0x9c));
        }
        // Call the child object's own destructor/free routine
        FUN_009c8eb0(childObj);
        // Clear the pointer
        *(void**)(this + 0x128) = 0;
    }
}