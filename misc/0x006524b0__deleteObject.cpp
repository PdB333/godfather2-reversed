// FUNC_NAME: deleteObject

// This function calls a base destructor/cleanup, then deallocates memory if the pointer is non-null.
void deleteObject(void* objPtr) // Pointer to the object being destroyed
{
    // Invoke the base destructor or cleanup routine (likely Destructible::~Destructible or similar)
    destroyBaseClass();  // FUN_00652640
    // If the object pointer is valid, free its memory
    if (objPtr != nullptr) {
        freeMemory(objPtr); // FUN_009c8eb0 - likely operator delete or custom deallocator
    }
}