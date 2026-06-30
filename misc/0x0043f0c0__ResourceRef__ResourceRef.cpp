// FUNC_NAME: ResourceRef::ResourceRef
// Function address: 0x0043f0c0
// Role: Constructor for a reference-counted resource wrapper object.
//   Takes a pointer to a resource object (with vtable) and an optional resource handle.
//   Initializes internal fields and manages reference counting via vtable calls.
//   The resource object's vtable layout: +0 = unknown, +4 = Release, +8 = AddRef, +0xC = unknown (maybe GetSize/GetData).

int ResourceRef::ResourceRef(int this, int *pResource, int hResource)
{
    // pResource is a pointer to some EARS engine resource object with a vtable.
    // The first few virtual functions are used for reference counting and retrieval.
    // Vtable offsets:
    //  +0: unknown (maybe QueryInterface)
    //  +4: Release (called with (hResource, 0))
    //  +8: AddRef
    //  +0xC: unknown (called without arguments, possibly GetSize or BeginUse)
    typedef void (__thiscall *AddRefFunc)(int *);
    typedef void (__thiscall *ReleaseFunc)(int *, int, int);
    typedef void (__thiscall *UnknownFunc)(int *);
    AddRefFunc addRef = (AddRefFunc)(**(int **)(pResource + 8));
    ReleaseFunc release = (ReleaseFunc)(**(int **)(pResource + 4));
    UnknownFunc unknown = (UnknownFunc)(**(int **)(pResource + 0xC));

    // Initial AddRef on the resource object
    addRef(pResource);

    // If a resource handle is provided, load resource data and associate it
    int loadedData;
    if (hResource != 0)
    {
        // FUN_004265d0 likely loads a resource and returns a handle/data
        loadedData = LoadResourceData(hResource, pResource); // FUN_004265d0
    }
    else
    {
        loadedData = 0;
    }

    // FUN_0043f650 likely sets the resource data into the object
    SetResourceData(pResource, loadedData); // FUN_0043f650

    // Store the pointer at this+0x10
    *(int **)(this + 0x10) = pResource;

    // Another AddRef – possibly to keep a second reference for internal use
    addRef(pResource);

    // If a resource handle was given, we also keep its data and then release the handle
    if (hResource != 0)
    {
        // Load again using the stored pointer (maybe to get final data)
        loadedData = LoadResourceData(hResource, *(int **)(this + 0x10));
        *(int *)(this + 0x14) = loadedData;

        // Release the original handle (with some flag 0)
        release(pResource, hResource, 0);

        // Call unknown vtable function (maybe finalize or get size)
        unknown(pResource);

        // Return this
        return this;
    }

    // No handle: set stored data to zero
    *(int *)(this + 0x14) = 0;

    // Call unknown vtable function
    unknown(pResource);

    // Return this
    return this;
}