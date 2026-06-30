//FUNC_NAME: Pool::acquireObject
int* __thiscall Pool::acquireObject(void)
{
    bool bSuccess = false;
    int* pObject = nullptr;

    // Enter critical section to protect the pool
    EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x28));

    // Check if there are any available objects
    if (*(int*)(this + 0x24) != 0) {
        // Retrieve the object at the current head index
        pObject = *(int**)(*(int*)(this + 0x18) + *(int*)(this + 0x20) * 4);

        // Advance the head index
        int newIndex = *(int*)(this + 0x20) + 1;
        *(int*)(this + 0x20) = newIndex;

        // Wrap around if we've reached the capacity
        if (*(int*)(this + 0x1c) <= newIndex) {
            *(int*)(this + 0x20) = 0;
        }

        // Decrement the available count
        *(int*)(this + 0x24) = *(int*)(this + 0x24) - 1;
        bSuccess = true;
    }

    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x28));

    // If we successfully acquired an object, increment its reference count
    if (bSuccess) {
        *pObject = *pObject + 1;
    }

    return pObject;
}