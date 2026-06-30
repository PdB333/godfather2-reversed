// FUNC_NAME: GameObject::getOwnerFromPointer
int __fastcall GameObject::getOwnerFromPointer(void* thisPtr)
{
    // Check if the pointer stored at offset +0x2178 (likely m_pChildComponent) is valid
    int* childPtr = *(int**)((char*)thisPtr + 0x2178);
    if (childPtr != nullptr)
    {
        // The child object is embedded at offset 0x48 from the parent.
        // Subtract 0x48 to get the owner/parent object address.
        return (int)childPtr - 0x48;
    }
    return 0;
}