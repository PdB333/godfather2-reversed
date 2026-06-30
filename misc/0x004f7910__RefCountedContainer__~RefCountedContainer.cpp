// FUNC_NAME: RefCountedContainer::~RefCountedContainer

void __fastcall RefCountedContainer::~RefCountedContainer(RefCountedContainer* this)
{
    // +0x20: mRefCountedObj (pointer to a reference-counted object)
    int* refCountedObj = this->mRefCountedObj;

    if (refCountedObj != 0)
    {
        // Decrement the reference count located at offset 0x04 of the referenced object.
        int* refCountPtr = (int*)(refCountedObj + 4);
        --(*refCountPtr);

        // If the reference count dropped to zero, call the object's virtual destructor
        // (located at vtable+0x04) to free it.
        if (*refCountPtr == 0)
        {
            // vtable is at offset 0x00, the second entry (vtable+0x04) is the destructor.
            (*(code**)(*(int*)refCountedObj + 4))(refCountedObj);
        }

        // Nullify the pointer so it no longer references the object.
        this->mRefCountedObj = 0;
    }

    // Finally, reset this object's vtable to a static base vtable (safety placeholder)
    // to prevent further virtual calls after destruction.
    this->vtable = &PTR_LAB_00e3729c;
}