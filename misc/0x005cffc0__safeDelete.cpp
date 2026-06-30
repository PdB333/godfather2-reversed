// FUNC_NAME: safeDelete
// Address: 0x005cffc0
// Utility: safely deletes an object via its vtable's second entry (typically destructor) and nulls the pointer.

void __fastcall safeDelete(void** ptrToPtr)
{
    void* object = *ptrToPtr;
    if (object != nullptr)
    {
        // Call the virtual function at vtable offset 4 (second entry)
        void (*deleter)(void*) = *(void(**)(void*))((*(int*)object) + 1);
        deleter(object);
    }
    *ptrToPtr = nullptr;
}