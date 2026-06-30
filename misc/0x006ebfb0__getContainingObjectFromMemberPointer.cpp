// FUNC_NAME: getContainingObjectFromMemberPointer
// Function at 0x006ebfb0: Given an object with a member pointer at offset 0x1ed8,
// returns the base of the containing structure if the pointer is non-null.
// Pattern: stored pointer points into a structure at offset 0x48, so we subtract 0x48 to get the containing object.
#include <cstddef>

void* __fastcall getContainingObjectFromMemberPointer(void* obj)
{
    void* memberPtr = *(void**)((char*)obj + 0x1ed8); // +0x1ed8: pointer to sub-object field
    if (memberPtr != nullptr)
    {
        return (void*)((char*)memberPtr - 0x48); // subtract field offset to get owner
    }
    return nullptr;
}