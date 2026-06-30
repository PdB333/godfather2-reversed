// FUNC_NAME: EARSBaseObject::destructor
void __thiscall EARSBaseObject::destructor(EARSBaseObject* this)
{
    // Set vtable to base class vtable to prevent virtual calls during destruction
    this->vtablePtr = &PTR_FUN_00e35228;

    // Release child resource if handle is valid and manager exists
    if (this->handle != 0 && this->manager != nullptr)
    {
        // manager->releaseResource(handle, someId)
        (*(void (__thiscall**)(int, int))(this->manager->vtablePtr + 4))(this->handle, this->someId);
    }

    // Finalize manager cleanup if present
    if (this->manager != nullptr)
    {
        // manager->finalize()
        (*(void (__thiscall**)(void))(this->manager->vtablePtr + 0xC))();
        return;
    }
    return;
}