// FUNC_NAME: SomeClass::DeletingDestructor
struct SomeClass {
    // +0x00: vtable? (implicit)
    void* internalPtr;  // +0x04: pointer to dynamically allocated internal object
};

// Forward declarations for memory management helpers
void DeleteObject(void* obj);   // Freed internal object
void FreeObject(void* ptr);     // Frees the entire SomeClass instance

int __thiscall SomeClass::DeletingDestructor(SomeClass* this, uint8_t deleteFlag)
{
    if (this->internalPtr != nullptr) {
        DeleteObject(this->internalPtr); // Destroy the internal sub-object
    }
    if (deleteFlag & 1) {
        FreeObject(this); // Delete the entire SomeClass instance if flag is set
    }
    return this; // Return the pointer (likely for chaining)
}