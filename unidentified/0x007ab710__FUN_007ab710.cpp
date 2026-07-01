// FUNC_NAME: SomeObject::getParentFromInternalPointer
// Function at 0x007ab710: Retrieve an owning object by walking an internal linked list or pointer structure.
// Uses pointer chain: this->m_internalPtr (+0x58) -> field at +0xFFC -> subtract 0x48 to get container base.
// This pattern is typical of embedded objects where a pointer to a member is stored, and the parent is found via offset subtraction.
// Returns 0 if any pointer in the chain is null.

int __fastcall SomeObject::getParentFromInternalPointer(int thisPtr)
{
    int result = 0;
    // Pointer at +0x58 is likely an internal structure (e.g., a list node or manager pointer)
    int internalPtr = *(int *)(thisPtr + 0x58);
    if (internalPtr != 0)
    {
        // Dereference a field at offset 0xFFC from that internal structure
        // 0xFFC is a large offset, suggesting the structure is large (e.g., vtable or array)
        int fieldPtr = *(int *)(internalPtr + 0xFFC);
        if (fieldPtr != 0)
        {
            // Subtract 0x48 bytes to get the base of the owning container
            // This is effectively a CONTAINING_RECORD macro
            result = fieldPtr - 0x48;
        }
    }
    return result;
}