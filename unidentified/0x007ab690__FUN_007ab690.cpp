// FUNC_NAME: SomeClass::getContainingObject
// Function at 0x007ab690: Retrieves a pointer to the containing object from a member pointer.
// The 'this' object has a pointer at offset +0x58 to a large structure.
// That structure has a field at offset +0x24fc which is a pointer to a member inside an object.
// Subtracting 0x48 (offset of that member) yields the containing object pointer.
// Returns 0 if the intermediate pointer is null.

int __fastcall SomeClass::getContainingObject(int thisPtr)
{
    int* ptr = *(int**)(thisPtr + 0x58); // +0x58: pointer to some large data structure
    if (ptr != 0) {
        int memberPtr = *(int*)((int)ptr + 0x24fc); // +0x24fc: pointer to a member inside an object
        if (memberPtr != 0) {
            return memberPtr - 0x48; // subtract offset of the member to get containing object
        }
    }
    return 0;
}