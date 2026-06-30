// FUNC_NAME: EARSObject::constructor
// Function at 0x00419240: Constructor for EARSObject. Takes a flag indicating whether the object was dynamically allocated.
// Calls the base class constructor and optionally frees memory if the flag is set (exception safety pattern).
void* __thiscall EARSObject::constructor(EARSObject* thisPtr, byte isDynamic) {
    // Set the virtual function table pointer (+0x00)
    thisPtr->vtable = (void*)0x00e2fd10;
    
    // Call base class constructor at 0x00418740
    baseClassConstructor(thisPtr);
    
    // If the object was dynamically allocated (isDynamic & 1), call operator delete to clean up
    // This is typical of Visual C++ exception handling constructors where the runtime may need to deallocate
    if ((isDynamic & 1) != 0) {
        operatorDelete(thisPtr);
    }
    
    return thisPtr;
}