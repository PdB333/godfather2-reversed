// FUNC_NAME: EARSObject::finalize
void __fastcall EARSObject::finalize()
{
    // +0x00: vtable pointer
    // +0x04: subObject (pointer to child object)
    if (this->subObject != nullptr)
    {
        // Call virtual function at vtable[1] (offset 0x04) to release subObject with flag 0
        (this->vtable->releaseSubObject)(this->subObject, 0);
        this->subObject = nullptr;
    }
    // Call virtual function at vtable[3] (offset 0x0C) for final destruction/cleanup
    (this->vtable->destroy)();
}