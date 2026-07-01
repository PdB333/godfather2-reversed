// FUNC_NAME: SomeClass::destructor
void __thiscall SomeClass::destructor(int isDeleting)
{
    // If the deleting flag is set, perform cleanup and free memory
    if (isDeleting != 0) {
        // Internal cleanup routine (likely releases owned resources)
        this->internalCleanup();
        // Free the object's memory (e.g., operator delete or custom deallocator)
        this->internalFree(isDeleting);
    }
}