//FUNC_NAME: Object::getParentFromMember
// Function at 0x00791300: Returns a pointer to the parent object that contains the member pointed to by this->memberPtr.
// If this->memberPtr (at offset +0x9c) is non-null, it subtracts 0x48 to get the containing object's address.
// This is a common pattern for intrusive containers where a node is embedded at offset 0x48 in the parent.
int* __thiscall Object::getParentFromMember(void* thisPtr)
{
    // +0x9c: pointer to a child structure (e.g., a linked list node or sub-object)
    int* memberPtr = *(int**)((char*)thisPtr + 0x9c);
    if (memberPtr != 0) {
        // The child structure is embedded at offset 0x48 in the parent object.
        // Subtract 0x48 to get the parent object's address.
        return (int*)((char*)memberPtr - 0x48);
    }
    return 0;
}