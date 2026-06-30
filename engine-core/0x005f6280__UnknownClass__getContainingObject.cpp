// FUNC_NAME: UnknownClass::getContainingObject
// Returns the base pointer of the object that contains the member at offset +0x24.
// The member at +0x24 is a pointer to a sub-object that lies at offset 0x48 within the container.
void* __thiscall UnknownClass::getContainingObject(void* thisPtr)
{
    // +0x24: pointer to an embedded sub-object
    void* subObjPtr = *(void**)((char*)thisPtr + 0x24);
    if (subObjPtr != nullptr)
    {
        // The sub-object is at offset 0x48 inside its container, so subtract to get container base.
        return (void*)((char*)subObjPtr - 0x48);
    }
    return nullptr;
}