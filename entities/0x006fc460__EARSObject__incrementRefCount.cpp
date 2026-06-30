// FUNC_NAME: EARSObject::incrementRefCount
void __thiscall EARSObject::incrementRefCount(EARSObject *this)
{
    // Check if the primary reference counter (at offset +0x198) is zero
    if (*(int *)((int)this + 0x198) == 0) {
        // No primary ref count object, use the first sub-object at +0x180
        this = (EARSObject *)((int)this + 0x180);
    }
    else {
        // Check secondary flag at +0x1d0
        if (*(int *)((int)this + 0x1d0) != 0) {
            // Secondary reference already active, do nothing
            return;
        }
        // Use the second sub-object at +0x1b8
        this = (EARSObject *)((int)this + 0x1b8);
    }

    if (this != NULL) {
        // Increment the reference count at offset +0x30 of the chosen sub-object
        *(int *)((int)this + 0x30) += 1;
    }
    return;
}