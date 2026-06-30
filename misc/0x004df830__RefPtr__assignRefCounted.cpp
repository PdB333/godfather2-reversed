// FUNC_NAME: RefPtr::assignRefCounted
void __thiscall RefPtr::assignRefCounted(void* thisPtr, int* newRefStruct)
{
    int* managedObject = *(int**)thisPtr; // +0x00: pointer to managed object

    if (managedObject != nullptr)
    {
        int* oldRefStruct = *(int**)(managedObject + 0x20); // +0x20: pointer to reference count structure
        if (oldRefStruct != nullptr)
        {
            int* refCount = (int*)(oldRefStruct + 4); // +0x04: reference count integer
            *refCount = *refCount - 1;

            if (*(int*)(oldRefStruct + 4) == 0) // check if ref count reached zero
            {
                // Call virtual destructor via vtable at offset 0 of ref struct, first virtual function at offset 4
                (**(void (__thiscall**)(void*))(*(int*)oldRefStruct + 4))(oldRefStruct);
            }
            *(int*)(managedObject + 0x20) = 0; // clear old ref struct pointer
        }

        *(int*)(managedObject + 0x20) = (int)newRefStruct; // assign new ref struct

        if (newRefStruct != nullptr)
        {
            *(int*)(newRefStruct + 4) = *(int*)(newRefStruct + 4) + 1; // increment ref count
        }
    }
}