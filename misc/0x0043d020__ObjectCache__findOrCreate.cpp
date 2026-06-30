// FUNC_NAME: ObjectCache::findOrCreate
// Address: 0x0043d020
// Retrieves an existing object by key, or creates a new one using the provided creation arguments.
// Internally uses a bucket manager at this+0x10 and a release function pointer at this+0x0c.

int* __thiscall ObjectCache::findOrCreate(int key, int* pCreateArgs, int arg4, int arg5)
{
    int* pSlot;            // pointer returned by bucket manager
    int* pObject;          // current object in the slot
    int bucketIndex = 0;   // index for bucket look-up
    int creationArgs[4];   // local copy of creation parameters

    // Copy creation arguments into local array
    creationArgs[0] = pCreateArgs[0];
    creationArgs[1] = pCreateArgs[1];
    creationArgs[2] = pCreateArgs[2];
    creationArgs[3] = pCreateArgs[3];

    // Bucket manager is stored at this+0x10
    void* bucketManager = reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x10);

    // Find the slot that would hold the object for this key
    pSlot = reinterpret_cast<int*>(FUN_0043d7a0(bucketManager, &bucketIndex));
    if (pSlot != nullptr)
    {
        pObject = reinterpret_cast<int*>(*pSlot);
        if (pObject != nullptr)
        {
            // If the existing object's key matches, return it
            if (*pObject == key)
            {
                return pObject;
            }
            // Otherwise, release the current object using the release function
            // Release function pointer is at vtable[1] (offset 0x04 from vtable base)
            // The vtable pointer is located at this+0x0c
            int** vtable = *reinterpret_cast<int***>(reinterpret_cast<char*>(this) + 0x0c);
            void (*releaseFunc)(int*, int) = reinterpret_cast<void(*)(int*, int)>(vtable[1]);
            releaseFunc(pObject, 0);
        }

        // Create a new object
        pObject = reinterpret_cast<int*>(FUN_0043d5f0());
        // Store the new object pointer into the slot
        *pSlot = reinterpret_cast<int>(pObject);

        // If creation failed, attempt a fallback
        if (pObject == nullptr)
        {
            int fallbackResult = FUN_0043db90(creationArgs);
            if (fallbackResult >= 0)
            {
                FUN_0043db10();
            }
        }
    }

    return pObject;
}