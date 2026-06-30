// FUNC_NAME: EARSObject::getObjectTypeID
// Address: 0x0045eea0
// Role: Returns the type ID of the object, or -1 if the object's type info is null.
// Accesses a pointer at this+0x218 (likely to a type descriptor or class info struct),
// then reads an int at offset +0x14 from that pointer.

int __fastcall EARSObject::getObjectTypeID(void *this)
{
    // +0x218: Pointer to an internal type/class descriptor.
    int *typeDescriptor = *(int **)((char *)this + 0x218);
    if (typeDescriptor != NULL)
    {
        // +0x14: Type identifier (e.g., hash, index, or ID).
        return *(int *)((char *)typeDescriptor + 0x14);
    }
    return -1;
}