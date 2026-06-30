// FUNC_NAME: ManagedObject::init

// Address: 0x005e0170
// Initializes a ManagedObject, taking ownership of a reference-counted object pointer (int* object)
// and optionally associating a resource handle (int resourceId).
// The object's virtual table is used for reference counting and resource management.

int ManagedObject::init(int* object, int resourceId)
{
    int* obj = object;

    // Increase reference count on the object (vtable+8 = AddRef)
    (*(void (__thiscall**)(int*))(*obj + 8))(obj);

    int handle;
    if (resourceId == 0) {
        handle = 0;
    } else {
        // Resolve or duplicate the resource handle relative to the object
        handle = FUN_004265d0(resourceId, obj);
    }

    // Call base class constructor (likely initializes something with object and handle)
    FUN_005e0b60(obj, handle);

    // Store the object pointer at offset 0x14
    this->m_object = obj;

    // Second AddRef (duplicate reference held by this)
    (*(void (__thiscall**)(int*))(*obj + 8))(obj);

    if (resourceId != 0) {
        // Retrieve the final resource handle stored in the object
        handle = FUN_004265d0(resourceId, this->m_object);
        this->m_resourceHandle = handle; // offset 0x18

        // Attach the resource to the object (vtable+4 = SetResource)
        (*(void (__thiscall**)(int*, int, int))(*obj + 4))(obj, resourceId, 0);

        // Finalize or release temporary reference (vtable+12 = Release)
        (*(void (__thiscall**)(int*))(*obj + 12))(obj);
    } else {
        this->m_resourceHandle = 0;
        // Release the single AddRef from earlier (vtable+12 = Release)
        (*(void (__thiscall**)(int*))(*obj + 12))(obj);
    }

    return (int)this;
}