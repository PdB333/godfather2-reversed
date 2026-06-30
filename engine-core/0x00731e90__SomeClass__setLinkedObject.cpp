// FUNC_NAME: SomeClass::setLinkedObject

void __thiscall SomeClass::setLinkedObject(int param_2)
{
    int* ppResource = &(this->field_0x2178);  // pointer to member at +0x2178
    int newResource;

    if (param_2 == 0) {
        newResource = 0;
    } else {
        newResource = param_2 + 0x48;  // offset for actual resource object? Or maybe the param is already a pointer, but code adds 0x48?
    }

    if (*ppResource != newResource) {
        if (*ppResource != 0) {
            // Release the old resource
            FUN_004daf90(ppResource);  // Custom deallocation function
        }
        *ppResource = newResource;
        if (newResource != 0) {
            // Link the resource: store the back-pointer from resource to owner's pointer
            this->field_0x217c = *(int*)(newResource + 4);  // previous back-pointer?
            *(int**)(newResource + 4) = ppResource;        // set new back-pointer to owner's pointer address
        }
    }

    if (param_2 == 0) {
        // Clear flags when resource is nullified
        this->field_0x1f58 &= 0xbfffffff;  // clear bit 30? (0x40000000)
        this->field_0x1f5c &= 0xffffff7f;  // clear bit 7? (0x80)
    }
    return;
}