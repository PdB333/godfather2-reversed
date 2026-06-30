// FUNC_NAME: UnknownClass::`scalar deleting destructor'
// Function at 0x0074c730: Standard scalar deleting destructor pattern.
// Calls the class destructor if the object is non-null, then optionally operator delete based on flag.
// param_2: bit 0 indicates whether to free memory (use delete operator).
int* __thiscall UnknownClass::scalarDeletingDestructor(int* thisPtr, byte shouldDelete) {
    if (*thisPtr != 0) {
        // Call the actual destructor for the class (FUN_004daf90)
        this->~UnknownClass();  // Assuming destructor is at 0x004daf90
    }
    if ((shouldDelete & 1) != 0) {
        // Call operator delete (FUN_009c8eb0)
        operator delete(thisPtr);  // Assuming operator delete at 0x009c8eb0
    }
    return thisPtr;
}