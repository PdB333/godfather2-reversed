// FUNC_NAME: RefCountedObject::Release

void __fastcall RefCountedObject::Release(int* ppThis)
{
    // Likely lock or atomic decrement helper
    LockMutex(); // FUN_004226c0

    int* pThis = (int*)*ppThis; // Dereference to get actual object pointer
    int* pRefCount = pThis + 1; // Ref count at offset 0x04

    *pRefCount -= 1; // Decrement reference count

    if (*pRefCount == 0)
    {
        // Call the second virtual function (destructor or delete)
        // vtable is at pThis[0], entry at offset 0x04
        (**(code**)(pThis[0] + 4))();
    }
}