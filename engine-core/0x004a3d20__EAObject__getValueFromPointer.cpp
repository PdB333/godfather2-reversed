// FUNC_NAME: EAObject::getValueFromPointer
int __fastcall EAObject::getValueFromPointer(EAObject* this)
{
    // Check if the pointer stored at offset +0x4 is valid
    // (likely a pointer to a sub-object or resource)
    if (*(int*)((char*)this + 4) != 0)
    {
        // If valid, call the helper function to retrieve the value
        return sub_4A3790();
    }
    // Otherwise return 0 (null/error)
    return 0;
}