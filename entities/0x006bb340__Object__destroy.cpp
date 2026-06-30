// FUNC_NAME: Object::destroy
// Function address: 0x006bb340
// Role: Internal destructor/deallocator helper for reference-counted or flag-managed objects.
//        Checks if object is valid (*this != 0) and calls cleanup (0x004daf90).
//        Then if the low bit of the flag is set, deallocates memory (0x009c8eb0).
int* __thiscall Object::destroy(int* thisObj, byte deleteFlag)
{
    // If the first word (likely vtable pointer or flag) is non-null, the object is alive
    if (*thisObj != 0) {
        // Internal cleanup / destructor call
        Object::cleanup(thisObj);           // 0x004daf90
    }
    // Deallocate memory if requested (bit 0 set)
    if ((deleteFlag & 1) != 0) {
        Object::deallocate(thisObj);        // 0x009c8eb0
    }
    return thisObj;
}