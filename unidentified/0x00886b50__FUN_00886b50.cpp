// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Function address: 0x00886b50
// Role: Scalar deleting destructor. Calls the actual destructor at 0x00886620 and conditionally deallocates memory via operator delete (0x00624da0) based on the flag.

class SomeClass {
public:
    SomeClass* scalarDeletingDestructor(byte deleteFlag);
};

SomeClass* SomeClass::scalarDeletingDestructor(byte deleteFlag) {
    this->~SomeClass(); // Calls base destructor (FUN_00886620) – destroys member data and calls base class destructor
    if (deleteFlag & 1) {
        delete this; // Deallocate memory via operator delete (FUN_00624da0) – typically scalar delete
    }
    return this; // Returns 'this' pointer (common in some custom allocators)
}