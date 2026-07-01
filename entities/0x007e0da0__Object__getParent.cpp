// FUNC_NAME: Object::getParent
int __fastcall Object::getParent(int thisPtr)
{
    // Offset 0x12C stores a pointer to a member field within the parent object.
    // The parent object's base address is 0x48 bytes before that member.
    // If the pointer is null, return 0.
    int* pMember = *(int**)(thisPtr + 0x12C);
    if (pMember)
    {
        return (int)((char*)pMember - 0x48);
    }
    return 0;
}