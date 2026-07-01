// FUNC_NAME: releaseRefCountedPtr
void __fastcall releaseRefCountedPtr(int** ppObject)
{
    int* pObject = *ppObject;
    if (pObject != nullptr)
    {
        // Decrement reference count at offset +0x04
        int* pRefCount = (int*)(pObject + 1); // pObject + 4 bytes
        *pRefCount = *pRefCount - 1;

        // If reference count reaches zero, call destructor via vtable at offset +0x04
        if (*(int*)(pObject + 1) == 0) // same as *pRefCount
        {
            // vtable is at pObject[0], destructor at vtable[1] (offset 4)
            void (*destructor)(void*) = *(void (**)(void*))(*(int*)pObject + 4);
            destructor(pObject);
        }

        // Nullify the pointer
        *ppObject = nullptr;
    }
}