// FUNC_NAME: SomeClass::~SomeClass
int* __thiscall SomeClass::~SomeClass(int* this, byte shouldDelete)
{
    // Free the owned pointer if it exists
    if (*this != 0) {
        FUN_009c8f10(*this);  // Likely operator delete or custom free for the pointed object
    }
    // If the flag indicates we should also free the object itself (e.g., from a placement new)
    if ((shouldDelete & 1) != 0) {
        FUN_009c8eb0(this);   // Likely operator delete or custom free for this object
    }
    return this;
}