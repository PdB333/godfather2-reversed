// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(void* thisPtr, int param2, int param3, int param4)
{
    // Stack locals for temporary object and managed pointers
    int local_34 = param2;               // Pointer to the data object to destroy
    int local_30 = 0;                    // First managed pointer (to be released)
    int local_2c = 0;
    int local_28 = 0;
    void* local_24 = nullptr;            // Release function pointer for local_30
    int local_20 = 0;
    void* local_1c = nullptr;            // Second managed pointer (to be released)
    int local_18 = 0;
    int local_14 = 0;
    void* local_10 = nullptr;            // Release function pointer for local_1c
    int local_c = 0;
    int local_8 = param4;                // Additional parameter (e.g., destructor flags)
    int local_4 = param3;                // Unused except for initialization

    // Check if reference counting allows destruction
    // +0x1c likely mWeakRefCount, +0x14 likely mRefCount
    if (*(int*)((int)thisPtr + 0x1c) < *(int*)((int)thisPtr + 0x14))
    {
        // Destroy the object pointed to by param2 (typically the data itself)
        destroyObject(&local_34);

        // Release the global singleton or manager referenced by DAT_012069c4
        releaseGlobalSingleton(&DAT_012069c4);

        // Release the first managed resource if present
        if (local_1c != nullptr)
        {
            ((void (*)(void*))local_10)(local_1c);
        }

        // Release the second managed resource if present
        if (local_30 != 0)
        {
            ((void (*)(void*))local_24)(local_30);
        }
    }
}