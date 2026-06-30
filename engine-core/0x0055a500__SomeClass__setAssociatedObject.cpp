// FUNC_NAME: SomeClass::setAssociatedObject
// Address: 0x0055a500
// Sets the associated object pointer at +0x34, performing attach/detach lifecycle.

void __thiscall SomeClass::setAssociatedObject(void* newObject)
{
    void* oldObject = *(void**)(this + 0x34); // +0x34 – pointer to currently associated object

    if (oldObject != 0)
    {
        detachOldObject(this);   // FUN_009f1b20 – detach previous object
        onObjectDetached();      // FUN_009f01a0 – notify detachment
    }

    *(void**)(this + 0x34) = newObject; // store new pointer

    if (newObject != 0)
    {
        attachNewObject(this);   // FUN_009f1f90 – attach new object
        onObjectAttached();      // FUN_009f0190 – notify attachment
    }
}